// Scene

// Public method implementations

bool Scene::Intersect(const Ray& ray, SurfaceInteraction* isect) const {
  return aggregate->Intersect(ray, isect);
}

bool Scene::IntersectP(const Ray& ray) const {
  return aggregate->IntersectP(ray);
}

bool Scene::IntersectTr(Ray ray, Sampler& sampler, SurfaceInteraction* isect, Spectrum* transmittance) const {
  return false;
}