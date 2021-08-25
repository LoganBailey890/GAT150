#include "Actor.h"
#include"Grapics/Render.h"
#include "Engine.h"
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

    void Actor::AddComponent(std::unique_ptr<Component> component)
    {
        component->owner = this;
        components.push_back(std::move(component));
    }

    bool Actor::Write(const rapidjson::Value& value) const
    {
        return false;
    }

    bool Actor::Read(const rapidjson::Value& value)
    {
        JSON_READ(value, tag);
        if (value.HasMember("transform"))
        {
            transform.Read(value["transform"]);
        }
        if (value.HasMember("components") && value["components"].IsArray())
        {
            for (auto& componentValue : value["components"].GetArray())
            {
                std::string type;
                JSON_READ(componentValue, type);

                auto component = ObjectFactory::Instance().Create<Component>(type);
                if (component)
                {
                    component->owner = this;
                    component->Read(componentValue);
                    AddComponent(std::move(component));
                }
            }
        }

        return true;
    }


}