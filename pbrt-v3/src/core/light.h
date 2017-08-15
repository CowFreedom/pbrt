#pragma once
#ifndef PBRT_CORE_LIGHT_H
#define PBRT_CORE_LIGHT_H

namespace pbrt {

	class Light {
	public:
		virtual void Preprocess(const Scene &scene);
	};

}

#endif
