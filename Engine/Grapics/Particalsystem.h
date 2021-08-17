#pragma once
#include"Math/Vector2.h"
#include"Framework/System.h"
#include<vector>
namespace nc
{
    class Render;
    class Texture;
    struct Particle
    {
        Vector2 position;
        Vector2 prevPosition;
        Vector2 velocity;
        std::shared_ptr<Texture> texture;
        float lifetime;
        bool isActive{ false };

        static bool IsNotActive(Particle particle) { return particle.isActive == false; }
    };
       

    class ParticleSystem : public GraphicsSystem
    {
    public:
        void Startup() override;
        void Shutdown() override;

        void Update(float dt) override;
        void Draw(Render* render) override;

        void Create(Vector2 position, size_t count, std::shared_ptr<Texture> texture, float lifetime,float speed);
        void Create(Vector2 position, size_t count, float lifetime,float speed, std::shared_ptr<Texture> texture,float angle,float angleRange);

    private:
        std::vector<Particle> particle;
    };
}
