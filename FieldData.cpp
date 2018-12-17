#include "StdAfx.h"
#include "FieldData.h"

FieldData::FieldData(void)
{
}

FieldData::FieldData(Json::ValueType type, Json::ValueType itemInArrayType, const CString &typeName, const CString &variableName)
	: Type(type)
	, ItemInArrayType(itemInArrayType)
	, TypeName(typeName)
	, VariableName(variableName)
{
}

FieldData::~FieldData(void)
{
}

bool FieldData::operator < (const FieldData &fieldData) const
{
	return Type < fieldData.Type

		|| Type == fieldData.Type
		&& ItemInArrayType < fieldData.ItemInArrayType

		|| Type == fieldData.Type
		&& ItemInArrayType == fieldData.ItemInArrayType
		&& TypeName < fieldData.TypeName

		|| Type == fieldData.Type
		&& ItemInArrayType == fieldData.ItemInArrayType
		&& TypeName == fieldData.TypeName
		&& VariableName < fieldData.VariableName;
}

bool FieldData::operator == (const FieldData &fieldData) const
{
	return Type == fieldData.Type
		&& ItemInArrayType == fieldData.ItemInArrayType
		&& TypeName == fieldData.TypeName
		&& VariableName == fieldData.VariableName;
}

bool FieldData::IsSimilar(const FieldData &fieldData) const
{
	return VariableName == fieldData.VariableName
		&& TypeName == fieldData.TypeName
		&& (Type == fieldData.Type
		|| Type == Json::realValue && fieldData.Type == Json::intValue
		|| Type == Json::intValue && fieldData.Type == Json::realValue)
		&& (Type != Json::arrayValue
		|| ItemInArrayType == fieldData.ItemInArrayType
		|| ItemInArrayType == Json::realValue && fieldData.ItemInArrayType == Json::intValue
		|| ItemInArrayType == Json::intValue && fieldData.ItemInArrayType == Json::realValue);
}

void FieldData::Update(const FieldData &fieldData)
{
	if (!IsSimilar(fieldData)) return;
	if (Type == Json::intValue && fieldData.Type == Json::realValue)
		Type = Json::realValue;
	if (ItemInArrayType == Json::intValue && fieldData.ItemInArrayType == Json::realValue)
		ItemInArrayType = Json::realValue;
}

CString GetSimpleTypeName(Json::ValueType type)
{
	if (type == Json::booleanValue)
		return "bool";
	else if (type == Json::realValue)
		return "double";
	else if (type == Json::intValue)
		return "int";
	else if (type == Json::uintValue)
		return "unsigned int";
	else if (type == Json::stringValue)
		return "CString";
	else
		return "";
}

CString FieldData::GetTypeName() const
{
	CString typeName = GetSimpleTypeName(Type);
	if (typeName != "") return typeName;

	if (Type == Json::objectValue || Type == Json::nullValue)
		return TypeName + "*";
	else if (Type == Json::arrayValue)
	{
		if (ItemInArrayType == Json::objectValue)
			return "JsonObjects<" + TypeName + ">";
		else
		{
			return "vector<" + GetSimpleTypeName(ItemInArrayType) + ">";
		}
	}
	else
	{
		ASSERT(false);
		return "";
	}
}

CString FieldData::GetLine() const
{
	return GetTypeName() + " " + VariableName + ";";
}

CString FieldData::MakeFirstUpper(const CString &strInput)
{
	if (strInput.GetLength() == 0) return strInput;
	CString first = strInput.Left(1);
	first.MakeUpper();
	return first + strInput.Right(strInput.GetLength() - 1);
}

CString FieldData::MakeField(const CString &strInput)
{
	return "m_" + strInput;
}

CString FieldData::GetClassName(const CString &strInput, bool isArray, vector<CString> existingNames)
{
	CString className = strInput;
	if (className.Find("axis") != -1
		|| className.Find("Axis") != -1)
	{
		className = "Vector3D";
	}

	if (className == "origin"
		|| className.Find("Point") != -1
		|| className.Find("point") != -1)
	{
		className = "Point3D";
	}

	if (className.Find("Joint") != -1
		|| className.Find("joint") != -1)
	{
		className = "Joint";
	}
	if (className.Find("Restraint") != -1
		|| className.Find("restraint") != -1)
	{
		className = "Restraint";
	}

	if (isArray)
	{
		if (className.GetLength() > 3 && className.Right(3) == "ies")
			className = className.Left(className.GetLength() - 3) + "y";
		else if (className.GetLength() > 4 && (className.Right(4) == "shes" || className.Right(4) == "ches"))
			className = className.Left(className.GetLength() - 2);
		else if (className.GetLength() > 1 && className.Right(1) == "s")
			className = className.Left(className.GetLength() - 1);
	}

	className = MakeFirstUpper(className);

	while(true)
	{
		bool found = false;
		for (int i = 0; i < (int)existingNames.size(); ++i)
		{
			if (existingNames[i] == className)
			{
				found = true;
				break;
			}
		}

		if (!found) return className;

		int pos = className.ReverseFind('_');
		if (pos == -1) 
		{
			className = className + "_1";
		}
		else
		{
			CString strIndex = className.Right(className.GetLength() - pos - 1);
			int index = 1;
			sscanf(strIndex, "%d", &index);
			++index;
			strIndex.Format("%d", index);
			className = className.Left(pos + 1) + strIndex;
		}
	}

	return className;
}

CString FieldData::StripField(const CString &strInput)
{
	if (strInput.GetLength() > 2 && strInput.Left(2) == "m_")
		return strInput.Right(strInput.GetLength() - 2);
	return strInput;
}

CString FieldData::GetJsonLine()
{
	if (Type == Json::objectValue || Type == Json::nullValue)
		return "jsonHelper.Json(\"" + StripField(VariableName) + "\", \"" + TypeName + "\", (JsonObject **)&" + VariableName + ");";
	else if (Type == Json::arrayValue && ItemInArrayType == Json::objectValue)
		return "jsonHelper.Json(\"" + StripField(VariableName) + "\", \"" + TypeName + "\", " + VariableName + ");";
	else
		return "jsonHelper.Json(\"" + StripField(VariableName) + "\", " + VariableName + ");";
}
