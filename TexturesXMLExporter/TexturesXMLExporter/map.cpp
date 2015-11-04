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

	if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::difSbstrs, statics::difSbstrsLen)) != wstring::npos)				// Diffuse maps
	{
		exporter::fileDif_count++;
		type.assign(mapType::Type::Diffuse);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::bumpSbstrs, statics::bumpSbstrsLen)) != wstring::npos)			// Bump
	{
		exporter::fileBmp_count++;
		type.assign(mapType::Type::Bump);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::normalSbstrs, statics::normalSbstrsLen)) != wstring::npos)		// Normal maps
	{
		exporter::fileNormal_count++;
		type.assign(mapType::Type::Normal);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::glossSbstrs, statics::glossSbstrsLen)) != wstring::npos)		// Glossiness maps
	{
		exporter::fileGloss_count++;
		type.assign(mapType::Type::Glossiness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::heightSbstrs, statics::heightSbstrsLen)) != wstring::npos)		// Height maps
	{
		exporter::fileHeight_count++;
		type.assign(mapType::Type::Height);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::specSbstrs, statics::specSbstrsLen)) != wstring::npos)			// Specular maps
	{
		exporter::fileSpec_count++;
		type.assign(mapType::Type::Specular);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::roughSbstrs, statics::roughSbstrsLen)) != wstring::npos)		// Roughness maps
	{
		exporter::fileRough_count++;
		type.assign(mapType::Type::Roughness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::metalSbstrs, statics::metalSbstrsLen)) != wstring::npos)		// Metalness maps
	{
		exporter::fileMetal_count++;
		type.assign(mapType::Type::Metalness);
	}
	else if ((namePos = statics::isTypeMap(curPath.filename().generic_wstring(), statics::emissiveSbstrs, statics::emissiveSbstrsLen)) != wstring::npos)		// Emissive maps
	{
		exporter::fileMetal_count++;
		type.assign(mapType::Type::Emissive);
	}
	else
	{
		namePos = statics::isImgSffx(curPath.filename().generic_wstring());
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

const wstring map::getName() const
{
	wstring filename = curPath.filename().generic_wstring();
	if (namePos)
	{
		return filename.substr(0, namePos);
	}
	// If no name recognised just get the one before the last dot.
	else
	{
		size_t dotPos = filename.find_last_of(L".");
		return filename.substr(0, dotPos);
	}
}

void map::generateThumb()
{
	thumbPath = wstring(statics::thumbnailsPath->c_str()).append(L"\\").append(curPath.filename().generic_wstring()).append(L".png");

	if (!boost::filesystem::exists(thumbPath))
	{
		wstring cmmd;
		if (statics::convertLocal)
			cmmd = statics::convertPath + wstring(L" -resize 200x200 ");
		else
			cmmd = L"convert -resize 200x200 ";

		cmmd.append(L"\"").append(curPath.generic_wstring()).append(L"\" \"").append(thumbPath.generic_wstring()).append(L"\"");
		
		_wsystem(cmmd.c_str());
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