#include "xmlexporter.h"

using namespace exporters;

xmlexporter::xmlexporter()
	:indents(1)
{
}


xmlexporter::~xmlexporter()
{
}

const string xmlexporter::getStringElement(const map& _map)
{
	string elem = _map.getType().getString();
	string xmlElem("<map type=\"" + elem + "\"" + " thumb=\"" + _map.getThumbPath().string() + "\">" + _map.getCurPath().string() + "</map>");

	return xmlElem;
}

const string xmlexporter::getStringElement(const material& _mat)
{
	string elem;

	for (int i = 0; i < indents; i++)
		elem.append("\t");
	elem += "<material name=\"" + _mat.getName() + "\">\n";

	indents++;

	/// Add maps
	size_t mapsSize = _mat.getMapsAmount();
	for (size_t m = 0; m < mapsSize; m++)
	{
		for (int t = 0; t < indents; t++)
			elem.append("\t");
		elem += getStringElement(_mat.getMap(m)) + "\n";
	}
	/// ~Add maps

	indents--;

	for (int i = 0; i < indents; i++)
		elem.append("\t");
	elem += "</material>\n";
	return elem;
}

const string xmlexporter::getStringElement(const folder& _folder)
{
	string elem;

	// Add indents
	for (int i = 0; i < indents; i++)
		elem.append("\t");
	elem += "<folder name=\"" + _folder.getName() + "\">\n";

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
		elem.append("\t");
	elem += "</folder>\n";

	return elem;
}