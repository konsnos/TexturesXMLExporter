/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include <iostream>

#include "exporter.h"

using namespace std;

int main()
{
	cout << "Starting Textures XML Exporter..." << endl << endl;
	
	std::clock_t start;
	double duration;

	start = std::clock();

	exporter exp;

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\nProgram finished after " << duration << " seconds." << endl << endl;

	cin.get();
}