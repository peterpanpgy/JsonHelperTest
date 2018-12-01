#include "StdAfx.h"
#include "Animal.h"
#include "JsonHelper.h"

IMPLEMENT_JSONOBJECT(Animal, "Animal")

Animal::Animal(void)
{
}


Animal::~Animal(void)
{
}


void Animal::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Name", Name);
}