#pragma once

#include <mutex>
#include <thread>

#include <queue>
#include <vector>
#include <functional>

#include "../singleton.hpp"

namespace CORE {

	// modified version of thread_pool_light
	// https://github.com/bshoshany/thread-pool/blob/master/BS_thread_pool_light.hpp

	using concurrency_t = std::invoke_result_t<decltype(std::thread::hardware_concurrency)>;

	class C_ThreadPool : public Singleton<C_ThreadPool> {
	public:
		void spawnThreads(std::function<void()> workerConstructor = nullptr, std::function<void()> workerDestructor = nullptr);
		void killThreads();
		void waitForTasks();

		template <typename F, typename... A>
		void addTask(F&& task, A&&... args) {

			std::function<void()> taskFunction = std::bind(std::forward<F>(task), std::forward<A>(args)...); {

				const std::scoped_lock taskLock(_tasksMutex);
				_tasks.push(taskFunction);
			}

			_taskCount++;
			_cvTaskAvailable.notify_one();
		}
	private:
		static void workerThread(void* param);

		std::function<void()> _workerConstructor = nullptr;
		std::function<void()> _workerDestructor = nullptr;

        std::atomic<bool> _running = false;
		std::atomic<bool> _waiting = false;

        std::condition_variable _cvTaskAvailable = {};
        std::condition_variable _cvTaskDone = {};

		concurrency_t _threadCount = 0;
		std::atomic<size_t> _taskCount = 0;

		mutable std::mutex _tasksMutex = {};

        std::queue<std::function<void()>> _tasks = {};
        std::unique_ptr<std::thread[]> _threads = nullptr;
	};
}