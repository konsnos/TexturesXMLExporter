#include <Magick++.h>
#include <iostream>

#include "imagemagick.h"
#include "boost\filesystem\operations.hpp"
#include "../statics.h"

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
		{

			generateThumb(_mat.getMap(i));
		}
	}

	void imagemagick::generateThumb(const texturesExporter::map& _map)
	{
		thumbPath = _map.getThumbPath(); // get thumb path.

		// make sure the thumb path exists before generating the thumbnail.
		if (!boost::filesystem::exists(thumbPath))
		{
			/*if (statics::convertLocal)
				cmmd = statics::convertPath + wstring(L" -resize 200x200 ");
			else
				cmmd = L"convert -resize 200x200 ";

			cmmd.append(L"\"").append(_map.getCurPath().generic_wstring()).append(L"\" \"").append(thumbPath.generic_wstring()).append(L"\"");

			_wsystem(cmmd.c_str());*/

			Image image;

			try
			{
				image.read(_map.getCurPath().generic_string()); //TODO: check if it works with wstrings
			}
			catch (const std::exception& error)
			{
				//cout << "Error: " << error.what() << endl; // this prints the error.
			}
			try
			{
				image.resize(Geometry(200, 200));
				image.write(thumbPath.generic_string());
			}
			catch (const std::exception& error)
			{
				cout << "Error: " << error.what() << endl; // this prints the error.
			}
		}
	}
}