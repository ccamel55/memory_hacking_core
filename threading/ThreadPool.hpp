#pragma once

#include <mutex>
#include <thread>

#include <queue>
#include <vector>
#include <functional>

#include "../singleton.hpp"

namespace CORE {

	class C_ThreadPool : public Singleton<C_ThreadPool> {
	public:
		void spawnThreads();
		void killThreads();
		void queueTask(const std::function<void()>& task);
		bool isBusy();
	private:
		static void threadLoop(void* instance);
	private:
		bool _shouldTerminate{};

		std::mutex _queueMutex{};
		std::condition_variable _mutexCondition{};

		std::vector<std::thread> _threadPool{};
		std::queue<std::function<void()>> _tasks{};
	};
}