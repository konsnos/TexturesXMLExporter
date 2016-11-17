/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

#include "boost\filesystem\path.hpp"

using namespace boost::filesystem;

using namespace std;

namespace texturesExporter
{
	enum ImgType { uknown, png, jpg, tif, tga, psd, svg, dds };

	///TODO: Move these to the map class.
	class statics
	{
	public:
		static const bool isImgSffx(const wstring& sffx);
		/**
		Checks if file is a specific type of map by searching for a substring that will indicate it is.
		Returns the index of the substring indication if it is. Returns wstring::npos if it isn't.
		*/
		static const size_t isTypeMap(wstring filename, const wstring* substrs, int length);

		static string statics::to_utf8(const wchar_t* buffer, int len);
		static string statics::to_utf8(const std::wstring& str);

		/* Returns local time. */
		static const tm GetLocalTime();

		/** Length of array containing image file extension. */
		static const int sffxsArrayLen;
		/** Possible image file suffixes. */
		static const wstring imgSffxs[];

		/// Diffuse
		static const int difSbstrsLen;
		static const wstring difSbstrs[];

		/** Length of array containing bump file extensions. */
		static const int bumpSbstrsLen;
		/** Bump map substrings. */
		static const wstring bumpSbstrs[];

		/** Length of array containing normal file extensions. */
		static const int normalSbstrsLen;
		/** Normal map substrings. */
		static const wstring normalSbstrs[];

		static const int glossSbstrsLen;
		static const wstring glossSbstrs[];

		static const int heightSbstrsLen;
		static const wstring heightSbstrs[];

		static const int specSbstrsLen;
		static const wstring specSbstrs[];

		static const int roughSbstrsLen;
		static const wstring roughSbstrs[];

		static const int metalSbstrsLen;
		static const wstring metalSbstrs[];

		static const int emissiveSbstrsLen;
		static const wstring emissiveSbstrs[];

		/* Compares two paths for their type, and if the same compares their file name. */
		static bool sortByTypeNFilename(const path& a, const path& b);

		/* Returns the enum of the image suffix. */
		static const ImgType getImgTypeBySuffix(const std::wstring& imgSuffix);

		/* Folder name for the thumbnails. */
		static const wstring statics::thumbnailsFolderName;
		/* Folder name for the Textures Showcaser project. This should be ignored as both this and Textures Showcaser will be in the same folder. */
		static const wstring statics::texturesShowcaserFolderName;

		/* Path for the thumbnails. */
		static wstring* statics::thumbnailsPath;

		/* Current path this program is running from. */
		static wchar_t* currentPath;
		/* Starting path to search for textures. */
		static wchar_t* startingPath;

		/* If set to true then the program will search for the convert program in the path given. */
		static bool convertLocal;
		/* Path for the convert program (ImageMagick).*/
		static wchar_t* convertPath;

		/* Version of this program. */
		static const float version;
	};
}