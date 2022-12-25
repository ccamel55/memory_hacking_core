#pragma once

#include <array>

#include "../singleton.hpp"

namespace CORE {

	constexpr size_t CIRCLE_SEGMENTS = 64;

	struct T_CircleCache {
		float _cos{};
		float _sin{};
	};

	class C_CircleCache : public Singleton<C_CircleCache> {
	public:
		void cache();
		const T_CircleCache& getLookup(size_t idx) const;
	private:
		std::array<T_CircleCache, CIRCLE_SEGMENTS + 1> _circleLookup{};
	};
}