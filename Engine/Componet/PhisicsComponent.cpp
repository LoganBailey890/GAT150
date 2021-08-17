#include "PhisicsComponent.h"
#include "Engine.h"

namespace nc
{
	void PhisicsComponenet::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
	}
}