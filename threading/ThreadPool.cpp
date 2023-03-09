#include "ThreadPool.hpp"

using namespace CORE;

void C_ThreadPool::workerThread(void* param) {

	const auto threadPoolData = reinterpret_cast<C_ThreadPool*>(param);

	if (threadPoolData->_workerConstructor) {
		threadPoolData->_workerConstructor();
	}

	while (threadPoolData->_running) {

		std::function<void()> task;
		std::unique_lock<std::mutex> taskLock(threadPoolData->_tasksMutex);

		threadPoolData->_cvTaskAvailable.wait(taskLock, [threadPoolData] { return !threadPoolData->_tasks.empty() || !threadPoolData->_running; });

		if (threadPoolData->_running) {

			task = std::move(threadPoolData->_tasks.front());
			threadPoolData->_tasks.pop();

			taskLock.unlock();

			task();

			taskLock.lock();
			--threadPoolData->_taskCount;

			if (threadPoolData->_waiting) {
				threadPoolData->_cvTaskDone.notify_one();
			}
		}
	}

	if (threadPoolData->_workerDestructor) {
		threadPoolData->_workerDestructor();
	}
}

void C_ThreadPool::spawnThreads(std::function<void()> workerConstructor, std::function<void()> workerDestructor) {

	if (std::thread::hardware_concurrency() > 0) {
		_threadCount = std::thread::hardware_concurrency();
	}
	else {
		_threadCount = 1;
	}
	
	_threads = std::make_unique<std::thread[]>(_threadCount);
	_running = true;

	for (concurrency_t i = 0; i < _threadCount; i++) {
		_threads[i] = std::thread(workerThread, this);
	}
}

void C_ThreadPool::killThreads() {

	// dont stop until finished everything in the thread pool
	waitForTasks();

	_running = false;
	_cvTaskAvailable.notify_all();

	for (concurrency_t i = 0; i < _threadCount; i++) {
		_threads[i].join();
	}
}

void C_ThreadPool::waitForTasks() {

	_waiting = true;

	std::unique_lock<std::mutex> taskLock(_tasksMutex);
	_cvTaskDone.wait(taskLock, [this] { return (_taskCount == 0); });

	_waiting = false;
}