#include "xmlexporter.h"

using namespace texturesExporter;

namespace exporters
{
	xmlexporter::xmlexporter()
		:indents(1)
	{
	}

	xmlexporter::~xmlexporter()
	{
	}

	const wstring xmlexporter::getStringElement(const map& _map)
	{
		wstring elem = _map.getType().getString();
		wstring xmlElem(L"<map type=\"" + elem + L"\" thumb=\"" + _map.getThumbPath().wstring() + L"\">" + _map.getCurPath().wstring() + L"</map>");

		return xmlElem;
	}

	const wstring xmlexporter::getStringElement(const material& _mat)
	{
		wstring elem;

		for (int i = 0; i < indents; i++)
			elem.append(L"\t");
		elem += L"<material name=\"" + _mat.getName() + L"\">\n";

		indents++;

		/// Add maps
		size_t mapsSize = _mat.getMapsAmount();
		for (size_t m = 0; m < mapsSize; m++)
		{
			for (int t = 0; t < indents; t++)
				elem.append(L"\t");
			elem += getStringElement(_mat.getMap(m)) + L"\n";
		}
		/// ~Add maps

		indents--;

		for (int i = 0; i < indents; i++)
			elem.append(L"\t");
		elem += L"</material>\n";
		return elem;
	}

	const wstring xmlexporter::getStringElement(const folder& _folder)
	{
		wstring elem;

		// Add indents
		for (int i = 0; i < indents; i++)
			elem.append(L"\t");
		elem += L"<folder name=\"" + _folder.getName() + L"\">\n";

		indents++;

		/// Add subdirs
		size_t foldersAmount = _folder.getFoldersAmount();
		for (size_t i = 0; i < foldersAmount; i++)
			elem += getStringElement(_folder.getFolder(i));

		/// Add materials
		size_t matsAmount = _folder.getMatsAmount();
		for (size_t i = 0; i < matsAmount; i++)
			elem += getStringElement(_folder.getMaterial(i));

		indents--;

		for (int i = 0; i < indents; i++)
			elem.append(L"\t");
		elem += L"</folder>\n";

		return elem;
	}
}