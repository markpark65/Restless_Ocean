#pragma once
#include <string>
#include "Datatype.h"

class IMap
{
public:
	virtual ~IMap() = default;
	virtual std::string GetName() const = 0;
	virtual AttributeType GetAttributeType() const = 0;

	virtual MapType GetMapType() const = 0;
};
