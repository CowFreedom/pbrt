#pragma once

#ifndef PBRT_CORE_SCENE_H
#define PBRT_CORE_SCENE_H

#include <pbrt.h>
#include <light.h>
#include <primitive.h>

namespace pbrt {

	class Scene {
	public:
		//Scene Public Methods
		Scene(std::shared_ptr<Primitive> aggregate,
			const std::vector<std::shared_ptr<Light>> &lights)
			: lights(lights), aggregate(aggregate) {

			worldBound = aggregate->WorldBound();

			for (const auto& light : lights)
				light->Preprocess(*this);			
		}

		bool Scene::Intersect(const Ray &ray, SurfaceInteraction *isect) const;

		bool IntersectP(const Ray &ray) const;

	private:
		std::vector<std::shared_ptr<Light>> lights;
		std::shared_ptr<Primitive> aggregate;
		Bounds3f worldBound;
	};

}


#endif // !PBRT_CORE_SCENE_H
