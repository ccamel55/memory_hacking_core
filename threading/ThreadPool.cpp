#include "ThreadPool.hpp"

using namespace CORE;

// https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

void C_ThreadPool::spawnThreads() {

	// we should probably play with this and find a more optimal value
	auto threadCount = std::thread::hardware_concurrency();

	if (threadCount < 2) {
		threadCount = 2;
	}
	else if (threadCount >= 8) {
		threadCount -= 2;
	}

	for (size_t i = 0; i < threadCount; i++) {
		_threadPool.push_back(std::thread(threadLoop, this));
	}
}

void C_ThreadPool::killThreads() {

	std::unique_lock<std::mutex> lock(_queueMutex);

	_shouldTerminate = true;
	_mutexCondition.notify_all();

	// wait for all threads to finish thier tasks
	for (std::thread& active_thread : _threadPool) {
		active_thread.join();
	}

	_threadPool.clear();
}

void C_ThreadPool::queueTask(const std::function<void()> &task) {

	std::unique_lock<std::mutex> lock(_queueMutex);
	_tasks.push(task);

	_mutexCondition.notify_one();
}

bool C_ThreadPool::isBusy() {
	
	std::unique_lock<std::mutex> lock(_queueMutex);
	return _tasks.empty();
}

void C_ThreadPool::threadLoop(void* instance) {

	const auto threadPoolInstance = reinterpret_cast<C_ThreadPool*>(instance);

	while (true) {

		std::unique_lock<std::mutex> lock(threadPoolInstance->_queueMutex);

		// wait for task if we dont have one
		threadPoolInstance->_mutexCondition.wait(lock, [&] {
			return !threadPoolInstance->_tasks.empty() || threadPoolInstance->_shouldTerminate;
			});

		if (threadPoolInstance->_shouldTerminate) {
			return;
		}

		auto task = threadPoolInstance->_tasks.front();
		threadPoolInstance->_tasks.pop();

		task();
	}
}