/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

#include "boost\filesystem\path.hpp"

#include "folder.h"

using namespace std;
using namespace boost::filesystem;

class exporter
{
public:
	exporter();
	~exporter();

	static unsigned long fileImg_count;
	static unsigned long fileOther_count;
	static unsigned long fileDif_count;
	static unsigned long fileBmp_count;
	static unsigned long fileNormal_count;
	static unsigned long fileGloss_count;
	static unsigned long fileHeight_count;
	static unsigned long fileSpec_count;
	static unsigned long fileRough_count;
	static unsigned long fileMetal_count;
	static unsigned long fileUnkn_count;
	static unsigned long dir_count;
	static unsigned long other_count;
	static unsigned long err_count;

	static int indents;
private:
	const char* generate_xml();
	void printFormatted(char* chars, int count) const;
	/* Generate tree folder list with all the textures in them. */
	void generateTreeOrder();
	/* Generates thumbnails for all maps in materials. */
	void generateThumbs();
	/* Instantiates the thumbnails path. */
	void initializeThumbnailsPath();
	/* Initializes the starting path. */
	void initializeStartingDir();

	/* The staring folder for the textures. */
	folder* rootFolder;
	/* The starting path of the folders. */
	path* rootPath;

	string xmlToWrite;
};

