#pragma once

#ifndef PBRT_CORE_INTEGRATOR_H
#define PBRT_CORE_INTEGRATOR_H

#include <scene.h>

namespace pbrt {

	class Integrator {
	public:
		virtual void Render(const Scene &scene) = 0;
	};


	class SamplerIntegrator :Integrator {
	public:
		SamplerIntegrator(std::shared_ptr<const Camera> camera, 
			std::shared_ptr<Sampler> sampler) :camera(camera), sampler(sampler) {
		}

		virtual void Preprocess(const pbrt::Scene& scene, Sampler& sampler);

	protected:
		std::shared_ptr<const Camera> camera;

	private:
		std::shared_ptr<Sampler> sampler;
	
	};
}

#endif
