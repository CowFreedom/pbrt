#pragma once
#ifndef PBRT_CORE_RNG_H
#define PBRT_CORE_RNG_H

#include<pbrt.h>

namespace pbrt {

#ifndef PBRT_HAVE_HEX_FP_CONSTANTS
	constexpr double DoubleOneMinusEpsilon = 0.99999999999999989;
	constexpr float FloatOneMinusEpsilon = 0.99999994;
#endif //PBRT_HAVE_HEX_FP_CONSTANTS
#ifdef PBRT_FLOAT_IS_DOUBLE
	constexpr Float OneMinusEpsilon = DoubleOneMinusEpsilon
#else
	constexpr Float OneMinusEpsilon = FloatoneMinusEpsilon;
#endif //PBRT_FLOAT_IS_DOUBLE

	class RNG {
	public:
		RNG() = delete;
		RNG(uint64_t sequenceIndex) {
			SetSequence(sequenceIndex);
		}
		void SetSequence(uint64_t sequenceIndex);

		uint32_t UniformUInt32();
		uint32_t UniformUInt32(uint32_t);
		Float UniformFloat() {
			//return std::min(OneMinusEpsilon, UniformUInt32() * 0x1p-32f);
		}
	};

	uint32_t RNG::UniformUInt32(uint32_t b) {
		uint32_t threshold = (~b + 1u) % b;

		while (true) {
			uint32_t r = UniformUInt32();
			if (r >= threshold)
				return r%b;
		}
	}
}
#endif