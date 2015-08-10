/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include <string>
#include <cctype>

#include "statics.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"

using namespace boost::filesystem;
using namespace std;

const int statics::sffxsArrayLen = 7;
const string statics::imgSffxs[] = { ".png", ".jpg", ".tif", ".tga", ".psd", ".svg", ".dds" };

////// DIFFUSE MAPS
const int statics::difSbstrsLen = 1;
const string statics::difSbstrs[] = { "_d" };

////// BUMP MAPS
const int statics::bumpSbstrsLen = 2;
const string statics::bumpSbstrs[] = { "_bmp", "bump" };

////// NORMAL MAPS
const int statics::normalSbstrsLen = 4;
const string statics::normalSbstrs[] = { "_normal", "_n", "_N", "_nY+" };

////// GLOSSINESS MAPS
const int statics::glossSbstrsLen = 2;
const string statics::glossSbstrs[] = { "_g", "_G" };

////// HEIGHT MAPS
const int statics::heightSbstrsLen = 2;
const string statics::heightSbstrs[] = { "_h", "_H" };

////// SPECULAR MAPS
const int statics::specSbstrsLen = 3;
const string statics::specSbstrs[] = { "_s", "_S", "_spec" };

////// ROUGHNESS MAPS
const int statics::roughSbstrsLen = 2;
const string statics::roughSbstrs[] = { "_r", "_R" };

////// METALNESS MAPS
const int statics::metalSbstrsLen = 3;
const string statics::metalSbstrs[] = { "_m", "_M", "_MT" };

////// EMISSIVE MAPS
const int statics::emissiveSbstrsLen = 2;
const string statics::emissiveSbstrs[] = { "_e", "_E" };

const string statics::thumbnailsFolderName = "exp_thumbs";
const string statics::texturesShowcaserFolderName = "TexturesShowcaser";

string* statics::thumbnailsPath = new string();
char* statics::startingPath = "";

bool statics::convertLocal = false;
char* statics::convertPath = "";

const float statics::version = 1.0f;

/** 
	Checks if file extension (suffix) is part of the img suffix array.
	Returns true if it is.
*/
const bool statics::isImgSffx(const string& sffx)
{
	for (int i = 0; i < sffxsArrayLen; i++)
	{
		if (sffx.compare(imgSffxs[i]) == 0)
		{
			return true;
		}
	}

	return false;
}

const size_t statics::isTypeMap(const string& filename, const string* substrs, int length)
{
	size_t pos;
	size_t findIndex;
	bool isStop;
	bool notInEnd;

	for (int i = 0; i < length; i++)
	{
		notInEnd = true;
		pos = 0;

		while (notInEnd)
		{
			if ((pos = filename.find(substrs[i], pos)) != string::npos)
			{
				isStop = true;
				findIndex = pos + substrs[i].length();
				while (isStop)
				{
					if (filename[findIndex] == '.')	// Search for . that will indicate a suffix of map type.
					{
						return pos;
					}
					else if (isdigit(filename[findIndex]))	// Ignore digits as there may be many map types.
					{
						findIndex++;
					}
					else
					{
						pos = findIndex; // Continue from last searched place.
						isStop = false;
					}
				}
			}
			else
			{
				notInEnd = false;
			}
		}
	}
	
	return string::npos;
}

bool statics::sortByTypeNFilename(const path& a, const path& b)
{
	if (detail::status(a).type() == detail::status(b).type())
	{
		//return a.filename().compare(b.filename()) < 0 ? true : false;
		return a.filename() < b.filename();
	}

	if (is_directory(a))
		return true;

	return false;
}