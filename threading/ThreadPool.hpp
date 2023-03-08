#pragma once

#include <mutex>
#include <thread>

#include <queue>
#include <vector>
#include <functional>

#include "../singleton.hpp"

namespace CORE {

	struct T_ThreadJob {
		void* param = nullptr;
		std::function<void(void* param)> fn = nullptr;
	};

	class C_ThreadPool : public Singleton<C_ThreadPool> {
	public:
		void spawnThreads();
		void killThreads();
		void queueTask(T_ThreadJob& task);
	private:
		static void threadLoop(void* instance);
	private:
		bool _shouldTerminate{};

		std::mutex _queueMutex{};
		std::condition_variable _mutexCondition{};

		std::vector<std::thread> _threadPool{};
		std::queue<T_ThreadJob> _tasks{};
	};
}