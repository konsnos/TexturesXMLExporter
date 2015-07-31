/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "material.h"
#include "exporter.h"

material::material(const string &newName, map* newMap)
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

const string material::getXMLElement() const
{
	string elem;

	for (int i = 0; i < exporter::indents; i++)
		elem.append("\t");
	elem += "<material name=\"" + name + "\">\n";

	exporter::indents++;

	/// Add maps
	size_t mapsSize = maps.size();
	for (size_t m = 0; m < mapsSize; m++)
	{
		for (int t = 0; t < exporter::indents; t++)
			elem.append("\t");
		elem += maps[m]->getXMLElement() + "\n";
	}
	/// ~Add maps
	
	exporter::indents--;

	for (int i = 0; i < exporter::indents; i++)
		elem.append("\t");
	elem += "</material>\n";
	return elem;
}

const string material::getName() const
{
	return name;
}

void material::destroy()
{
	for (std::vector<map*>::iterator it = maps.begin(); it != maps.end(); ++it)
	{
		delete *it;
	}
	maps.clear();
}