#pragma once

namespace CORE {

#if _WIN32
	using bit_flag_t = uint32_t;
#else
	using bit_flag_t = uint64_t;
#endif

	class BIT_FLAG {
	public:
		__forceinline void setFlag(bit_flag_t flag) {
			_flags |= flag;
		}

		__forceinline void removeFlag(bit_flag_t flag) {
			_flags &= ~flag;
		}

		__forceinline bool hasFlag(bit_flag_t flag) {
			return _flags & flag;
		}

		__forceinline void toggleFlag(bit_flag_t flag) {
			_flags ^= flag;
		}

	private:
		bit_flag_t _flags{};
	};
}