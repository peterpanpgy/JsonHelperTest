#pragma once
#include "JsonObject.h"
class Frame;

class Shape : public JsonObject
{
	DECLARE_JSONOBJECT(Shape)

public:
	Shape(void);
	~Shape(void);

public:
	CString AiscSpecYear;
	CString DesignMethod;
	CString ManufacturingLocation;
	Frame *Frame;
};

