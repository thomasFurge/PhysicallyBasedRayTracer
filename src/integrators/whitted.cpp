#include "whitted.h"

Spectrum WhittedIntegrator::Li(const RayDifferential& ray,
  const Scene& scene, Sampler& sampler, MemoryArena& arena, int depth) const
{
  Spectrum L(0.f);
  // Find closest ray intersection or return background radiance
  SurfaceIntersection isect;
  if (!scene.Intersect(ray, &isect)) {
    for (const auto& light : scene.lights)
      L += light->Le(ray);
    return L;
  }

  // Compute emitted and reflected light at ray intersection point
  // Initialize common variables for Whitted integrator
  Normal3f n = isect.shading.n;
  Vector3f wo = isect.wo;

  // Compute scattering functions for surface interaction
  isect.ComputeScatteringFunction(ray, arena);

  // Compute emitted light if ray hit an area light source
  L += isect.Le(wo);

  // Add contribution of each light source
  for (const auto& light : scene.lights) {
    Vector3f wi;
    Float pdf;
    VisibilityTester visibility;
    Spectrum Li = light->Sample_Li(isect, sampler.Get2D(), &wi, &pdf, &visibility);
    if (Li.IsBlack() || pdf == 0) continue;
    Spectrum f = isect.bsdf->f(wo, wi);
    if (!f.IsBlack() && visibility.Unoccluded(scene))
      L += f * Li * AbsDot(wi, n) / pdf;
  }

  if (depth + 1 < maxDepth) {
    // Trace rays for specular reflection and refraction
    L += SpecularReflect(ray, isect, scene, sampler, arena, depth);
    L += SpecularTransmit(ray, isect, scene, sampler, arena, depth);
  }

  return L;
}