#pragma once
#include "JsonObject.h"

class People : JsonObject
{
	DECLARE_JSONOBJECT(People)

public:
	People(void);
	~People(void);

public:
	CString Name;
};

