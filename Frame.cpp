#include "StdAfx.h"
#include "Frame.h"
#include "JsonHelper.h"
#include "CoordinateSystem.h"
#include "GravityLoadCaseKey.h"
#include "Material.h"
#include "FrameSegment.h"

Frame::Frame(void)
{
	CoordinateSystem = NULL;
	GravityLoadCaseKey = NULL;
}

Frame::~Frame(void)
{
	delete CoordinateSystem;
	delete GravityLoadCaseKey;
}

IMPLEMENT_JSONOBJECT(Frame, "Frame")

void Frame::Json(JsonHelper &jsonHelper)
{
	jsonHelper.Json("Key", Key);
	jsonHelper.Json("LocatedAlong", LocatedAlong);
	jsonHelper.Json("CoordinateSystem", "CoordinateSystem", (JsonObject **)&CoordinateSystem);
	jsonHelper.Json("GravityLoadCaseKey", "GravityLoadCaseKey", (JsonObject **)&GravityLoadCaseKey);
	jsonHelper.Json("GravityDirection", GravityDirection);
	jsonHelper.Json("FrameType", FrameType);
	jsonHelper.Json("SymmetryForced", SymmetryForced);
	jsonHelper.Json("UseMinimumMomentForConnection", UseMinimumMomentForConnection);
	jsonHelper.Json("IsOversizedHole", IsOversizedHole);
	jsonHelper.Json("IsWeldedWasherUsed", IsWeldedWasherUsed);
	jsonHelper.Json("Material", "Material", (JsonObject **)&Material);
	jsonHelper.Json("Segments", "FrameSegment", FrameSegments);
}