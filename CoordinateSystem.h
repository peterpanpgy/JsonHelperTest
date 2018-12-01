#pragma once
#include "JsonObject.h"
#include "CoordinateSystem.h"

class CoordinateSystem : public JsonObject
{
	DECLARE_JSONOBJECT(CoordinateSystem)

public:
	CoordinateSystem(void);
	~CoordinateSystem(void);

public:
	CString Origin;
	CString X;
	CString Y;
	CString Z;
};

