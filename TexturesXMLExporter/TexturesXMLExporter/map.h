/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

#include "boost\filesystem\path.hpp"

#include "mapType.h"

using namespace std;
using namespace boost::filesystem;

/* Contains information about a file which is a texture for a material. */
class map
{
public:
	map(path &);
	~map();

	/* Returns the material name without any file extensions or map type substrings. */
	string getMatName() const;
	/* Returns the xml string of this map. */
	const string getXMLElement() const;
	/* Generates thumbnail for this map if it doesn't exist. */
	void generateThumb();
	/* Returns the string of the map type. */
	const mapType getType() const;

private:
	size_t namePos;
	/* Type of the map that is to be put as the element of the xml string. */
	mapType type;
	/* File's full path. */
	path curPath;
	/* Thumbnail's path. */
	path thumbPath;
	/* Registers map. Assigns and counts image type. */
	void registerMap();
};

