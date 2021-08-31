#include "Eenemy.h"
#include "Engine.h"

using namespace nc;

void EnemeyComponent::Update()
{
	Actor* player = owner->scene->FindActor("Player");
	if (player)
	{

		Vector2 direction = player->transform.position - owner->transform.position;
		Vector2 force = direction.Normalized() * speed;

		PhisicsComponenet* physicsComponent = owner->GetComponent<PhisicsComponenet>();
		assert(physicsComponent);

		physicsComponent->ApplyForce(force);

	}

}

bool EnemeyComponent::Write(const rapidjson::Value& value) const
{
	return false;
}

bool EnemeyComponent::Read(const rapidjson::Value& value)
{
	JSON_READ(value, speed);
	return true;
}