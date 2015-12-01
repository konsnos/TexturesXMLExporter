/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "exporter.h"
#include "Statics.h"
#include "folder.h"

#include "exporters\istringexporter.h"
#include "exporters\xmlexporter.h"

#include "thumbgenerators\imagemagick.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"

#include <direct.h>
#include <time.h>

#include <exception>


using namespace std;
using namespace boost::filesystem;
using namespace exporters;
using namespace thumbgenerators;

unsigned long exporter::fileImg_count = 0;
unsigned long exporter::fileOther_count = 0;
unsigned long exporter::fileDif_count = 0;
unsigned long exporter::fileBmp_count = 0;
unsigned long exporter::fileNormal_count = 0;
unsigned long exporter::fileGloss_count = 0;
unsigned long exporter::fileHeight_count = 0;
unsigned long exporter::fileSpec_count = 0;
unsigned long exporter::fileRough_count = 0;
unsigned long exporter::fileMetal_count = 0;
unsigned long exporter::fileUnkn_count = 0;
unsigned long exporter::dir_count = 0;
unsigned long exporter::other_count = 0;
unsigned long exporter::err_count = 0;

/** Initializer variables and save to file the generated xml. */
exporter::exporter()
{
	// Initialize time
	clock_t start = std::clock();

	initializeStatsCounts();

	initializeStartingDir();

	initializeThumbnailsPath();

	generateTreeOrder();

	generateThumbs();

	{
		ofstream fileTexsExport(rootPath->wstring() + L"\\textures.xml");	// textures.xml file is generated at the root textures folder.

		fileTexsExport << statics::to_utf8(generate_xml());
		fileTexsExport.close();
	}

	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	saveStats(duration, start);
	printStats(duration);
}

void exporter::initializeStatsCounts()
{
	fileImg_count = 0;
	fileOther_count = 0;
	fileDif_count = 0;
	fileBmp_count = 0;
	fileNormal_count = 0;
	fileGloss_count = 0;
	fileHeight_count = 0;
	fileSpec_count = 0;
	fileRough_count = 0;
	fileMetal_count = 0;
	fileUnkn_count = 0;
	dir_count = 0;
	other_count = 0;
	err_count = 0;
}

void exporter::initializeStartingDir()
{
	// Get current path.
	statics::currentPath = _wgetcwd(NULL, 0);
	if (statics::currentPath == NULL)
	{
		cout << "Error: Could not retrieve current path. Exitting..." << endl;
		exit(1);
	}

	if (statics::startingPath == L"")
		statics::startingPath = statics::currentPath;

	wcout << L"Root path is " << statics::startingPath << endl << endl;
	rootPath = new path(statics::startingPath);

	if (!is_directory(*rootPath))
	{
		cout << "Error: Current path is not a directory. Exitting..." << endl;
		exit(1);
	}
}

void exporter::initializeThumbnailsPath()
{
	path tempDir(rootPath->wstring() + L"\\" + statics::thumbnailsFolderName);

	if (is_directory(tempDir))	// Check if thumbnails directory exists.
	{
		wcout << L"Using thumbnails directory at " << tempDir << endl << endl;
	}
	else
	{
		if (boost::filesystem::create_directory(tempDir))	// Create thumbnails directory
		{
			wcout << "Thumbnails folder created at " << tempDir << endl << endl;
		}
		else	// Couldn't create thumbnail directory.
		{
			cout << "Error: Thumbnails folder couldn't be created.";
			exit(1);	// Exit with error.
		}
	}

	statics::thumbnailsPath = new wstring(tempDir.wstring());
}

void exporter::generateThumbs()
{
	cout << "Generating thumbnails..." << endl;

	IThumbGenerator* im = new imagemagick();
	im->generateThumbs(*rootFolder);
}

void exporter::generateTreeOrder()
{
	cout << "Sorting folders and materials..." << endl;

	rootFolder = new folder(*rootPath);

	// Trim folders
	rootFolder->trimSingleMatFolders();
}

/** 
	Initialize wstring to write.
	Search for current directory for files recursively.
*/
const wstring exporter::generate_xml()
{
	cout << "Generating textures.xml..." << endl;
	wstring stringToWrite = L"<!-- Generated by TexturesXMLExporter, a tool built by Konstantinos Egkarchos (konsnosl@gmail.com) -->\n";
	
	// Write time to the file.
	{
		const tm* timePtr = &statics::GetLocalTime();

		wchar_t buffer[50];

		wcsftime(buffer, 50, L"%A %d %B %Y %X", timePtr);

		stringToWrite.append(L"<!-- This xml was exported at ");
		stringToWrite.append(buffer);
		stringToWrite.append(L" -->\n");
		stringToWrite.append(L"<Texs path=\"" + rootFolder->getPath_Parent() + L"\">\n");
	}

	// Generate the xml
	IStringExporter* exporter = new xmlexporter();
	stringToWrite.append(exporter->getStringElement(*rootFolder));
	delete exporter;

	// Check for invalid characters
	cout << "Validating xml..." << endl;
	{
		size_t index = 0;
		
		// Replace the & symbol
		while (true)
		{
			// Locate the substring to replace.
			index = stringToWrite.find(L"&", index);
			if (index == wstring::npos)
				break;

			// Make the replacement.
			stringToWrite.replace(index, 1, L"&amp;");

			index += 5;
		}
	}

	stringToWrite.append(L"</Texs>\n");

	return stringToWrite;
}

void exporter::printFormatted(ostream& stream, char* chars, int count) const
{
	stream << std::setw(26) << std::left << chars << std::right << std::setw(2) << "|" << std::setw(6) << count << std::setw(3) << "|"  << endl;
}

/** Removes all spaces from the wstring and returns the value. */
wstring removeSpaces(wstring str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace));

	return str;
}

void exporter::printStats(double timeDuration) const
{
	cout << endl;
	cout << std::setfill('-') << std::setw(38) << " " << endl;
	cout << std::setfill(' ');
	printFormatted(cout, "| Images", fileImg_count);
	printFormatted(cout, "| Diffuse maps", fileDif_count);
	printFormatted(cout, "| Bump maps", fileBmp_count);
	printFormatted(cout, "| Normal maps", fileNormal_count);
	printFormatted(cout, "| Glossiness maps", fileGloss_count);
	printFormatted(cout, "| Height maps", fileHeight_count);
	printFormatted(cout, "| Specular maps", fileSpec_count);
	printFormatted(cout, "| Roughness maps", fileRough_count);
	printFormatted(cout, "| Metalness maps", fileMetal_count);
	printFormatted(cout, "| Unknown maps", fileUnkn_count);
	printFormatted(cout, "| Other files", fileOther_count);
	printFormatted(cout, "| Directories", dir_count);
	printFormatted(cout, "| Others", other_count);
	printFormatted(cout, "| Errors", err_count);
	cout << std::setfill('-') << std::setw(38) << " " << endl;
	cout << std::setfill(' ') << std::setw(0);

	cout << "\nProgram finished after " << timeDuration << " seconds." << endl << endl;
}

void exporter::saveStats(double timeDuration, clock_t startTime)
{
	const tm* timePtr = &statics::GetLocalTime();
	
	// Generate a log file with the date on its name.
	ofstream fileLog(wstring(statics::currentPath) + L"\\log_" + to_wstring(timePtr->tm_year + 1900) + L"_" + to_wstring(timePtr->tm_yday) + L"_" + to_wstring(timePtr->tm_hour) + L"_" + to_wstring(timePtr->tm_min) + L"_" + to_wstring(timePtr->tm_sec) + L".txt");

	cout << "Generating log file..." << endl;

	wstring stringToWrite = L"Generated by TexturesXMLExporter, a tool built by Konstantinos Egkarchos (konsnosl@gmail.com)\n";

	// Write time to the file.
	{
		wchar_t buffer[50];

		wcsftime(buffer, 50, L"%A %d %B %Y %X", timePtr);

		stringToWrite.append(L"This log was exported at ");
		stringToWrite.append(buffer);
		stringToWrite.append(L" \n");
	}

	stringToWrite.append(L"\nRoot path is ").append(statics::startingPath).append(L"\nThumbnails directory is ").append(*statics::thumbnailsPath).append(L"\n");

	fileLog << statics::to_utf8(stringToWrite);

	fileLog << endl;
	fileLog << std::setfill('-') << std::setw(38) << " " << endl;
	fileLog << std::setfill(' ');
	printFormatted(fileLog, "| Images", fileImg_count);
	printFormatted(fileLog, "| Diffuse maps", fileDif_count);
	printFormatted(fileLog, "| Bump maps", fileBmp_count);
	printFormatted(fileLog, "| Normal maps", fileNormal_count);
	printFormatted(fileLog, "| Glossiness maps", fileGloss_count);
	printFormatted(fileLog, "| Height maps", fileHeight_count);
	printFormatted(fileLog, "| Specular maps", fileSpec_count);
	printFormatted(fileLog, "| Roughness maps", fileRough_count);
	printFormatted(fileLog, "| Metalness maps", fileMetal_count);
	printFormatted(fileLog, "| Unknown maps", fileUnkn_count);
	printFormatted(fileLog, "| Other files", fileOther_count);
	printFormatted(fileLog, "| Directories", dir_count);
	printFormatted(fileLog, "| Others", other_count);
	printFormatted(fileLog, "| Errors", err_count);
	fileLog << std::setfill('-') << std::setw(38) << " " << endl;
	fileLog << std::setfill(' ') << std::setw(0);

	fileLog << "\nProgram finished after " << timeDuration << " seconds." << endl << endl;

	fileLog.close();
}

exporter::~exporter()
{
	//rootFolder->destroy();
}
