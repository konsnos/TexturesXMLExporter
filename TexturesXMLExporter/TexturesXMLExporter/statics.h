/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

#include "boost\filesystem\path.hpp"

using namespace boost::filesystem;

///TODO: Move these to the map class.
class statics
{
public:
	static const bool isImgSffx(const std::string &sffx);
	static const size_t isDifMap(const std::string &filename);
	static const size_t isBumpMap(const std::string &filename);
	static const size_t isNormalMap(const std::string &filename);
	static const size_t isGlossinessMap(const std::string &filename);
	static const size_t isHeightMap(const std::string &filename);
	static const size_t isSpecularMap(const std::string &filename);
	static const size_t isRoughnessMap(const std::string &filename);
	static const size_t isMetalnessMap(const std::string &filename);

	/** Length of array containing image file extension. */
	static const int sffxsArrayLen;
	/** Possible image file suffixes. */
	static const std::string imgSffxs[];

	/// Diffuse
	static const int difSbstrsLen;
	static const std::string difSbstrs[];

	/** Length of array containing bump file extensions. */
	static const int bumpSbstrsLen;
	/** Bump map substrings. */
	static const std::string bumpSbstrs[];

	/** Length of array containing normal file extensions. */
	static const int normalSbstrsLen;
	/** Normal map substrings. */
	static const std::string normalSbstrs[];

	static const int statics::glossSbstrsLen;
	static const std::string statics::glossSbstrs[];

	static const int statics::heightSbstrsLen;
	static const std::string statics::heightSbstrs[];

	static const int statics::specSbstrsLen;
	static const std::string statics::specSbstrs[];

	static const int statics::roughSbstrsLen;
	static const std::string statics::roughSbstrs[];

	static const int statics::metalSbstrsLen;
	static const std::string statics::metalSbstrs[];

	/* Compares two paths for their type, and if the same compares their file name. */
	static bool sortByTypeNFilename(const path &a, const path &b);
};