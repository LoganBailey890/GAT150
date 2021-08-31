#include "PickUpComponenet.h"
#include"Engine.h"

using namespace nc;

void PickUpComponent::Create()
{
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter", std::bind(&PickUpComponent::OnCollisionEnter, this, std::placeholders::_1), owner);
    owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit", std::bind(&PickUpComponent::OnCollisionExit, this, std::placeholders::_1), owner);

    owner->scene->engine->Get<AudioSystem>()->AddAudio("coins", "Audio/coin.wav");
}

void PickUpComponent::Update()
{
    Vector2 force = Vector2::zero;

    PhisicsComponenet* physicsComponent = owner->GetComponent<PhisicsComponenet>();
    assert(physicsComponent);
    physicsComponent->ApplyForce(force);
}

PickUpComponent::~PickUpComponent()
{

}

void PickUpComponent::OnCollisionEnter(const nc::Event& event)
{
    void* p = std::get<void*>(event.data);
    Actor* actor = reinterpret_cast<Actor*>(p);

    if (istring_compare(actor->name, "Player"))
    {
        owner->scene->engine->Get<AudioSystem>()->PlayAudio("coins");
        owner->destroy = true;
    }
}

void PickUpComponent::OnCollisionExit(const nc::Event& event)
{

}

bool PickUpComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool PickUpComponent::Read(const rapidjson::Value& value)
{
    return true;
}