#include "StdAfx.h"
#include "People.h"
#include "JsonHelper.h"

IMPLEMENT_JSONOBJECT(People, "People")

People::People(void)
{
}


People::~People(void)
{
}


void People::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Name", Name);
}