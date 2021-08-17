#pragma once
#include"Object/Actor.h"


class Enemy2 : public nc::Actor
{
public:
    Enemy2(const nc::Transform& transform, std::shared_ptr<nc::Texture> texture, float speed) : nc::Actor{ transform , texture }, speed{ speed }  {}

    void Update(float dt) override;
    void OnCollision(Actor* actor) override;

private:
    float speed = 300;
 
};