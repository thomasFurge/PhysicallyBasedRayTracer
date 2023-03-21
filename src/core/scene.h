#pragma once

// Scene 

class Scene {
public:
  // Constructor
  Scene(std::shared_ptr<Primitive> aggregate, const std::vector<std::shared_ptr<Light>>& lights) : lights(lights), aggregate(aggregate) {
    worldBound = aggregate->WorldBound();
    for (const auto& light : lights)
      light->Preprocess(*this);
  }
  
  // Public Methods
  const Bounds3f& WorldBound() const { return worldBound; }
  bool Intersect(const Ray& ray, SurfaceInteraction* isect) const;
  bool IntersectP(const Ray& ray) const;
  bool IntersectTr(Ray ray, Sampler& sampler, SurfaceInteraction* isect, Spectrum* transmittance) const;

  // Public Data
  std::vector<std::shared_ptr<Light>> lights;

private:
  std::shared_ptr<Primitive> aggregate;
  Bounds3f worldBound;
};