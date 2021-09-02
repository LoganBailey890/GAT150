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
		render->Draw(texture, rect, owner->transform);
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
		JSON_READ(value, rect);
		if (rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h ==0)
		{
			Vector2 size = texture->Getsize();
			rect.w = static_cast<int>(size.x);
			rect.h = static_cast<int>(size.y);
		}
		return true;
	}

}
