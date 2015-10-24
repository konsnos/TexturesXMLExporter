#pragma once

#include "istringexporter.h"

namespace exporters
{
	class xmlexporter : public IStringExporter
	{
	public:
		xmlexporter();
		~xmlexporter();

		/* Creates a string representation of a map and returns it. */
		virtual const string getStringElement(const map &);
		/* Creates a string representation of a material and returns it. */
		virtual const string getStringElement(const material &);
		/* Creates a string representation of a folder and returns it. */
		virtual const string getStringElement(const folder &);

	private:
		int indents;
	};
}