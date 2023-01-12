#pragma once

namespace CORE {

	class C_Bitflag {
	public:
		__forceinline void set_flag(uint32_t flag) {
			_flags |= flag;
		}

		__forceinline void remove_flag(uint32_t flag) {
			_flags &= ~flag;
		}

		__forceinline bool has_flags(uint32_t flag) {
			return _flags & flag;
		}

	private:
#if _WIN32
		uint32_t _flags{};
#else
		uint64_t _flags{};
#endif
	};
}