/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
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
	/* Trims single material folders. Moves the material to the parent one. */
	void trimSingleMatFolders();
	/* Returns the xml of this folder. */
	const string getXMLElement() const;
	/* Remove the last material from the list and return it. */
	material * popMaterial();
	/* Returns the path of the folder. */
	string getPath() const;
	/* Free up taken memory from variables of this folder. */
	void destroy();

private:
	path curPath;
	/* Directories contained in this directory. */
	vector<folder*> folders;
	/* Materials contained in this directory. */
	vector<material*> mats;
	/* Recursively creates the list of materials and folders in this directory and all subdirectories. */
	void listDir();
};