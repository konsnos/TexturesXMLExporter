/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include <iostream>

#include "exporter.h"
#include "statics.h"

using namespace std;

/* Stores parameters passed from the command line. */
void handleCMDArguments(int argc, char* argv[])
{
	string arg;
	for (size_t i = 1; i < argc; i++)
	{
		arg = argv[i];

		if (arg == "--help")			// Help
		{
			cout << "\nTexturesXMLExporter\n\nGenerate an xml containing all textures in material format inside their folders.\n\nOptional Arguments\n\n-p\n\tA custom path must be supplied.\n\n--help\n\tDisplay this help and exit\n\n--version\n\tOutput version information and exit" << endl;
			exit(0);
		}
		else if (arg == "--version")	// Version
		{
			cout << "\nTexturesXMLExporter version " << statics::version << endl << endl;
			exit(0);
		}
		else if (arg == "-p")			// Path
		{
			if (i+1 != argc)
			{
				statics::startingPath = argv[++i];
			}
			else
			{
				cout << "Not enough parameters." << endl;
			}
		}
	}

	cout << endl << endl;;
}

/*
	Goal of the program is to generate thumbnails of all textures and an xml with those textures and thumbnails to load into a javascript page in order to be able to preview these files easily.
*/
int main(int argc, char* argv[])
{
	handleCMDArguments(argc, argv);

	cout << "Starting Textures XML Exporter..." << endl << endl;
	
	std::clock_t start;
	double duration;

	start = std::clock();

	exporter exp;

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\nProgram finished after " << duration << " seconds." << endl << endl;

	cin.get();

	exit(0);
}