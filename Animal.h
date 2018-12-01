#pragma once
#include "JsonObject.h"

class Animal : JsonObject
{
	DECLARE_JSONOBJECT(Animal)

public:
	Animal(void);
	~Animal(void);

public:
	CString Name;
};

