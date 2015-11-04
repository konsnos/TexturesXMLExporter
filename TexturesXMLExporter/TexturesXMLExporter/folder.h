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
	material* getMaterials();
	/* Returns amount of subfolders. */
	const size_t getFoldersAmount() const;
	/* Returns the count of materials contained in this directory. */
	const size_t getMatsAmount() const;
	/* Returns the count of materials contained in this directory recursively. */
	const size_t getMatsRecAmount() const;
	/* Adds a material in the list of materials of this folder. */
	void addMat(material* newMat);
	/* Trims single material folders. Moves the material to the parent one. */
	void trimSingleMatFolders();
	/* Returns the folder name. */
	const wstring getName() const;
	/* Remove the last material from the list and return it. */
	material* popMaterial();
	/* Iterate recursively all materials in folder to generate thumbnails. */
	void iterateMatsForThumbs();
	/* Returns the path of the folder. */
	wstring getPath() const;
	/* Returns the parent path of the folder. */
	wstring getPath_Parent() const;
	/* Returns a reference to a material at a specified index. */
	const material& getMaterial(const int index) const;
	/* Returns a reference to a subfolder at a specified index. */
	const folder& getFolder(const int index) const;
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