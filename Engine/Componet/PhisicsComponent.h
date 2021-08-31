#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhisicsComponenet :public Component
	{
	public:
		std::unique_ptr<Object> Clone() const { return std::make_unique<PhisicsComponenet>(*this); }

		void Update() override;
		virtual void ApplyForce(const Vector2& force) { acceleration += force; }
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
	public:
		Vector2 velocity;
		Vector2 force;
		Vector2 acceleration;
		float damping{ 1 };

		// Inherited via Component
	};
}