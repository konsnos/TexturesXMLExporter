/*
* <author>Konstantinos Egkarchos</author>
* <contact>konsnosl@gmail.com</contact>
*/
#pragma once

#include <string>

using namespace std;

namespace texturesExporter
{
	/* Contains information about the type of a texture. */
	class mapType
	{
	public:
		enum Type : int
		{
			Diffuse = 0,
			Bump,
			Normal,
			Glossiness,
			Height,
			Specular,
			Roughness,
			Metalness,
			Emissive,
			Other
		};

		mapType();
		~mapType();

		void assign(Type newType);
		/* Returns the wstring of the type. */
		const wstring getString() const;
		/* Returns the type */
		const Type getType() const;

	private:
		Type type;

		static const wstring types[];
	};
}