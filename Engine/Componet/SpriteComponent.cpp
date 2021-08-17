#include "SpriteComponent.h"
#include "Grapics\Render.h"
#include "Object/Actor.h"

namespace nc 
{
	void nc::SpriteComonent::Update()
	{
		//
	}

	void nc::SpriteComonent::Draw(Render* render)
	{
		render->Draw(textue, owner->transform);
	}

}
