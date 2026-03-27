#include "MapUtils.h"

std::string GetMapName(MapType mapType)
{
	switch (mapType)
	{
	case MapType::BuildingMap:
		return "침몰된 도시";
	case MapType::SeaCaveMap:
		return "해저 동굴";
	case MapType::CollapsedShipMap:
		return "난파선";
	default:
		return "알 수 없는 맵";
	}
}

AttributeType GetMapAttributeType(MapType mapType)
{
	switch (mapType)
	{
	case MapType::BuildingMap:
		return AttributeType::Giant;
	case MapType::SeaCaveMap:
		return AttributeType::Hidden;
	case MapType::CollapsedShipMap:
		return AttributeType::Luminous;
	default:
		return AttributeType::Hidden;
	}
}

//map enum class에서 사용하는 utils입니다.
