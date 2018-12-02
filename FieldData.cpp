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

CString FieldData::GetClassName(const CString &strInput, bool isArray)
{
	if (strInput.Find("axis") != -1
		|| strInput.Find("Axis") != -1)
	{
		return "Vector3D";
	}

	if (strInput == "origin"
		|| strInput.Find("Point") != -1
		|| strInput.Find("point") != -1)
	{
		return "Point3D";
	}

	if (strInput.Find("Joint") != -1
		|| strInput.Find("joint") != -1)
	{
		return "Joint";
	}

	CString str = strInput;

	if (isArray)
	{
		if (strInput.GetLength() > 3 && strInput.Right(3) == "ies")
			str = strInput.Left(strInput.GetLength() - 3) + "y";
		else if (strInput.GetLength() > 4 && (strInput.Right(4) == "shes" || strInput.Right(4) == "ches"))
			str = strInput.Left(strInput.GetLength() - 2);
		else if (strInput.GetLength() > 1 && strInput.Right(1) == "s")
			str = strInput.Left(strInput.GetLength() - 1);
	}

	return MakeFirstUpper(str);
}

CString FieldData::GetJsonLine()
{
	if (Type == Json::objectValue)
		return "jsonHelper.Json(\"" + VariableName + "\", \"" + TypeName + "\", (JsonObject **)&" + VariableName + ");";
	else if (Type == Json::arrayValue && ItemInArrayType == Json::objectValue)
		return "jsonHelper.Json(\"" + VariableName + "\", \"" + TypeName + "\", " + VariableName + ");";
	else
		return "jsonHelper.Json(\"" + VariableName + "\", " + VariableName + ");";
}
