#include"Player.h"
#include"Projectile.h"
#include"Engine.h"
#include"Enemy.h"
#include"Enemy2.h"
#include"Math/MathUtilis.h"
#include<memory>



Player::Player(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform , texture }, speed{ speed }
{

}
void Player::Initialize()
{
    //std::unique_ptr locator = std::make_unique<actor>();
    //locator->transform.localposition = nc::vector2{ -8,0 };
    //locator->transform.localrotation = nc::pi;
    //addchild(std::move(locator));

    //locator = std::make_unique<actor>();
    //locator->transform.localposition = nc::vector2{ 0, 5 };
    //addchild(std::move(locator));

    //locator = std::make_unique<actor>();
    //locator->transform.localposition = nc::vector2{ 0, -5 };
    //addchild(std::move(locator));

}
void Player::Update(float dt)
{
    Actor::Update(dt);

    //children[3]->transform.localrotation += 5 * dt;

    //movement
    float thrust = 0;
    if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_A) == nc::InputSystem::eKeyState::Held) transform.rotation -= 5 * dt;
    if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_D) == nc::InputSystem::eKeyState::Held) transform.rotation += 5 * dt;
    if (scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_W) == nc::InputSystem::eKeyState::Held) thrust = speed;

    nc::Vector2 accelration;
    accelration += nc::Vector2::Rotate(nc::Vector2::right, transform.rotation) * thrust;
    nc::Vector2 gravity = (nc::Vector2{ 100,80 } - transform.position).Normalized() * 10;
    //nc::Vector2 gravity = (nc::Vector2::down * 50);
    accelration += gravity;

    velocity += accelration * dt;
    transform.position += velocity * dt;

    velocity *= 0.985f;

    transform.position.x = nc::Wrap(transform.position.x, 0.0f, 800.0f);
    transform.position.y = nc::Wrap(transform.position.y, 0.0f, 600.0f);

    //fire
    fireTimer -= dt;
    if (fireTimer <= 0 && scene->engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
    {
        fireTimer = fireRate;

        //nc::Transform t = children[1]->transform;
        //t.scale = 1.0f;


        /*std::vector<nc::Vector2> points = { {-5,-5}, {5,-5}, {0,10}, {-5,-5} };
        std::shared_ptr <nc::Shape> shape1 = std::make_shared<nc::Shape>(points, nc::Color{ 0 , 1 ,0 });*/
        nc::Transform t = transform;
        t.scale = 0.2f;
        std::unique_ptr<Projectile> projectile = std::make_unique <Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Bullet.png", scene->engine->Get<nc::Render>()), 600.0f);
        std::shared_ptr<nc::Texture> bullet = scene->engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Bullet.png", scene->engine->Get<nc::Render>());
       


        //std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<nc::ResourceSystem>()->Get<nc::Shape>("Player.txt"), 600.0f);
        projectile->tag = "Player";
        scene->AddActor(std::make_unique <Projectile>(t, bullet, 600.0f));
        scene->AddActor(std::move(projectile));
        scene->engine->Get<nc::AudioSystem>()->PlayAudio("player_fire");

    }

    std::vector<nc::Color> colors = { nc::Color::white, nc::Color::cyan, nc::Color::purple };
    //scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, 50, transform.rotation,nc::DegToRad(30));


}
void Player::OnCollision(Actor* actor)
{
   
    if (dynamic_cast<Enemy*>(actor) || actor->tag == "Enemy" || dynamic_cast<Enemy2*>(actor))
    {
       
      destroy = true;
      actor->destroy = true;

      //scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 200, 1, nc::Color::red, 50);
      scene->engine->Get<nc::AudioSystem>()->PlayAudio("player_explosion");

       nc::Event event;
       event.name = "PlayerDead";
       scene->engine->Get<nc::EventSystem>()->Notify(event);
    }
}