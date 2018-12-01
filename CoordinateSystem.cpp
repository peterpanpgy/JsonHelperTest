#include "StdAfx.h"
#include "CoordinateSystem.h"
#include "JsonHelper.h"

CoordinateSystem::CoordinateSystem(void)
{
}

CoordinateSystem::~CoordinateSystem(void)
{
}

IMPLEMENT_JSONOBJECT(CoordinateSystem, "CoordinateSystem")

void CoordinateSystem::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Origin", Origin);
	jsonHelper.Json("X", X);
	jsonHelper.Json("Y", Y);
	jsonHelper.Json("Z", Z);
}
