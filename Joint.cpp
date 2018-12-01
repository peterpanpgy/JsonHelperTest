#include "StdAfx.h"
#include "Joint.h"
#include "JsonHelper.h"

IMPLEMENT_JSONOBJECT(Joint, "Joint")

Joint::Joint(void)
{
}

Joint::~Joint(void)
{
}

void Joint::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Key", Key);
	jsonHelper.Json("IsMajorJoint", IsMajorJoint);
	jsonHelper.Json("IsMemberEndJoint", IsMemberEndJoint);
	jsonHelper.Json("IsSecondaryJoint", IsSecondaryJoint);
	jsonHelper.Json("Reactions", Reactions);
	jsonHelper.Json("Deflections", Deflections);
	jsonHelper.Json("JointTypes", JointTypes);
	jsonHelper.Json("JointCoordinate", JointCoordinate);
}
