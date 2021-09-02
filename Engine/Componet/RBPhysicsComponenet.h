#pragma once
#include "PhisicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace nc
{
	class RBPhysicsComponent : public PhisicsComponenet
	{

	public:
		RBPhysicsComponent() = default;
		RBPhysicsComponent(const RBPhysicsComponent & other);
		std::unique_ptr<Object> Clone() const { return std::make_unique<RBPhysicsComponent>(*this); }

		virtual ~RBPhysicsComponent();
		void Update() override;
		void ApplyForce(const Vector2& force) override;
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		PhysicsSystem::RigidBodyData data;
		b2Body* body{ nullptr };

	};
}