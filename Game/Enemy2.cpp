#include "Enemy2.h"
#include"Projectile.h"
#include"Player.h"
#include"Engine.h"

void Enemy2::Update(float dt)
{
    Actor::Update(dt);

    if (scene->GetActor<Player>())
    {
        nc::Vector2 direction = scene->GetActor<Player>()->transform.position - transform.position;
        nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);

        //float turnAngle = nc::Vector2::SignedAngle(forward, direction.Normalized());
        //transform.rotation = transform.rotation + turnAngle * (3 * dt);
        //transform.rotation = nc::Lerp(transform.rotation, transform.rotation + turnAngle, direction.Angle(), 2 * dt);

        float angle = nc::Vector2::Angle(forward, direction.Normalized());

        //fireTimer -= dt;
        //if (fireTimer <= 0 && angle <= nc::DegToRad(10))
        //{
        //    fireTimer = fireRate;
        //    /*std::vector<nc::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
        //    std::shared_ptr <nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 0 , 1 ,0 });*/
        //    nc::Transform t = transform;
        //    t.scale = 0.5f;

        //    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Player.txt"), 600.0f);
        //    projectile->tag = "Enemy";
        //    scene->AddActor(std::move(projectile));

        //    //scene->AddActor(std::make_unique <Projectile>(t, shape, 600.0f));

        //    scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemy_fire");

        //}


        //transform.rotation = direction.Angle();
    }

    transform.position += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * speed * dt;
    transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
    transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);


}

void Enemy2::OnCollision(Actor* actor)
{
    if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player")
    {
        destroy = true;
        actor->destroy = true;

        //std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::yellow };
        //scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::red, 50);
        scene->engine->Get<nc::AudioSystem>()->PlayAudio("enemy_explosion");

        nc::Event event;
        event.name = "AddPoints";
        //event.data = 300;
        scene->engine->Get<nc::EventSystem>()->Notify(event);
    }
}
