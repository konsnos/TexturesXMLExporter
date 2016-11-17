#pragma once

#include <string>
#include <codecvt>

using namespace std;

namespace texturesExporter
{
	/* Helper class to convert wstring to string and the reverse, using utf8 encoding.*/
	class string_utf8_helper
	{
	public:
		static const wstring utf8_to_wstring(const string& str);
		static const string wstring_to_utf8(const wstring& str);
	};
}