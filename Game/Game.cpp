#include "Game.h"
#include "Player.h"
#include "Enemy2.h"
#include "Enemy.h"


void Game::Initialize()
{
    //create engine
    engine = std::make_unique<nc::Engine>(); 
    engine->Startup();
    engine->Get<nc::Render>()->Create("GAT150", 800, 600);
    nc::setFilePath("../Resources");
    //create scene
    scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();

   nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));

    engine->Get<nc::AudioSystem>()->AddAudio("explosion", "audio/explosion.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("BKM", "audio/BackGround.mp3");
    nc::AudioChannel musicChannel = engine->Get<nc::AudioSystem>()->PlayAudio("BKM", 1, 4, true);
   

    //std::shared_ptr<nc::Texture> texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("kim.png", engine->Get<nc::Render>());
    particleTexture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Boom.png", engine->Get<nc::Render>());

   /* for (size_t i = 0; i < 10; i++)
    {
        nc::Transform transform{ nc::Vector2{nc::RandomRange(0,800),nc::RandomRange(0,600) }, nc::RandomRange(0,360), 1.0f };
        std::unique_ptr<nc::Actor> actor = std::make_unique<nc::Actor>(transform, texture);

        scene->AddActor(std::move(actor));

    }*/

    //Text


    //game
    engine->Get<nc::AudioSystem>()->AddAudio("player_fire", "audio/PlayerShots.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("player_explosion", "audio/PlayerExlosion.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("enemy_fire", "audio/EnemyShot.wav");
    engine->Get<nc::AudioSystem>()->AddAudio("enemy_explosion", "audio/EnemyExlosion.wav");

    engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
    engine->Get<nc::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
    scene->RemoveAllActor();
    engine->Shutdown();
}

void Game::Update()
{
    engine->Update();
    float dt = engine->time.deltaTime;
    stateTimer += dt;

    //(this->*stateFunction)(dt);
   

    switch (state)
    {
    case Game::eState::TitleScreen:
        if ((engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed))
        {
            state = eState::StartGame;
            //std::cout << "START GAME \n";
        }
        break;
    case Game::eState::StartGame:
        score = 0;
        lives = 1;
        state = eState::StartLevel;
        break;
    case Game::eState::StartLevel:
        UpdateLevelStart(dt);
        state = eState::Game;
        break;
    case Game::eState::Game:
        if (scene->GetActors<Enemy>().size() == 0)
        {
            if (scene->GetActors<Enemy2>().size() == 0)
            {
               state = eState::Gameover;
            }
        }
        break;
    case Game::eState::Gameover:
        scene->RemoveAllActor();
        if ((engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed))
        {
            state = eState::TitleScreen;
        }
        break;
    default:
        break;
    }



    quit = (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed);
  

    //if (engine->Get<nc::InputSystem>()->GetButtonState((int)nc::InputSystem::eMouseButton::right) == nc::InputSystem::eKeyState::Pressed)
    //{
    //    nc::Vector2 position = engine->Get<nc::InputSystem>()->GetMousePosition();
    //    engine->Get<nc::ParticleSystem>()->Create({ position.x,position.y }, 10, particleTexture, 2, 25);
    //    engine->Get<nc::AudioSystem>()->PlayAudio("explosion", 1, nc::RandomRange(0.2f, 2.0f));
    //    musicChannel.SetPitch(nc::RandomRange(-0.2f, 5.0f));
    //    //channel.Stop();
    //    std::cout << position.x << " " << position.y << std::endl;

    //}

    scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
    int size = 25;
    std::shared_ptr<nc::Font> font = engine->Get<nc::ResourceSystem>()->Get<nc::Font>("fonts/SEVESBRG.ttf", &size);
    textTexture = std::make_shared<nc::Texture>(engine->Get<nc::Render>());
    engine->Get<nc::ResourceSystem>()->Add("textTexture", textTexture);

    switch (state)
    {
    case Game::eState::TitleScreen:
        textTexture->Create(font->CreateSurface("Space fighter", nc::Color{ 1,1,1 }));
        break;
    case Game::eState::StartGame:

        break;
    case Game::eState::StartLevel:
        break;
    case Game::eState::Game:
        break;
    case Game::eState::Gameover:
        textTexture->Create(font->CreateSurface("Presse space to restart", nc::Color{ 1,1,1 }));
        break;
    default:
        break;
    }
    //draw
    engine->Get<nc::Render>()->BeginFrame();
    scene->Draw(engine->Get<nc::Render>());
    engine->Draw(engine->Get<nc::Render>());
    nc::Transform t;
    t.position = { 150,150 };
    engine->Get<nc::Render>()->Draw(textTexture, t);



    engine->Get<nc::Render>()->EndFrame();
}
void Game::UpdateTitle(float dt)
{

}

void Game::UpdateLevelStart(float dt)
{
    scene->AddActor(std::make_unique<Player>(nc::Transform{ nc::Vector2{400, 300}, 0,2}, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("Player.png", engine->Get<nc::Render>()), 350.0f));
    for (size_t i = 0; i < 2 ; i++)
    {
        scene->AddActor(std::make_unique<Enemy>(nc::Transform{ nc::Vector2{ nc::RandomRange(0.0f,800), nc::RandomRange(0.0f,600)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("player.png", engine->Get<nc::Render>()), 100.0f));
    }

    for (size_t i = 0; i < 4; i++)
    {
        scene->AddActor(std::make_unique<Enemy2>(nc::Transform{ nc::Vector2{ nc::RandomRange(0.0f,800), nc::RandomRange(0.0f,600)}, nc::RandomRange(0, nc::TwoPi), 2 }, engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("rock.png", engine->Get<nc::Render>()), 100.0f));
        
    }
    state = eState::Game;

}

void Game::OnAddPoints(const nc::Event& event)
{
    //score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const nc::Event& event)
{
    lives--;
   // std::cout << std::get<std::string>(event.data) << std::endl;
    state = eState::Gameover;
}