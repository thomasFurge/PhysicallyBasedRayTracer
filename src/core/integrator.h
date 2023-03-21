// Integrator

class Integrator {
public:
  virtual ~Integrator();
  virtual void Render(const Scene& scene) = 0;
};

class SampleIntegrator : public Integrator {
public:
  // Constructor
  SamplerIntegrator(std::shared_ptr<const Camera> camera,
    std::shared_ptr<Sampler> sampler)
    : camera(camera), sampler(sampler) {}

  // Public methods
  virtual void Preprocess(const Scene& scene, Sampler& sampler) {}
  void Render(const Scene& scene);
  virtual Spectrum Li(const RayDifferential& ray, const Scene& scene,
    Sampler& sampler, MemoryArena& arena, int depth = 0) const = 0;
  Spectrum SpecularReflect(const RayDifferential& ray,
    const SurfaceInteraction& isect, const Scene& scene, Sampler& sampler,
    MemoryArena& arena, int depth) const;
  Spectrum SpecularTransmit(const RayDifferential& ray,
    const SurfaceInteraction& isect, const Scene& scene, Sampler& sampler,
    MemoryArena& arena, int depth) const;

protected:
  // Protected Data
  std::shared_ptr<const Camera> camera;

private:
  // Private Data
  std::shared_ptr<Sampler> sampler;
};
