#include "StdAfx.h"
#include "TestModel.h"
#include "JsonHelper.h"
#include "OneObject.h"

IMPLEMENT_JSONOBJECT(TestModel, "TestModel")

TestModel::TestModel(void)
{
	anObject = NULL;
}

TestModel::~TestModel(void)
{
	delete anObject;
}

void TestModel::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("aBool", aBool);
	jsonHelper.Json("aInt", aInt);
	jsonHelper.Json("aDouble", aDouble);
	jsonHelper.Json("aUInt", aUInt);
	jsonHelper.Json("aString", aString);
	jsonHelper.Json("anArray", anArray);
	jsonHelper.Json("anObjectArray", "Animal", anObjectArray);
	jsonHelper.Json("anObject", "OneObject", (JsonObject **)&anObject);
}