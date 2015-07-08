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

	for (size_t i = 0; i < paths.size(); i++)
	{
		if (is_directory(paths[i]))
		{
			if (paths[i].filename() != statics::thumbnailsFolderName)	// Ignore thumbnails folder.
			{
				folders.push_back(new folder(paths[i]));
			}
		}
		else if (is_regular_file(paths[i]))
		{
			if (statics::isImgSffx(paths[i].extension().generic_string()))
			{
				map* newMap = new map(paths[i]);

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

	size_t length = folders.size();
	for (size_t i = 0; i < length; i++)
	{
		amount += folders[i]->getMatsRecAmount();
	}

	return amount;
}

void folder::addMat(material * newMat)
{
	mats.push_back(newMat);
}

void folder::iterateMatsForThumbs()
{
	{
		size_t length = folders.size();
		for (size_t f = 0; f < length; f++)
		{
			folders[f]->iterateMatsForThumbs();
		}
	}

	{
		size_t length = mats.size();
		for (size_t f = 0; f < length; f++)
		{
			mats[f]->generateMapsThumbs();
		}
	}
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
	{
		size_t length = folders.size();
		for (size_t f = 0; f < length; f++)
		{
			elem += folders[f]->getXMLElement();
		}
	}
	/// ~Add subdirs

	/// Add materials
	{
		size_t length = mats.size();
		for (size_t f = 0; f < length; f++)
		{
			elem += mats[f]->getXMLElement();
		}
	}
	/// ~Add materials

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