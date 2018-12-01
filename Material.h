#pragma once
#include "JsonObject.h"

class Material : public JsonObject
{
	DECLARE_JSONOBJECT(Material)

public:
	Material(void);
	~Material(void);
};

