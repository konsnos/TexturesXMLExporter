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
	static const bool isImgSffx(const string& sffx);
	/**
	Checks if file is a specific type of map by searching for a substring that will indicate it is.
	Returns the index of the substring indication if it is. Returns string::npos if it isn't.
	*/
	static const size_t isTypeMap(const string& filename, const string* substrs, int length);

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

	static const int glossSbstrsLen;
	static const string glossSbstrs[];

	static const int heightSbstrsLen;
	static const string heightSbstrs[];

	static const int specSbstrsLen;
	static const string specSbstrs[];

	static const int roughSbstrsLen;
	static const string roughSbstrs[];

	static const int metalSbstrsLen;
	static const string metalSbstrs[];

	static const int emissiveSbstrsLen;
	static const string emissiveSbstrs[];

	/* Compares two paths for their type, and if the same compares their file name. */
	static bool sortByTypeNFilename(const path& a, const path& b);

	/* Folder name for the thumbnails. */
	static const string statics::thumbnailsFolderName;
	/* Folder name for the Textures Showcaser project. This should be ignored as both this and Textures Showcaser will be in the same folder. */
	static const string statics::texturesShowcaserFolderName;

	/* Path for the thumbnails. */
	static string* statics::thumbnailsPath;

	/* Current path this program is running from. */
	static char* currentPath;
	/* Starting path to search for textures. */
	static char* startingPath;

	/* If set to true then the program will search for the convert program in the path given. */
	static bool convertLocal;
	/* Path for the convert program (ImageMagick).*/
	static char* convertPath;

	/* Version of this program. */
	static const float version;
};