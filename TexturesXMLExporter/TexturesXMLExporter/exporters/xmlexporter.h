#pragma once

#include "istringexporter.h"

namespace exporters
{
	class xmlexporter : public IStringExporter
	{
	public:
		xmlexporter();
		~xmlexporter();

		/* Creates a wstring representation of a map and returns it. */
		virtual const wstring getStringElement(const map &);
		/* Creates a wstring representation of a material and returns it. */
		virtual const wstring getStringElement(const material &);
		/* Creates a wstring representation of a folder and returns it. */
		virtual const wstring getStringElement(const folder &);

	private:
		int indents;
	};
}