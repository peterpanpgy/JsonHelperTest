#pragma once
#include "JsonObject.h"
#include <vector>
using namespace std;

class Joint : public JsonObject
{
	DECLARE_JSONOBJECT(Joint)

public:
	Joint(void);
	~Joint(void);

public:
	CString Key;
	bool IsMajorJoint;
	bool IsMemberEndJoint;
	bool IsSecondaryJoint;
	vector<double> Reactions;
	vector<double> Deflections;
	vector<CString> JointTypes;
	CString JointCoordinate;
};

