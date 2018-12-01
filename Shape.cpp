#include "StdAfx.h"
#include "Shape.h"
#include "JsonHelper.h"
#include "Frame.h"

Shape::Shape(void)
{
	Frame = NULL;
}


Shape::~Shape(void)
{
	delete Frame;
}

IMPLEMENT_JSONOBJECT(Shape, "Shape")

void Shape::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("AiscSpecYear", AiscSpecYear);
	jsonHelper.Json("DesignMethod", DesignMethod);
	jsonHelper.Json("ManufacturingLocation", ManufacturingLocation);
	jsonHelper.Json("Frame", "Frame", (JsonObject **)&Frame);
}