/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>
#include <vector>

#include "map.h"
#include "ixmlexpressed.h"

using namespace std;

/* A material is a list of maps. */
class material : Ixmlexpressed
{
public:
	material(const string& newName, map* newMap);
	~material();

	/* Adds a map to the list of maps for this material. */
	void addMap(map* newMap);
	/* Generate thumbs from maps. */
	void generateMapsThumbs();
	/* Returns the xml string of this material. */
	const string getXMLElement() const;
	/* Returns the name of the material. */
	const string getName() const;

	/* Free up taken memory from this material. */
	void destroy();
private:
	/* Name of the material. */
	string name;
	/* List of maps contained to this material. */
	vector<map*> maps;
};

