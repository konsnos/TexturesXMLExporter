/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

#include "boost\filesystem\path.hpp"

using namespace boost::filesystem;

using namespace std;

///TODO: Move these to the map class.
class statics
{
public:
	static const bool isImgSffx(const string &sffx);
	static const size_t isDifMap(const string &filename);
	static const size_t isBumpMap(const string &filename);
	static const size_t isNormalMap(const string &filename);
	static const size_t isGlossinessMap(const string &filename);
	static const size_t isHeightMap(const string &filename);
	static const size_t isSpecularMap(const string &filename);
	static const size_t isRoughnessMap(const string &filename);
	static const size_t isMetalnessMap(const string &filename);

	/** Length of array containing image file extension. */
	static const int sffxsArrayLen;
	/** Possible image file suffixes. */
	static const string imgSffxs[];

	/// Diffuse
	static const int difSbstrsLen;
	static const string difSbstrs[];

	/** Length of array containing bump file extensions. */
	static const int bumpSbstrsLen;
	/** Bump map substrings. */
	static const string bumpSbstrs[];

	/** Length of array containing normal file extensions. */
	static const int normalSbstrsLen;
	/** Normal map substrings. */
	static const string normalSbstrs[];

	static const int statics::glossSbstrsLen;
	static const string statics::glossSbstrs[];

	static const int statics::heightSbstrsLen;
	static const string statics::heightSbstrs[];

	static const int statics::specSbstrsLen;
	static const string statics::specSbstrs[];

	static const int statics::roughSbstrsLen;
	static const string statics::roughSbstrs[];

	static const int statics::metalSbstrsLen;
	static const string statics::metalSbstrs[];

	/* Compares two paths for their type, and if the same compares their file name. */
	static bool sortByTypeNFilename(const path &a, const path &b);

	/* Folder name for the thumbnails. */
	static const string statics::thumbnailsFolderName;
	/* Folder name for the Textures Showcaser project. This should be ignored as both this and Textures Showcaser will be in the same folder. */
	static const string statics::texturesShowcaserFolderName;

	/* Path for the thumbnails. */
	static string* statics::thumbnailsPath;

	/* Starting path to search for textures. */
	static char* startingPath;

	/* If set to true then the program will search for the convert program in the path given. */
	static bool convertLocal;
	/* Path for the convert program (ImageMagick).*/
	static char* convertPath;

	/* Version of this program. */
	static const float version;
};