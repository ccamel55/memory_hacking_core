#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace CORE {

	template<typename T>
	class C_TrippleBuffer {
	public:
		C_TrippleBuffer() {
			m_aBuffers;
			m_cReadQueueMutex;
			m_cReadQueue;

			m_pReadBuffer = &m_aBuffers[0];
			m_pWriteBuffer = &m_aBuffers[1];

			m_pAvaliableBuffer = &m_aBuffers[2];
			m_pNextReadBuffer = NULL;
		}

		~C_TrippleBuffer() {

		}

		T* getWriteBuffer() {
			return m_pWriteBuffer;
		}

		void setWriteComplete() {

			// give back the write buffer
			auto written = m_pWriteBuffer;
			m_pWriteBuffer = m_pAvaliableBuffer.exchange(m_pWriteBuffer);

			// mark it as written
			m_pNextReadBuffer.store(written, std::memory_order_release);

			// notify any waiting reader
			m_cReadQueue.notify_one();
		}

		T* getReadBuffer(std::chrono::milliseconds timeout = std::chrono::milliseconds(500)) {

			const auto timeout_time = std::chrono::steady_clock::now() + timeout;

			// get the written buffer, waiting if necessary
			auto b = m_pNextReadBuffer.exchange(nullptr);

			while (b != m_pReadBuffer) {

				// it could be the available buffer
				m_pReadBuffer = m_pAvaliableBuffer.exchange(m_pReadBuffer);

				if (b == m_pReadBuffer) {
					// yes, that's it
					return m_pReadBuffer;
				}

				// else we need to wait for writer
				b = nullptr;
				std::unique_lock lock{ m_cReadQueueMutex };

				auto test = [this, &b] { b = m_pNextReadBuffer.exchange(nullptr); return b; };

				if (!m_cReadQueue.wait_until(lock, timeout_time, test)) {
					return nullptr;
				}
			}

			return m_pReadBuffer;
		}

	private:
		T m_aBuffers[3];

		// pointers to read write and avaliable buffer
		T* m_pReadBuffer;
		T* m_pWriteBuffer;

		std::atomic<T*> m_pAvaliableBuffer;
		std::atomic<T*> m_pNextReadBuffer;

		std::mutex m_cReadQueueMutex;
		std::condition_variable m_cReadQueue;
	};
}