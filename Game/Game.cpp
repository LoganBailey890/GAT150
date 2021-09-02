#include "Game.h"
#include "GameComponent/PlayerComponent.h"
#include "GameComponent/Eenemy.h"
#include "GameComponent/PickUpComponenet.h"



void Game::Initialize()
{
    //create engine
    engine = std::make_unique<nc::Engine>();
    engine->Startup();
    engine->Get<nc::Render>()->Create("GAT150", 800, 600);
    //register classes
    REGISTER_CLASS(PlayerComponent);
    REGISTER_CLASS(EnemeyComponent);
    REGISTER_CLASS(PickUpComponent);
    //create scene
    scene = std::make_unique<nc::Scene>();
    scene->engine = engine.get();
    nc::SeedRandom(static_cast<unsigned int>(time(nullptr)));
    nc::setFilePath("../Resources");

    engine->Get<nc::EventSystem>()->Subscribe("add_score", std::bind(&Game::OnAddScore, this, std::placeholders::_1));
    engine->Get<nc::EventSystem>()->Subscribe("remove_score", std::bind(&Game::OnRemoveScore, this, std::placeholders::_1));








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
    switch (state)
    {
    case Game::eState::Reset:
        Reset();
        break;
    case Game::eState::Title:
        Title();
        break;
    case Game::eState::StartGame:
        StartGame();
        break;
    case Game::eState::StartLevel:
        StartLevel();
        break;
    case Game::eState::Level:
        Level();
        break;
    case Game::eState::PlayerDead:
        PlayerDead();
        break;
    case Game::eState::GameOver:
        GameOver();
        break;
    default:
        break;
    }
  
    //update score
    auto scoreActor = scene->FindActor("Score");
    if (scoreActor)
    {
        scoreActor->GetComponent<nc::TextComponent>()->SetText(std::to_string(score));
    }

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

void Game::Reset()
{
    scene->RemoveAllActor();
    rapidjson::Document document;
    bool success = nc::json::Load("title.txt", document);
    assert(success);
    scene->Read(document);

    state = eState::Title;
}

void Game::Title()
{
    if (engine->Get<nc::InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == nc::InputSystem::eKeyState::Pressed)
    {
        auto title = scene->FindActor("Title");
        assert(title);
        title->active = false;
        state = eState::StartGame;
    }
}

void Game::StartGame()
{
    
    rapidjson::Document document;
    bool success = nc::json::Load("scene.txt", document);
    assert(success);
    scene->Read(document);

    nc::Tilemap tilemap;
    tilemap.scene = scene.get();
    success = nc::json::Load("map.txt", document);
    assert(success);
    tilemap.Read(document);
    tilemap.Create();

    state = eState::StartLevel;
}

void Game::StartLevel()
{
    statetimer += engine->time.deltaTime;
    if (statetimer >= 1)
    {
        auto player = nc::ObjectFactory::Instance().Create<nc::Actor>("Player");
        player->transform.position = nc::Vector2{ 400,200 };
        scene->AddActor(std::move(player));

        spawnTimer = 2;
        enemySpawnTimer = 5;
        maxEnemyAllowed = 3;
        state = eState::Level;
    }
}

void Game::Level()
{
    spawnTimer -= engine->time.deltaTime;
    enemySpawnTimer -= engine->time.deltaTime;
    if (spawnTimer <= 0)
    {
        spawnTimer = nc::RandomRange(2, 4);
        auto coin = nc::ObjectFactory::Instance().Create<nc::Actor>("coins");
        coin->transform.position = nc::Vector2{ nc::RandomRange(0,800), nc::RandomRange(150,500) };
        scene->AddActor(std::move(coin));
    }
    
    if (enemySpawnTimer <= 0 && maxEnemyAllowed >=0)
    {
        auto enemy = nc::ObjectFactory::Instance().Create<nc::Actor>("bat");
        enemy->transform.position = nc::Vector2{ nc::RandomRange(0,800), nc::RandomRange(0,800) };
        scene->AddActor(std::move(enemy));
        enemySpawnTimer = 8;
        maxEnemyAllowed = maxEnemyAllowed - 1;
    }
    //if (score >= 200 || score < 0)
    //{
    //    state = eState::GameOver;
    //}
}



void Game::PlayerDead()
{
}

void Game::GameOver()
{
    state = eState::Reset;
}

void Game::OnAddScore(const nc::Event& event)
{
   score += std::get<int>(event.data);

}

void Game::OnRemoveScore(const nc::Event& event)
{
    score -= std::get<int>(event.data);
}
