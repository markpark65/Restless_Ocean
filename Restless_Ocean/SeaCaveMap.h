#pragma once
#include "IMap.h"

class SeaCaveMap : public IMap {
public:
	std::string GetName() const override;
	AttributeType GetAttributeType() const override;
};
