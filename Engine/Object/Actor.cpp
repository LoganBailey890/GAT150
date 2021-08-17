#include "Actor.h"
#include"Grapics/Render.h"
#include "Componet/GraphicsComponent.h"
#include<algorithm>


namespace nc
{
    void nc::Actor::Update(float dt)
    {
  
        std::for_each(components.begin(), components.end(), [](auto& component)
        { 
            component->Update(); 
        });

        transform.Update();
        std::for_each(children.begin(), children.end(), [](auto& child) {child->transform.Update(child->parent->transform.matrix); });
    }

    void nc::Actor::Draw(Render* render)
    {
        std::for_each(components.begin(), components.end(), [render](auto& component)
        {
            if (dynamic_cast<GraphicsComponent*>(component.get()))
            {
                dynamic_cast<GraphicsComponent*>(component.get())->Draw(render);
            }
        });
       std::for_each(children.begin(), children.end(), [render](auto& child) {child->Draw(render); });
    }
    void nc::Actor::AddChild(std::unique_ptr<Actor> actor)
    {
        actor->parent = this;
        children.push_back(std::move(actor));
    }
    float nc::Actor::GetRadius()
    {
        //return std::max(texture->Getsize().x,texture->Getsize().y) * 0.5f;
        return 0;// (texture) ? texture->Getsize().Length() * 0.5f * transform.scale.x : 0;
    }

    void nc::Actor::AddComponent(std::unique_ptr<Component> component)
    {
        component->owner =this;
        components.push_back(std::move(component));
    }
}