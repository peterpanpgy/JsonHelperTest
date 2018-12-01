#include "StdAfx.h"
#include "FrameSegment.h"
#include "JsonHelper.h"
#include "CoordinateSystem.h"
#include "Joint.h"

IMPLEMENT_JSONOBJECT(FrameSegment, "FrameSegment")

FrameSegment::FrameSegment(void)
{
	CoordinateSystem = NULL;
	StartJoint = NULL;
	EndJoint = NULL;
	ReferenceJoint = NULL;
}

FrameSegment::~FrameSegment(void)
{
	delete CoordinateSystem;
	delete StartJoint;
	delete EndJoint;
	delete ReferenceJoint;
}

void FrameSegment::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Key", Key);
	jsonHelper.Json("ItemKey", ItemKey);
	jsonHelper.Json("SegmentType", SegmentType);
	jsonHelper.Json("CrossSectionType", CrossSectionType);
	jsonHelper.Json("SectionType", SectionType);
	jsonHelper.Json("SupportConditionHighEnd", SupportConditionHighEnd);
	jsonHelper.Json("SupportConditionLowEnd", SupportConditionLowEnd);
	jsonHelper.Json("PinX", PinX);
	jsonHelper.Json("PinY", PinY);
	jsonHelper.Json("PinZ", PinZ);
	jsonHelper.Json("IsExpandable", IsExpandable);
	jsonHelper.Json("Surface", Surface);
	jsonHelper.Json("StartAt", StartAt);
	jsonHelper.Json("EndAt", EndAt);
	jsonHelper.Json("KneePlateOrientationType", KneePlateOrientationType);
	jsonHelper.Json("IsCapPlateExtended", IsCapPlateExtended);
	jsonHelper.Json("IsTurned", IsTurned);
	jsonHelper.Json("CoordinateSystem", "CoordinateSystem", (JsonObject **)&CoordinateSystem);
	jsonHelper.Json("StartJoint", "Joint", (JsonObject **)&StartJoint);
	jsonHelper.Json("EndJoint", "Joint", (JsonObject **)&EndJoint);
	jsonHelper.Json("ReferenceJoint", "Joint", (JsonObject **)&ReferenceJoint);
	jsonHelper.Json("LoadCombinationKeys", LoadCombinationKeys);
}	
