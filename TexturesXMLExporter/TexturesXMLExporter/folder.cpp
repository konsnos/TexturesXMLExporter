/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#include "folder.h"
#include "statics.h"
#include "exporter.h"

#include "boost\filesystem\path.hpp"
#include "boost\filesystem\operations.hpp"

namespace texturesExporter
{
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
				if (path.filename() != statics::thumbnailsFolderName && path.filename() != statics::texturesShowcaserFolderName)	// Ignore thumbnails folder.
				{
					folders.push_back(new folder(path));
				}
			}
			else if (is_regular_file(path))
			{
				if (statics::isImgSffx(path.extension().generic_wstring()))
				{
					map* newMap = new map(path, statics::getImgTypeBySuffix(path.extension().generic_wstring()));

					/// Check if material exists.
					size_t length = mats.size();
					wstring matName = newMap->getName();
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

	material* folder::popMaterial()
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

	material* folder::getMaterials()
	{
		return mats[0];
	}

	const size_t folder::getMatsAmount() const
	{
		return mats.size();
	}

	const size_t folder::getFoldersAmount() const
	{
		return folders.size();
	}

	const size_t folder::getMatsRecAmount() const
	{
		int amount = 0;

		amount += getMatsAmount();

		for (auto& folder : folders)
			amount += folder->getMatsRecAmount();

		return amount;
	}

	const material& folder::getMaterial(const int index) const
	{
		return *mats[index];
	}

	const folder& folder::getFolder(const int index) const
	{
		return *folders[index];
	}

	void folder::addMat(material* newMat)
	{
		mats.push_back(newMat);
	}

	const wstring folder::getName() const
	{
		return curPath.filename().generic_wstring();
	}

	void folder::trimSingleMatFolders()
	{
		for (std::vector<folder*>::iterator it = folders.begin(); it != folders.end();)
		{
			(*it)->trimSingleMatFolders();

			int matsRecAmount = (*it)->getMatsRecAmount();
			if (matsRecAmount == 0)	// If folder doesn't contain any material is erased.
			{
				(*it)->destroy();
				delete * it;
				it = folders.erase(it);
			}
			else if (matsRecAmount == 1 && (*it)->getMatsAmount() == 1)	// If folder contains just one material, this material gets pushed to the parent folder. Then the folder is erased
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

	wstring folder::getPath() const
	{
		return curPath.wstring();
	}

	wstring folder::getPath_Parent() const
	{
		if (curPath.has_parent_path())
		{
			return curPath.parent_path().wstring();
		}
		return L"";
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
}