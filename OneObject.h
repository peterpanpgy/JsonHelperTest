#pragma once
#include "JsonObject.h"
#include "JsonObjects.h"
#include <vector>
using namespace std;
class People;

class OneObject : public JsonObject
{
	DECLARE_JSONOBJECT(OneObject)

public:
	OneObject(void);
	~OneObject(void);

public:
	bool aBoolInObject;
	int aIntInObject;
	double aDoubleInObject;
	unsigned int aUIntInObject;
	CString aStringInObject;
	vector<CString> anArrayInObject;
	JsonObjects<People *> objectObjectArray;
};

