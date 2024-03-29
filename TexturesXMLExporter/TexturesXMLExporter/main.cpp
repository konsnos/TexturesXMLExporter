/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include <iostream>

#include "exporter.h"
#include "statics.h"

using namespace std;
using namespace texturesExporter;

/* Stores parameters passed from the command line. */
void handleCMDArguments(int argc, wchar_t* argv[])
{
	wstring arg;
	for (int i = 1; i < argc; i++)
	{
		arg = argv[i];

		if (arg == "--help")			// Help
		{
			cout << "\nTexturesXMLExporter\n\nGenerate an xml containing all textures in material format inside their folders.\n\nOptional Arguments\n\n-p\n\tA custom path must be supplied\n\tExample: \"TexturesXMLExporter.exe -p C:\\Users\\Me\\Textures\".\n\tThe thumbs folder and the textures.xml file will be generated to this folder.\n\n--version\n\tOutput version information and exit.\n\n--help\n\tDisplay this help and exit." << endl;
			exit(0);
		}
		else if (arg == "--version")	// Version
		{
			cout << "\nTexturesXMLExporter version " << statics::version << endl << endl;
			exit(0);
		}
		else if (arg == "-p")			// Path
		{
			/*
			Example: "TexturesXMLExporter.exe -p C:\Users\Me\Textures"
			The thumbs folder and the textures.xml file will be generated to this folder.
			*/
			if (i+1 != argc)
			{
				statics::startingPath = argv[++i];
			}
			else
			{
				cout << "Not enough parameters. Check --help ." << endl;
				exit(1);
			}
		}
	}

	cout << endl << endl;;
}

/*
	Goal of the program is to generate thumbnails of all textures and an xml with those textures and thumbnails to load into a javascript page in order to be able to preview these files easily.
*/
int wmain(int argc, wchar_t* argv[])
{
	handleCMDArguments(argc, argv);

	cout << "Starting Textures XML Exporter..." << endl << endl;

	exporter exp;

	cin.get();

	exit(0);
}