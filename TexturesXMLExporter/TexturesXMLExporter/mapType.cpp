/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "mapType.h"

const wstring mapType::types[] = { L"diffuse", L"bump", L"normal", L"gloss", L"height", L"specular", L"rough", L"metal", L"emissive", L"other" };

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

const wstring mapType::getString() const
{
	return types[type];
}

const mapType::Type mapType::getType() const
{
	return type;
}