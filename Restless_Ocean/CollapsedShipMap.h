#pragma once
#include "IMap.h"

class CollapsedShipMap : public IMap {
public:
	std::string GetName() const override;
	AttributeType GetAttributeType() const override;
};
