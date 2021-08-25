#include "SpriteComponent.h"
#include "Grapics\Render.h"
#include "Object/Actor.h"
#include "Engine.h"

namespace nc 
{
	void nc::SpriteComponent::Update()
	{
		//
	}

	void nc::SpriteComponent::Draw(Render* render)
	{
		render->Draw(texture, owner->transform);
	}

	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string textureName;
		JSON_READ(value, textureName);
		texture = owner->scene->engine->Get<ResourceSystem>()->Get<Texture>(textureName, owner->scene->engine->Get<Render>());
		return true;
	}

}
