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

namespace texturesExporter
{
	/* Contains information about a file which is a texture for a material. */
	class map
	{
	public:
		map(path &);
		~map();

		/* Returns the material name without any file extensions or map type substrings. If untilDot is true then the name also includes any suffix (eg. _n) */
		const wstring getName() const;
		/* Returns the wstring of the map type. */
		const mapType getType() const;
		/* Returns the thumbnail path variable. */
		const path getThumbPath() const;
		/* Returns map full path variable. */
		const path getCurPath() const;

	private:
		size_t namePos;
		/* Type of the map that is to be put as the element of the xml wstring. */
		mapType type;
		/* File's full path. */
		path curPath;
		/* Thumbnail's path. */
		path thumbPath;
		/* Registers map. Assigns and counts image type. */
		void registerMap();
	};
}