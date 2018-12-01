#include "StdAfx.h"
#include "JsonObject.h"

JsonObject::JsonObject(void)
{
}


JsonObject::~JsonObject(void)
{
}

#pragma data_seg("shared")
JsonObjectCreator& JsonObjectCreator::Inst()
{
	static JsonObjectCreator Creator;
	return Creator;
}
#pragma data_seg()
