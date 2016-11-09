/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <cctype>
#include <Windows.h>

#include "statics.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"

using namespace boost::filesystem;
using namespace std;

const int statics::sffxsArrayLen = 7;
const wstring statics::imgSffxs[] = { L".png", L".jpg", L".tif", L".tga", L".psd", L".svg", L".dds" };

////// DIFFUSE MAPS
const int statics::difSbstrsLen = 2;
const wstring statics::difSbstrs[] = { L"_d", L"_baked" };

////// BUMP MAPS
const int statics::bumpSbstrsLen = 2;
const wstring statics::bumpSbstrs[] = { L"_bmp", L"bump" };

////// NORMAL MAPS
const int statics::normalSbstrsLen = 3;
const wstring statics::normalSbstrs[] = { L"_normal", L"_n", L"_ny+" };

////// GLOSSINESS MAPS
const int statics::glossSbstrsLen = 1;
const wstring statics::glossSbstrs[] = { L"_g" };

////// HEIGHT MAPS
const int statics::heightSbstrsLen = 1;
const wstring statics::heightSbstrs[] = { L"_h" };

////// SPECULAR MAPS
const int statics::specSbstrsLen = 2;
const wstring statics::specSbstrs[] = { L"_s", L"_spec" };

////// ROUGHNESS MAPS
const int statics::roughSbstrsLen = 1;
const wstring statics::roughSbstrs[] = { L"_r" };

////// METALNESS MAPS
const int statics::metalSbstrsLen = 2;
const wstring statics::metalSbstrs[] = { L"_m", L"_mt" };

////// EMISSIVE MAPS
const int statics::emissiveSbstrsLen = 1;
const wstring statics::emissiveSbstrs[] = { L"_e" };

const wstring statics::thumbnailsFolderName = L"exp_thumbs";
const wstring statics::texturesShowcaserFolderName = L"TexturesShowcaser";

wchar_t* statics::currentPath = L"";
wstring* statics::thumbnailsPath = new wstring();
wchar_t* statics::startingPath = L"";

bool statics::convertLocal = false;
wchar_t* statics::convertPath = L"";

const float statics::version = 1.0f;

/** 
	Checks if file extension (suffix) is part of the img suffix array.
	Returns true if it is.
*/
const bool statics::isImgSffx(const wstring& sffx)
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

const size_t statics::isTypeMap(wstring filename, const wstring* substrs, int length)
{
	size_t pos;
	size_t findIndex;
	bool isStop;
	bool notInEnd;

	// make filename to lower case in order to ignore multiple case instances.
	std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

	for (int i = 0; i < length; i++)
	{
		notInEnd = true;
		pos = 0;

		while (notInEnd)
		{
			if ((pos = filename.find(substrs[i], pos)) != wstring::npos)
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
	
	return wstring::npos;
}

const tm statics::GetLocalTime()
{
	time_t t = time(NULL);

	/*tm time;
	localtime_s(&time, &t);

	return time;*/

	return *localtime(&t);
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

const ImgType statics::getImgTypeBySuffix(const std::wstring & imgSuffix)
{
	if (imgSuffix == statics::imgSffxs[0])
		return ImgType::png;
	else if (imgSuffix == statics::imgSffxs[1])
		return ImgType::jpg;
	else if (imgSuffix == statics::imgSffxs[2])
		return ImgType::tif;
	else if (imgSuffix == statics::imgSffxs[3])
		return ImgType::tga;
	else if (imgSuffix == statics::imgSffxs[4])
		return ImgType::psd;
	else if (imgSuffix == statics::imgSffxs[5])
		return ImgType::svg;
	else if (imgSuffix == statics::imgSffxs[6])
		return ImgType::dds;

	return ImgType::uknown;
}

string statics::to_utf8(const wchar_t* buffer, int len)
{
	int nChars = ::WideCharToMultiByte(CP_UTF8, 0, buffer, len, NULL, 0, NULL, NULL);
	if (nChars == 0) return "";

	string newbuffer;
	newbuffer.resize(nChars);
	::WideCharToMultiByte(CP_UTF8, 0, buffer, len, const_cast< char* >(newbuffer.c_str()), nChars, NULL, NULL);

	return newbuffer;
}

string statics::to_utf8(const std::wstring& str)
{
	return to_utf8(str.c_str(), (int)str.size());
}