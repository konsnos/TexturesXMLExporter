#pragma once

#include <string>
#include <vector>

#include "map.h"

using namespace std;

/* A material is a list of maps. */
class material
{
public:
	material(const string &newName, map * newMap);
	~material();

	/* Adds a map to the list of maps for this material. */
	void addMap(map * newMap);
	/* Returns the xml string of this material. */
	const string getXMLElement() const;
	/* Returns the name of the material. */
	const string getName() const;
private:
	/* Name of the material. */
	string name;
	/* List of maps contained to this material. */
	vector<map*> maps;
};

