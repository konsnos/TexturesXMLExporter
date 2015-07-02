#pragma once

#include <string>

using namespace std;

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
		Other
	};

	mapType();
	~mapType();

	void assign(Type newType);
	/* Returns the string of the type. */
	const string getString() const;
	/* Returns the type */
	const Type getType() const;
	
private:
	Type type;

	static const string types[];
};

