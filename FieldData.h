#pragma once

class FieldData
{
public:
	FieldData(void);
	FieldData(Json::ValueType type, Json::ValueType itemInArrayType, const CString &typeName, const CString &variableName);
	~FieldData(void);

	bool operator < (const FieldData &fieldData) const;
	bool operator == (const FieldData &fieldData) const;
	bool IsSimilar(const FieldData &fieldData) const;

	CString GetTypeName() const;
	CString GetLine() const;
	CString GetJsonLine();
	void Update(const FieldData &fieldData);

	static CString MakeFirstUpper(const CString &strInput);
	static CString GetClassName(const CString &strInput, bool isArray);

public:
	Json::ValueType Type;
	Json::ValueType ItemInArrayType;
	CString TypeName;
	CString VariableName;
};

