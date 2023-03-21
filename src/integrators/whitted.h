#pragma once

#include "integrator.h"

// WhittedIntegrator

class WhittedIntegrator : public SamplerIntegrator {
public:
  // Public methods
  WhittedIntegrator(int maxDepth, std::shared_ptr<const Camera> camera,
    std::shared_ptr<Sampler> sampler)
    : SamplerIntegrator(camera, sampler), maxDepth(maxDepth) {}
  Sampler Li(const RayDifferential& ray, const Scene& scene,
    Sampler& sampler, MemoryArena& arena, int depth) const;

private:
  // Private Data
  const int maxDepth;
};
