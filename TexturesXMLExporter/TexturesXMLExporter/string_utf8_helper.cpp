#include "string_utf8_helper.h"

namespace texturesExporter
{
	const wstring string_utf8_helper::utf8_to_wstring(const string & str)
	{
		wstring_convert<codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}

	const string string_utf8_helper::wstring_to_utf8(const wstring & str)
	{
		wstring_convert<codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}
}