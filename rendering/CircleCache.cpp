#include "CircleCache.hpp"

#include <cmath>

using namespace CORE;

void C_CircleCache::cache() {

	// build lookup circle
	for (size_t i = 0; i <= CIRCLE_SEGMENTS; i++) {

		_circleLookup.at(i)._cos = std::cos(6.283185f * (i / static_cast<float>(CIRCLE_SEGMENTS)));
		_circleLookup.at(i)._sin = std::sin(6.283185f * (i / static_cast<float>(CIRCLE_SEGMENTS)));
	}
}

const T_CircleCache& C_CircleCache::getLookup(size_t idx) const {
	return _circleLookup.at(idx);
}