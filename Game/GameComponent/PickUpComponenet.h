#pragma once
#include "Componet/Component.h"
#include "Framework/EventSystem.h"

class PickUpComponent : public nc::Component
{
public:
	std::unique_ptr<Object> Clone() const { return std::make_unique<PickUpComponent>(*this); }

	void Create() override;

	void Update() override;

	~PickUpComponent();
	virtual void OnCollisionEnter(const nc::Event& event);
	virtual void OnCollisionExit(const nc::Event& event);

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;
};