/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>
#include <vector>

#include "map.h"

using namespace std;

namespace texturesExporter
{
	/* A material is a list of maps. */
	class material
	{
	public:
		material(const wstring& newName, map* newMap);
		~material();

		/* Adds a map to the list of maps for this material. */
		void addMap(map* newMap);
		/* Returns the name of the material. */
		const wstring getName() const;
		/* Returns the amount of maps contained in this material. */
		const size_t getMapsAmount() const;
		/* Returns a reference to a map at a specified index. */
		const map& getMap(const int index) const;

		/* Free up taken memory from this material. */
		void destroy();
	private:
		/* Name of the material. */
		wstring name;
		/* List of maps contained to this material. */
		vector<map*> maps;
	};
}