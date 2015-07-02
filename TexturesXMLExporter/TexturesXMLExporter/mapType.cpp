/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "mapType.h"

const string mapType::types[] = { "diffuse", "bump", "normal", "glossiness", "height", "specular", "roughness", "metalness", "other" };

mapType::mapType()
	:type(Other)
{
}


mapType::~mapType()
{
}

void mapType::assign(Type newType)
{
	type = newType;
}

const string mapType::getString() const
{
	return types[type];
}

const mapType::Type mapType::getType() const
{
	return type;
}