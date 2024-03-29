/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "map.h"
#include "statics.h"
#include "exporter.h"

#include <iostream>
#include <functional>

#include "boost/filesystem/operations.hpp"

namespace texturesExporter
{
	map::map(path& refPath, ImgType refImgType)
		: curPath(refPath), imgType(refImgType)
	{
		registerMap();

		// The thumbnail is the path to the thumbnails folder plus the filename in a png format.
		thumbPath = wstring(statics::thumbnailsPath->c_str()).append(L"\\").append(
			curPath.filename().generic_wstring()).append(L"_").append(
				to_wstring(std::hash<wstring>()(curPath.generic_wstring()))).append(L".png");
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
			namePos = curPath.filename().generic_wstring().find_last_of(L".");
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
		return curPath.filename().generic_wstring().substr(0, namePos);
	}

	const path map::getThumbPath() const
	{
		return thumbPath;
	}

	const path map::getCurPath() const
	{
		return curPath;
	}

	const bool map::requiresThumb() const
	{
		switch (imgType)
		{
		case texturesExporter::png:
		case texturesExporter::jpg:
			return false;
		case texturesExporter::tif:
		case texturesExporter::tga:
		case texturesExporter::psd:
		case texturesExporter::svg:
		case texturesExporter::dds:
			return true;
		// nothing should get past this
		default:
			string strError("File type is unidentified. File path: ");
			strError.append(curPath.generic_string());
			throw std::invalid_argument(strError);
			break;
		}
	}
}