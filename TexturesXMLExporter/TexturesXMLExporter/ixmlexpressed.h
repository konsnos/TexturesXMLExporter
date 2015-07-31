#pragma once

#include <string>

using namespace std;

/* Class describes an interface for all classes that need to include xml functions. */
class Ixmlexpressed
{
public:
	virtual ~Ixmlexpressed() {};
	virtual const string getXMLElement() const = 0;
};