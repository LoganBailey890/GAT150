#include "PhisicsComponent.h"
#include "Engine.h"

namespace nc
{
	void PhisicsComponenet::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
	}
	bool PhisicsComponenet::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PhisicsComponenet::Read(const rapidjson::Value& value)
	{
		return false;
	}
}