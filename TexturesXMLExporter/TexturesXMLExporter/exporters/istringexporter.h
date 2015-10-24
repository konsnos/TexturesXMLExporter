/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>
#include "../folder.h"
#include "../material.h"
#include "../map.h"

using namespace std;

namespace exporters
{
	/* Interface which represents an exporter. */
	class IStringExporter
	{
	public:
		virtual ~IStringExporter(){ };
		/* Creates a string representation of a map and returns it. */
		virtual const string getStringElement(const map&) = 0;
		/* Creates a string representation of a material and returns it. */
		virtual const string getStringElement(const material&) = 0;
		/* Creates a string representation of a folder and returns it. */
		virtual const string getStringElement(const folder&) = 0;
	};
}