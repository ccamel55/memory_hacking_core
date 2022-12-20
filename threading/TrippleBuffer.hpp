#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace CORE {

	template<typename T>
	class C_TrippleBuffer {
	public:
		C_TrippleBuffer(T& readBuffer, T& writeBuffer, T& readyBuffer) :
			_reading(&readBuffer),
			_writing(&writeBuffer),
			_ready(&readyBuffer) {

			// dont swap by default
			_updated.exchange(true);
		}

		~C_TrippleBuffer() {

		}

		T* getWriteBuffer() {
			return _writing.load();
		}

		void finishWrite() {

			// swap ready and write buffers
			auto p = _ready.exchange(_writing);
			_writing.store(p);

			// mark updated info
			_updated.exchange(false);
		}

		const T* getReadBuffer() const {
			return _reading.load();
		}

		void finishRead() {

			// if we didnt update then dont swap
			if (_updated.exchange(true)) {
				return;
			}

			// swap only if we updated
			auto p = _ready.exchange(_reading);
			_reading.store(p);
		}

	private:
		std::atomic<T*> _reading{};
		std::atomic<T*> _writing{};

		std::atomic<bool> _updated{};
		std::atomic<T*> _ready{};
	};
}