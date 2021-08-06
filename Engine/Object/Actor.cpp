#include "Actor.h"
#include"Grapics/Render.h"
#include<algorithm>

void nc::Actor::Update(float dt)
{
    transform.rotation += 50;

    transform.Update();
    std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
}

void nc::Actor::Draw(Render* render)
{
    render->Draw(texture, transform);
}
void nc::Actor::AddChild(std::unique_ptr<Actor> actor)
{
    actor->parent = this;
    children.push_back(std::move(actor));
}
float nc::Actor::GetRadius()
{
    return std::max(texture->Getsize().x,texture->Getsize().y) * 0.5f;
}
