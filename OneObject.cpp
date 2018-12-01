#include "StdAfx.h"
#include "OneObject.h"
#include "JsonHelper.h"
#include "People.h"

IMPLEMENT_JSONOBJECT(OneObject, "OneObject")

OneObject::OneObject(void)
{
}

OneObject::~OneObject(void)
{
}

void OneObject::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("aBoolInObject", aBoolInObject);
	jsonHelper.Json("aIntInObject", aIntInObject);
	jsonHelper.Json("aDoubleInObject", aDoubleInObject);
	jsonHelper.Json("aUIntInObject", aUIntInObject);
	jsonHelper.Json("aStringInObject", aStringInObject);
	jsonHelper.Json("anArrayInObject", anArrayInObject);
	jsonHelper.Json("objectObjectArray", "People", objectObjectArray);
}