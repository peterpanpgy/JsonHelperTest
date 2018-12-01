#pragma once
#include "JsonObject.h"
class CoordinateSystem;
class Joint;

class FrameSegment : public JsonObject
{
	DECLARE_JSONOBJECT(FrameSegment)

public:
	FrameSegment(void);
	~FrameSegment(void);

public:
	CString Key;
	CString ItemKey;
	CString SegmentType;
	CString CrossSectionType;
	CString SectionType;
	CString SupportConditionHighEnd;
	CString SupportConditionLowEnd;
	int PinX;
	int PinY;
	int PinZ;
	bool IsExpandable;
	CString Surface;
	CString StartAt;
	CString EndAt;
	CString KneePlateOrientationType;
	bool IsCapPlateExtended;
	bool IsTurned;
	CoordinateSystem *CoordinateSystem;
	Joint *StartJoint;
	Joint *EndJoint;
	Joint *ReferenceJoint;
	vector<CString> LoadCombinationKeys;
};

