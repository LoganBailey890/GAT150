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
    nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    nc::setFilePath("../Resources");

     //std::unique_ptr<nc::Actor> actor = std::make_unique < nc::Actor>(nc::Transform{ nc::Vector2{ 400,300 } });
     //{
     //    nc::SpriteComonent* component = actor->AddComponent<nc::SpriteComonent>();
     //    component->textue = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("animation/character.png", engine->Get<nc::Render>());
     //   
     //}
     //{
     //    nc::PhisicsComponenet* component = actor->AddComponent<nc::PhisicsComponenet>();
     //   // component->ApplyForce(nc::Vector2::right * 200);

     //}
    //std::unique_ptr<nc::Actor> actor = std::make_unique <nc::Actor>(nc::Transform{ nc::Vector2{200, 300}, 0, 5});
    //{
    //    //auto component = nc::ObjectFactory::Instance().Create<nc::SpriteComponent>("SpriteComponent");
    //    //component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("kim.png", engine->Get<nc::Render>());
    //    //actor->AddComponent(std::move(component));


    //    nc::SpriteAnimationComponent* component = actor->AddComponent<nc::SpriteAnimationComponent>();
    //    component->texture = engine->Get<nc::ResourceSystem>()->Get<nc::Texture>("character.png", engine->Get<nc::Render>());
    //    component->fps = 12;
    //    component->numFramesX = 12 ;
    //    component->numFramesY = 8 ;
    //}
    //scene->AddActor(std::move(actor));

    rapidjson::Document document;
    bool success = nc::json::Load("scene.txt", document);
    scene->Read(document);
    assert(success);

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
