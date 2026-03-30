#include "SeaCaveMap.h"

std::string SeaCaveMap::GetName() const {
	return "SeaCave";
}

AttributeType SeaCaveMap::GetAttributeType() const{
	return AttributeType::Hidden;
}


MapType SeaCaveMap::GetMapType() const
{
	return MapType::SeaCaveMap;
}
