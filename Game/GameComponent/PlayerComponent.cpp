#include "PlayerComponent.h"
#include "Engine.h"

using namespace nc;

void PlayerComponent::Create()
{
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_enter",std::bind(&PlayerComponent::OnCollisionEnter,this,std::placeholders::_1),owner);
	owner->scene->engine->Get<EventSystem>()->Subscribe("collision_exit",std::bind(&PlayerComponent::OnCollisionExit,this,std::placeholders::_1),owner);

	owner->scene->engine->Get<AudioSystem>()->AddAudio("hurt", "Audio/hurt.wav");
	
}

void PlayerComponent::Update()
{

	Vector2 force = Vector2::zero;
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_A) == InputSystem::eKeyState::Held)
	{
		force.x -= speed;
	}
	if (owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_D) == InputSystem::eKeyState::Held)
	{
		force.x += speed;
	}
	if (contacts.size() > 0 && owner->scene->engine->Get<InputSystem>()->GetKeyState(SDL_SCANCODE_SPACE) == InputSystem::eKeyState::Pressed)
	{
		force.y -= 200;
	}

	PhisicsComponenet* physicsComponent = owner->GetComponent<PhisicsComponenet>();
	assert(physicsComponent);

	physicsComponent->ApplyForce(force);

	SpriteAnimationComponent* spriteAnimationComponent = owner->GetComponent<SpriteAnimationComponent>();
	assert(spriteAnimationComponent);

	if (physicsComponent->velocity.x > 0) spriteAnimationComponent->SetSequence("walk_right");
	else if (physicsComponent->velocity.x < 0) spriteAnimationComponent->SetSequence("walk_left");
	else spriteAnimationComponent->SetSequence("idel");
}

PlayerComponent::~PlayerComponent()
{
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_enter", owner);
	owner->scene->engine->Get<EventSystem>()->Unsubscribe("collision_exit", owner);
}

void PlayerComponent::OnCollisionEnter(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);
	if (istring_compare(actor->tag, "ground"))
	{
		contacts.push_back(actor);
	}
	

	/*std::cout << actor->tag << std::endl;*/
}

void PlayerComponent::OnCollisionExit(const Event& event)
{
	void* p = std::get<void*>(event.data);
	Actor* actor = reinterpret_cast<Actor*>(p);
	if (istring_compare(actor->tag, "ground"))
	{
		contacts.remove(actor);
	}
	if (istring_compare(actor->tag, "Enemy"))
	{
		owner->scene->engine->Get<AudioSystem>()->PlayAudio("hurt");
	}
}

bool PlayerComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool PlayerComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}

