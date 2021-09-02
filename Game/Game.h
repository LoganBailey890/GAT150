#pragma once
#include"Engine.h"

class Game
{
public:
    enum class eState
    {
        Reset,
        Title,
        StartGame,
        StartLevel,
        Level,
        PlayerDead,
        GameOver
    };


public:
    void Initialize();
    void Shutdown();

    void Update();
    void Draw();

    bool IsQuit() { return quit; }

private:
    void Reset();
    void Title();
    void StartGame();
    void StartLevel();
    void Level();
    void PlayerDead();
    void GameOver();

    void OnAddScore(const nc::Event& event);
    void OnRemoveScore(const nc::Event& event);
   

public:
    std::unique_ptr<nc::Engine> engine;
    std::unique_ptr<nc::Scene> scene;


private:
    bool quit = false;

    eState state = eState::Reset;
    float statetimer = 0;
    int score = 0;
    float spawnTimer = 0;
    float enemySpawnTimer = 0;
    int maxEnemyAllowed = 0;
};

