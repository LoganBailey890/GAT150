#include "Game.h"



void Game::Initialize()
{
    //create engine
    engine = std::make_unique<nc::Engine>(); 
    engine->Startup();
    engine->Get<nc::Render>()->Create("GAT150", 800, 600);
    //create scene
    scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();
    nc::setFilePath("../Resources");
    nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));

     std::unique_ptr<nc::Actor> actor = std::make_unique < nc::Actor>(nc::Transform{ nc::Vector2{ 400,300 } });
     {
         std::unique_ptr<nc::SpriteComonent> component = std::make_unique<nc::SpriteComonent>();
         component->textue = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("kim.png", engine->Get<nc::Render>());
         actor->AddComponent(std::move(component));
        
     }
     {
         std::unique_ptr<nc::PhisicsComponenet> component = std::make_unique<nc::PhisicsComponenet>();
         component->ApplyForce(nc::Vector2::right * 200);
         actor->AddComponent(std::move(component));
     }
     scene->AddActor(std::move(actor));

}

void Game::Shutdown()
{
    scene->RemoveAllActor();
    engine->Shutdown();
}

void Game::Update()
{
    engine->Update();
    quit = (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eKeyState::Pressed);
  


    scene->Update(engine->time.deltaTime);
}

void Game::Draw()
{
    
    //draw
    engine->Get<nc::Render>()->BeginFrame();
    scene->Draw(engine->Get<nc::Render>());
    engine->Draw(engine->Get<nc::Render>());

    engine->Get<nc::Render>()->EndFrame();
}
