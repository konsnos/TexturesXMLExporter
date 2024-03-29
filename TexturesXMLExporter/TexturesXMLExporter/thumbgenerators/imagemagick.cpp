#include <Magick++.h>
#include <iostream>

#include "imagemagick.h"
#include "boost\filesystem\operations.hpp"
#include "../string_utf8_helper.h"

using namespace std;
using namespace texturesExporter;
using namespace Magick;
// var length, var path

namespace thumbgenerators
{
	imagemagick::imagemagick()
	{
		char *args = "";
		InitializeMagick(args);
	}

	imagemagick::~imagemagick()
	{
	}

	void imagemagick::generateThumbs(const folder& _folder)
	{
		// Search subfolders in folder.
		{
			size_t foldersLength = _folder.getFoldersAmount();
			for (size_t i = 0; i < foldersLength; i++)
				generateThumbs(_folder.getFolder(i));
		}

		// search materials in folder
		{
			size_t matsLength = _folder.getMatsAmount();
			for (size_t i = 0; i < matsLength; i++)
				generateThumbs(_folder.getMaterial(i));
		}
	}

	void imagemagick::generateThumbs(const material& _mat)
	{
		size_t mapsLength = _mat.getMapsAmount();
		for (size_t i = 0; i < mapsLength; i++)
			generateThumb(_mat.getMap(i));
	}

	void imagemagick::generateThumb(const texturesExporter::map& _map)
	{
		if (_map.requiresThumb())
		{
			thumbPath = _map.getThumbPath(); // get thumb path.

			// check if the thumbnail already exists.
			// if not generate it.
			if (!boost::filesystem::exists(thumbPath))
			{
				try
				{
					Image image(string_utf8_helper::wstring_to_utf8(_map.getCurPath().generic_wstring())); //TODO: check if it works with wstrings
					image.resize(Geometry(200, 200));
					image.write(string_utf8_helper::wstring_to_utf8(thumbPath.generic_wstring()));
				}
				catch (const std::exception& error)
				{
					cout << "Error generating thumbnail: " << error.what() << endl; // this prints the error.
				}
			}
		}
	}
}