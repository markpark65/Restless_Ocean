#include "BuildingMap.h"

std::string BuildingMap::GetName() const {
	return "BuildingMap";
}

AttributeType BuildingMap::GetAttributeType() const {
	return AttributeType::Luminous;
}

MapType BuildingMap::GetMapType() const
{
	return MapType::BuildingMap;
}
