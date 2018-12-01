#pragma once
#include "JsonObject.h"
#include "JsonObjects.h"
class CoordinateSystem;
class GravityLoadCaseKey;
class Material;
class FrameSegment;

class Frame : public JsonObject
{
	DECLARE_JSONOBJECT(Frame)

public:
	Frame(void);
	~Frame(void);

public:
	CString Key;
	CString LocatedAlong;
	CoordinateSystem *CoordinateSystem;
	GravityLoadCaseKey *GravityLoadCaseKey;
	CString GravityDirection;
	CString FrameType;
	CString SymmetryForced;
	bool UseMinimumMomentForConnection;
	bool IsOversizedHole;
	bool IsWeldedWasherUsed;
	Material *Material;
	JsonObjects<FrameSegment> FrameSegments;
};

