#include "IMap.h"

class BuildingMap : public IMap {
public:
	std::string GetName() const override;
	AttributeType GetAttributeType() const override;
};
