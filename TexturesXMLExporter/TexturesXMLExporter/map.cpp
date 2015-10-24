/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "map.h"
#include "statics.h"
#include "exporter.h"

#include <iostream>

#include "boost/filesystem/operations.hpp"


map::map(path& refPath)
	: curPath(refPath)
{
	registerMap();
}

void map::registerMap()
{
	exporter::fileImg_count++;

	if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::difSbstrs, statics::difSbstrsLen)) != string::npos)				// Diffuse maps
	{
		exporter::fileDif_count++;
		type.assign(mapType::Type::Diffuse);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::bumpSbstrs, statics::bumpSbstrsLen)) != string::npos)			// Bump
	{
		exporter::fileBmp_count++;
		type.assign(mapType::Type::Bump);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::normalSbstrs, statics::normalSbstrsLen)) != string::npos)		// Normal maps
	{
		exporter::fileNormal_count++;
		type.assign(mapType::Type::Normal);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::glossSbstrs, statics::glossSbstrsLen)) != string::npos)		// Glossiness maps
	{
		exporter::fileGloss_count++;
		type.assign(mapType::Type::Glossiness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::heightSbstrs, statics::heightSbstrsLen)) != string::npos)		// Height maps
	{
		exporter::fileHeight_count++;
		type.assign(mapType::Type::Height);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::specSbstrs, statics::specSbstrsLen)) != string::npos)			// Specular maps
	{
		exporter::fileSpec_count++;
		type.assign(mapType::Type::Specular);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::roughSbstrs, statics::roughSbstrsLen)) != string::npos)		// Roughness maps
	{
		exporter::fileRough_count++;
		type.assign(mapType::Type::Roughness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::metalSbstrs, statics::metalSbstrsLen)) != string::npos)		// Metalness maps
	{
		exporter::fileMetal_count++;
		type.assign(mapType::Type::Metalness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_string(), statics::emissiveSbstrs, statics::emissiveSbstrsLen)) != string::npos)		// Emissive maps
	{
		exporter::fileMetal_count++;
		type.assign(mapType::Type::Emissive);
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

const string map::getName() const
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

void map::generateThumb()
{
	thumbPath = string(statics::thumbnailsPath->c_str()).append("\\").append(curPath.filename().generic_string()).append(".png");

	if (!boost::filesystem::exists(thumbPath))
	{
		string cmmd;
		if (statics::convertLocal)
		{
			cmmd = statics::convertPath + string(" -resize 200x200 ");
		}
		else
		{
			cmmd = "convert -resize 200x200 ";
		}
		cmmd.append("\"").append(curPath.generic_string()).append("\" \"").append(thumbPath.generic_string()).append("\"");

		system(cmmd.c_str());
	}
}

const path map::getThumbPath() const
{
	return thumbPath;
}

const path map::getCurPath() const
{
	return curPath;
}