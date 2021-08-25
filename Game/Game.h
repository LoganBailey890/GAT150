#pragma once
#include"Engine.h"

class Game
{
public:


public:
    void Initialize();
    void Shutdown();

    void Update();
    void Draw();

    bool IsQuit() { return quit; }

private:
   

public:
    std::unique_ptr<nc::Engine> engine;
    std::unique_ptr<nc::Scene> scene;


private:
    bool quit = false;
};

