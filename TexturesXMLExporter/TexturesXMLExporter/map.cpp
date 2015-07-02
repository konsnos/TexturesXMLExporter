/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "map.h"
#include "statics.h"
#include "exporter.h"

#include <iostream>


map::map(path& refPath)
	: curPath(refPath)
{
	registerMap();
}

void map::registerMap()
{
	exporter::fileImg_count++;

	if ((namePos = statics::isDifMap(curPath.filename().generic_string())) != 0)					// Diffuse maps
	{
		exporter::fileDif_count++;
		type.assign(mapType::Type::Diffuse);
	}
	else if ((namePos = statics::isBumpMap(curPath.filename().generic_string())) != 0)			// Bump
	{
		exporter::fileBmp_count++;
		type.assign(mapType::Type::Bump);
	}
	else if ((namePos = statics::isNormalMap(curPath.filename().generic_string())) != 0)			// Normal maps
	{
		exporter::fileNormal_count++;
		type.assign(mapType::Type::Normal);
	}
	else if ((namePos = statics::isGlossinessMap(curPath.filename().generic_string())) != 0)		// Glossiness maps
	{
		exporter::fileGloss_count++;
		type.assign(mapType::Type::Glossiness);
	}
	else if ((namePos = statics::isHeightMap(curPath.filename().generic_string())) != 0)			// Height maps
	{
		exporter::fileHeight_count++;
		type.assign(mapType::Type::Height);
	}
	else if ((namePos = statics::isSpecularMap(curPath.filename().generic_string())) != 0)		// Specular maps
	{
		exporter::fileSpec_count++;
		type.assign(mapType::Type::Specular);
	}
	else if ((namePos = statics::isRoughnessMap(curPath.filename().generic_string())) != 0)		// Roughness maps
	{
		exporter::fileRough_count++;
		type.assign(mapType::Type::Roughness);
	}
	else if ((namePos = statics::isMetalnessMap(curPath.filename().generic_string())) != 0)		// Metalness maps
	{
		exporter::fileMetal_count++;
		type.assign(mapType::Type::Metalness);
	}
	else
	{
		namePos = statics::isImgSffx(curPath.filename().generic_string());
		exporter::fileUnkn_count++;
		type.assign(mapType::Type::Other);
	}
}


map::~map()
{
}

const mapType map::getType() const
{
	return type;
}

const string map::getXMLElement() const
{
	string elem = getType().getString();
	string xmlElem("<" + elem + ">" + curPath.string() + "</" + elem + ">");

	return xmlElem;
}

string map::getMatName() const
{
	string filename = curPath.filename().generic_string();
	if (namePos)
	{
		return filename.substr(0, namePos);
	}
	// If no name recognised just get the one before the last dot.
	else
	{
		size_t dotPos = filename.find_last_of(".");
		return filename.substr(0, dotPos);
	}
}