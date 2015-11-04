/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "material.h"
#include "exporter.h"

material::material(const wstring &newName, map* newMap)
	:name(newName)
{
	maps.push_back(newMap);
}


material::~material()
{
}

void material::addMap(map* newMap)
{
	maps.push_back(newMap);
}

void material::generateMapsThumbs()
{
	for (auto& map : maps)
		map->generateThumb();
}

const wstring material::getName() const
{
	return name;
}

const size_t material::getMapsAmount() const
{
	return maps.size();
}

const map& material::getMap(const int index) const
{
	return *maps[index];
}

void material::destroy()
{
	for (std::vector<map*>::iterator it = maps.begin(); it != maps.end(); ++it)
	{
		delete *it;
	}
	maps.clear();
}