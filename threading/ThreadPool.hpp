#pragma once

#include "../singleton.hpp"

namespace CORE {

	class C_ThreadPool : public Singleton<C_ThreadPool> {
	public:
		C_ThreadPool();
		~C_ThreadPool();

		void spawnThreads();
		void killThreads();
	private:



	};
}