#include "Particalsystem.h"
#include "../Math/Random.h"
#include "Grapics/Texture.h"
#include"Render.h"
namespace nc
{
    void ParticleSystem::Startup()
    {
        particle.resize(1000);
    }

    void ParticleSystem::Shutdown()
    {
        particle.clear();
    }

    void ParticleSystem::Update(float dt)
    {
        for (Particle& particle : particle)
        {
            if (particle.isActive)
            {
                particle.lifetime -= dt;
                particle.isActive = particle.lifetime > 0;
                particle.prevPosition = particle.position;
                particle.position += particle.velocity * dt;

            }
        }


    }

    void ParticleSystem::Draw(Render* render)
    {
        for (const Particle& particle : particle)
        {
            if (particle.isActive)
            {
                render->Draw(particle.texture,particle.position);
            }
        }
    }

    void ParticleSystem::Create(Vector2 position, size_t count, std::shared_ptr<Texture> texture,float lifetime, float speed)
    {
        for (size_t i = 0; i < count; i++)
        {
            auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
            if (particles != particle.end())
            {
                particles->isActive = true;
                particles->lifetime = lifetime;
                particles->position = position;
                particles->prevPosition = position;
                particles->texture = texture;
               //particles->color = color;

                particles->velocity = Vector2{ RandomRange(-1, 1), RandomRange(-1, 1) } *(speed * Random());
            }
        }
    }
    void ParticleSystem::Create(Vector2 position, size_t count, float lifetime, float speed, std::shared_ptr<Texture> texture, float angle, float angleRange)
    {
        for (size_t i = 0; i < count; i++)
        {
            auto particles = std::find_if(particle.begin(), particle.end(), Particle::IsNotActive);
            if (particles != particle.end())
            {
                particles->isActive = true;
                particles->lifetime = lifetime;
                particles->position = position;
                particles->prevPosition = position;
                particles->texture = texture;
                //particles->color = colors[rand() % colors.size()];

                particles->velocity = nc::Vector2::Rotate(nc::Vector2::right, angle + nc::RandomRange(-angleRange, angleRange)) * (speed * Random());
            }
        }
    }
}