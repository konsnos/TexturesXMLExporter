/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include <string>

#include "statics.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"

using namespace boost::filesystem;
using namespace std;

const int statics::sffxsArrayLen = 6;
const string statics::imgSffxs[] = { ".png", ".jpg", ".tif", ".tga", ".psd", ".svg" };

////// DIFFUSE MAPS
const int statics::difSbstrsLen = 1;
const string statics::difSbstrs[] = { "_d." };

////// BUMP MAPS
const int statics::bumpSbstrsLen = 1;
const string statics::bumpSbstrs[] = { "_bmp." };

////// NORMAL MAPS
const int statics::normalSbstrsLen = 4;
const string statics::normalSbstrs[] = { "_normal.", "_N.", "_n.", "_nY+." };

////// GLOSSINESS MAPS
const int statics::glossSbstrsLen = 1;
const string statics::glossSbstrs[] = { "_g." };

////// HEIGHT MAPS
const int statics::heightSbstrsLen = 2;
const string statics::heightSbstrs[] = { "_h.", "_H." };

////// SPECULAR MAPS
const int statics::specSbstrsLen = 2;
const string statics::specSbstrs[] = { "_s.", "_S." };

////// ROUGHNESS MAPS
const int statics::roughSbstrsLen = 2;
const string statics::roughSbstrs[] = { "_r.", "_R." };

////// METALNESS MAPS
const int statics::metalSbstrsLen = 2;
const string statics::metalSbstrs[] = { "_m.", "_MT." };

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
const bool statics::isImgSffx(const string &sffx)
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

/**
	Checks if file is a bump map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isDifMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < difSbstrsLen; i++)
	{
		if ((pos = filename.find(difSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a bump map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isBumpMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < bumpSbstrsLen; i++)
	{
		if ((pos = filename.find(bumpSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a normal map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isNormalMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < normalSbstrsLen; i++)
	{
		if ((pos = filename.find(normalSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a glossiness map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isGlossinessMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < glossSbstrsLen; i++)
	{
		if ((pos = filename.find(glossSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a height map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isHeightMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < heightSbstrsLen; i++)
	{
		if ((pos = filename.find(heightSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a specular map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isSpecularMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < specSbstrsLen; i++)
	{
		if ((pos = filename.find(specSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a roughness map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isRoughnessMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < roughSbstrsLen; i++)
	{
		if ((pos = filename.find(roughSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

/**
	Checks if file is a metalness map by searching for a substring that will indicate it is.
	Returns true if it is.
*/
const size_t statics::isMetalnessMap(const string &filename)
{
	size_t pos = string::npos;
	for (int i = 0; i < metalSbstrsLen; i++)
	{
		if ((pos = filename.find(metalSbstrs[i])) != string::npos)
		{
			return pos;
		}
	}

	return 0;
}

bool statics::sortByTypeNFilename(const path &a, const path &b)
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