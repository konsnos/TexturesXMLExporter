#pragma once
#include "../folder.h"
#include "ithumbgenerator.h"

namespace thumbgenerators
{
	class imagemagick : public IThumbGenerator
	{
	public:
		imagemagick();
		~imagemagick();

		/* Iterates recursively all subfolders, and all materials to generate thumbnails. */
		void generateThumbs(const folder&);
	protected:
		/* Iterates alls maps in the material to generate thumbnails. */
		void generateThumbs(const material&);
		/* Genrates thumbnail of the map. */
		void generateThumb(const map&);
	private:
		/* Path of the thumbnail. */
		path thumbPath;
		/* String containing the command for the command line to create the thumbnail. */
		wstring cmmd;
	};
}