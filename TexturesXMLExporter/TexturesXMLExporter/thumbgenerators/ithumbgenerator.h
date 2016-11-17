/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include "../folder.h"
#include "../material.h"
#include "../map.h"

using namespace texturesExporter;

namespace thumbgenerators
{
	/* Interface which represents */
	class IThumbGenerator
	{
	public:
		virtual ~IThumbGenerator(){};

		/* Iterates recursively all subfolders, and all materials to generate thumbnails. */
		virtual void generateThumbs(const folder&) = 0;
	protected:
		/* Iterates alls maps in the material to generate thumbnails. */
		virtual void generateThumbs(const material&) = 0;
		/* Genrates thumbnail of the map. */
		virtual void generateThumb(const texturesExporter::map&) = 0;
	};
}