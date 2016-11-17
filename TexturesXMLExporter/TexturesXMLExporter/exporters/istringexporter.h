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
using namespace texturesExporter;

namespace exporters
{
	/* Interface which represents an exporter. */
	class IStringExporter
	{
	public:
		virtual ~IStringExporter(){ };
		/* Creates a wstring representation of a map and returns it. */
		virtual const wstring getStringElement(const map&) = 0;
		/* Creates a wstring representation of a material and returns it. */
		virtual const wstring getStringElement(const material&) = 0;
		/* Creates a wstring representation of a folder and returns it. */
		virtual const wstring getStringElement(const folder&) = 0;
	};
}