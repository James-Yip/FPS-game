#pragma once
#include <GLFW/glfw3.h>
#include <ECS.h>

#include <Components/ParticleComponent.h>

using namespace ECS;

class ParticleSystem : public EntitySystem
{
public:
	ParticleSystem() {}

	virtual ~ParticleSystem() {}

	virtual void tick(class World* world, float deltaTime) override {
		glm::vec3 CameraPos;
		world->each<PlayerComponent>([&](Entity* ent, ComponentHandle<PlayerComponent> playerCHandle) -> void {
			auto cameraCHandle = ent->get<CameraComponent>();
			CameraPos = cameraCHandle->Position;
		});

		world->each<ParticleComponent, PositionComponent>([&](
			Entity* ent,
			ComponentHandle<ParticleComponent> particleCHandle,
			ComponentHandle<PositionComponent> positionCHandle) {
			if (particleCHandle->producedParticles > particleCHandle->MAX_TOTAL_NUM)
				return;
			// Generate 10 new particule each millisecond,
			// but limit this to 16 ms (60 fps), or if you have 1 long frame (1sec),
			// newparticles will be huge and the next frame even longer.
			int newparticles = (int)(deltaTime * 1000.0 * particleCHandle->newParticlesPerMS);
			if (newparticles > (int)(16.0f * particleCHandle->newParticlesPerMS))
				newparticles = (int)(16.0f * particleCHandle->newParticlesPerMS);

			particleCHandle->producedParticles += newparticles;

			generateNewParticles(particleCHandle, positionCHandle, newparticles);
			simulateAllParticles(particleCHandle, CameraPos, deltaTime);

		});
	}

	static void simulateBlood(class World* world, glm::vec3 pos) {
		world->each<ParticleComponent, PositionComponent>([&](
			Entity* ent,
			ComponentHandle<ParticleComponent> particleCHandle,
			ComponentHandle<PositionComponent> positionCHandle) {

				positionCHandle->Position = pos;

				particleCHandle->producedParticles = 0;
				particleCHandle->maxParticles = 50;
				particleCHandle->life = 1.0f;
				particleCHandle->newParticlesPerMS = 30;
				particleCHandle->spread = 3.0f;
				particleCHandle->maindir = glm::vec3(5.0f, 0.0f, 1.0f);
				particleCHandle->color_r = 245;
				particleCHandle->color_g = 10;
				particleCHandle->color_b = 10;
				particleCHandle->color_a = 224;
		});

	}
	static void simulateSmoke(class World* world, glm::vec3 pos) {
		world->each<ParticleComponent, PositionComponent>([&](
			Entity* ent,
			ComponentHandle<ParticleComponent> particleCHandle,
			ComponentHandle<PositionComponent> positionCHandle) {

				positionCHandle->Position = pos;

				particleCHandle->producedParticles = 0;
				particleCHandle->maxParticles = 50;
				particleCHandle->life = 0.3f;
				particleCHandle->newParticlesPerMS = 50;
				particleCHandle->spread = 5.0f;
				particleCHandle->maindir = glm::vec3(5.0f, 0.0f, 5.0f);
				particleCHandle->color_r = 64;
				particleCHandle->color_g = 64;
				particleCHandle->color_b = 64;
				particleCHandle->color_a = 224;
		});

	}

private:
	/* ----------- private methods for rendering particles -----------*/
	// Finds a Particle in particleCHandle->container which isn't used yet.
	// (i.e. life < 0);
	int FindUnusedParticle(ComponentHandle<ParticleComponent> particleCHandle) {

		for (int i = particleCHandle->lastUsedParticle; i < particleCHandle->maxParticles; i++) {
			if (particleCHandle->container[i].life < 0) {
				particleCHandle->lastUsedParticle = i;
				return i;
			}
		}

		for (int i = 0; i < particleCHandle->lastUsedParticle; i++) {
			if (particleCHandle->container[i].life < 0) {
				particleCHandle->lastUsedParticle = i;
				return i;
			}
		}

		return 0; // All particles are taken, override the first one
	}

	void SortParticles(ComponentHandle<ParticleComponent> particleCHandle) {
		std::sort(&particleCHandle->container[0], &particleCHandle->container[particleCHandle->maxParticles]);
	}

	void generateNewParticles(
		ComponentHandle<ParticleComponent> particleCHandle,
		ComponentHandle<PositionComponent> positionCHandle,
		int newparticles) {
		for (int i = 0; i < newparticles; i++) {
			int particleIndex = FindUnusedParticle(particleCHandle);
			particleCHandle->container[particleIndex].life = particleCHandle->life;
			particleCHandle->container[particleIndex].pos = positionCHandle->Position;

			// Very bad way to generate a random direction; 
			// See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
			// combined with some user-controlled parameters (main direction, spread, etc)
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
			);

			particleCHandle->container[particleIndex].speed = particleCHandle->maindir + randomdir * particleCHandle->spread;


			int maxColorBiase = 10;
			particleCHandle->container[particleIndex].r = (rand() % (2*maxColorBiase) - maxColorBiase) +  particleCHandle->color_r;
			particleCHandle->container[particleIndex].g = (rand() % (2*maxColorBiase) - maxColorBiase) +  particleCHandle->color_g;
			particleCHandle->container[particleIndex].b = (rand() % (2*maxColorBiase) - maxColorBiase) +  particleCHandle->color_b;
			particleCHandle->container[particleIndex].a = (rand() % (2*maxColorBiase) - maxColorBiase) +  particleCHandle->color_a;

			particleCHandle->container[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;

		}
	}

	// Simulate all particles
	void simulateAllParticles(
		ComponentHandle<ParticleComponent> particleCHandle,
		glm::vec3 cameraPos,
		float deltaTime) {

		particleCHandle->particlesCount = 0;
		for (int i = 0; i < particleCHandle->maxParticles; i++) {

			Particle& p = particleCHandle->container[i]; // shortcut

			if (p.life > 0.0f) {

				// Decrease life
				p.life -= deltaTime;
				if (p.life > 0.0f) {

					// Simulate simple physics : gravity only, no collisions
					p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)deltaTime * 0.5f;
					p.pos += p.speed * (float)deltaTime;
					p.cameradistance = glm::length2(p.pos - cameraPos);
					//particleCHandle->container[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					particleCHandle->g_particule_position_size_data[4 * particleCHandle->particlesCount + 0] = p.pos.x;
					particleCHandle->g_particule_position_size_data[4 * particleCHandle->particlesCount + 1] = p.pos.y;
					particleCHandle->g_particule_position_size_data[4 * particleCHandle->particlesCount + 2] = p.pos.z;

					particleCHandle->g_particule_position_size_data[4 * particleCHandle->particlesCount + 3] = p.size;

					particleCHandle->g_particule_color_data[4 * particleCHandle->particlesCount + 0] = p.r;
					particleCHandle->g_particule_color_data[4 * particleCHandle->particlesCount + 1] = p.g;
					particleCHandle->g_particule_color_data[4 * particleCHandle->particlesCount + 2] = p.b;
					particleCHandle->g_particule_color_data[4 * particleCHandle->particlesCount + 3] = p.a;

				}
				else {
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -1.0f;
				}

				particleCHandle->particlesCount++;

			}
		}

		SortParticles(particleCHandle);
	}
};
