#pragma once
#include "JsonObject.h"
#include "JsonObjects.h"
#include <vector>
using namespace std;
class Animal;
class OneObject;

class TestModel : public JsonObject
{
	DECLARE_JSONOBJECT(TestModel)

public:
	TestModel(void);
	~TestModel(void);

public:
	bool aBool;
	int aInt;
	double aDouble;
	unsigned int aUInt;
	CString aString;
	vector<int> anArray;
	JsonObjects<Animal *> anObjectArray;
	OneObject *anObject;
};

