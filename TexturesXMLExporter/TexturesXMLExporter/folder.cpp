/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "folder.h"
#include "statics.h"
#include "exporter.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"


folder::folder(path& refPath)
	:curPath(refPath)
{
	listDir();
}


folder::~folder()
{
}

void folder::listDir()
{
	exporter::dir_count++;
	vector<path> paths;

	copy(directory_iterator(curPath), directory_iterator(), back_inserter(paths));

	sort(paths.begin(), paths.end(), &statics::sortByTypeNFilename);

	for (auto& path : paths)
	{
		if (is_directory(path))
		{
			if (path.filename() != statics::thumbnailsFolderName)	// Ignore thumbnails folder.
			{
				folders.push_back(new folder(path));
			}
		}
		else if (is_regular_file(path))
		{
			if (statics::isImgSffx(path.extension().generic_string()))
			{
				map* newMap = new map(path);

				/// Check if material exists.
				size_t length = mats.size();
				string matName = newMap->getMatName();
				bool found = false;
				for (size_t m = 0; m < length; m++)
				{
					if (matName == mats[m]->getName())
					{
						mats[m]->addMap(newMap);
						found = true;
						break;
					}
				}

				if (!found)
				{
					mats.push_back(new material(matName, newMap));
				}
			}
			else
			{
				exporter::fileOther_count++;
			}
		}
		else
		{
			exporter::other_count++;
		}
	}
}

material * folder::popMaterial()
{
	if (mats.size() > 0)
	{
		material * poppedMat = mats.back();
		mats.pop_back();
		return poppedMat;
	}
	else
	{
		return nullptr;
	}
}

material * folder::getMaterials()
{
	return mats[0];
}

const int folder::getMatsAmount() const
{
	return mats.size();
}

const int folder::getMatsRecAmount() const
{
	int amount = 0;

	amount += getMatsAmount();

	for (auto& folder : folders)
		amount += folder->getMatsRecAmount();

	return amount;
}

void folder::addMat(material * newMat)
{
	mats.push_back(newMat);
}

void folder::iterateMatsForThumbs()
{
	for (auto& folder : folders)
		folder->iterateMatsForThumbs();

	for (auto& mat : mats)
		mat->generateMapsThumbs();
}

const string folder::getXMLElement() const
{
	string elem;

	// Add indents
	for (int i = 0; i < exporter::indents; i++)
		elem.append("\t");
	elem += "<folder name=\"" + curPath.filename().generic_string() + "\">\n";

	exporter::indents++;

	/// Add subdirs
	for (auto& folder : folders)
		elem += folder->getXMLElement();

	/// Add materials
	for (auto& mat : mats)
		elem += mat->getXMLElement();

	exporter::indents--;

	for (int i = 0; i < exporter::indents; i++)
		elem.append("\t");
	elem += "</folder>\n";

	return elem;
}

void folder::trimSingleMatFolders()
{
	for (std::vector<folder*>::iterator it = folders.begin(); it != folders.end();)
	{
		(*it)->trimSingleMatFolders();

		int matsRecAmount = (*it)->getMatsRecAmount();
		if (matsRecAmount == 0)
		{
			(*it)->destroy();
			delete * it;
			it = folders.erase(it);
		}
		else if (matsRecAmount == 1 && (*it)->getMatsAmount() == 1)
		{
			material* folderMat = (*it)->popMaterial();
			mats.push_back(folderMat);
			(*it)->destroy();
			delete * it;
			it = folders.erase(it);
		}
		else
		{
			++it;
		}
	}
}

string folder::getPath() const
{
	return curPath.generic_string();
}

void folder::destroy()
{
	// Materials
	for (std::vector<material*>::iterator it = mats.begin(); it != mats.end(); ++it)
	{
		(*it)->destroy();
		delete *it;
	}
	mats.clear();
	// Folders
	for (std::vector<folder*>::iterator it = folders.begin(); it != folders.end(); ++it)
	{
		(*it)->destroy();
		delete *it;
	}
	folders.clear();
}