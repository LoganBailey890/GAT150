#pragma once
#include "Core/Serializable.h"
#include "Object/Object.h"
#include <vector>
namespace nc
{
	class Tilemap : public Object, public ISerializable
	{
	public:

		void Create() override;
		
		virtual bool Write(const rapidjson::Value& value) const override;

		virtual bool Read(const rapidjson::Value& value) override;

	public:
		class Scene* scene = nullptr;

		int numTilesX{ 0 };
		int numTilesy{ 0 };

		Vector2 size;
		Vector2 start;
		std::vector<std::string> tileNames;
		std::vector<int> tiles;

	};
}