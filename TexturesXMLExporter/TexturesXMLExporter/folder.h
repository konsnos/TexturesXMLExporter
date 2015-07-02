#pragma once

#include <vector>
#include <string>

#include "material.h"

using namespace std;


class folder
{
public:
	folder(path& refPath);
	~folder();

	/* Returns the materials contained in this directory. */
	material * getMaterials();
	/* Returns the count of materials contained in this directory. */
	const int getMatsAmount() const;
	/* Returns the count of materials contained in this directory recursively. */
	const int getMatsRecAmount() const;
	/* Adds a material in the list of materials of this folder. */
	void addMat(material * newMat);
	/* Returns the xml of this folder. */
	const string getXMLElement() const;

private:
	path curPath;
	/* Directories contained in this directory. */
	vector<folder*> folders;
	/* Materials contained in this directory. */
	vector<material*> mats;
	/* Recursively creates the list of materials and folders in this directory and all subdirectories. */
	void listDir();
};

