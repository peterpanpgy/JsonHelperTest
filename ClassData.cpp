#include "StdAfx.h"
#include "ClassData.h"

ClassData::ClassData(void)
{
}

ClassData::ClassData(const CString &name)
	: Name(name)
{
}

ClassData::~ClassData(void)
{
}

bool ClassData::IsSame(const ClassData &classData) const
{
	if (FieldDatas.size() != classData.FieldDatas.size())
		return false;

	list<FieldData>::const_iterator it = FieldDatas.begin();
	list<FieldData>::const_iterator itOther = classData.FieldDatas.begin();
	for (; it != FieldDatas.end(); ++it, ++itOther)
	{
		if (!((*it) == (*itOther))) return false;
	}

	return true;
}

bool ClassData::IsSimilar(const ClassData &classData) const
{
	if (FieldDatas.size() != classData.FieldDatas.size())
		return false;

	list<FieldData>::const_iterator it = FieldDatas.begin();
	list<FieldData>::const_iterator itOther = classData.FieldDatas.begin();
	for (; it != FieldDatas.end(); ++it, ++itOther)
	{
		if (!(it->IsSimilar(*itOther))) return false;
	}

	return true;
}

void ClassData::Update(const ClassData &classData)
{
	list<FieldData>::iterator it = FieldDatas.begin();
	list<FieldData>::const_iterator itOther = classData.FieldDatas.begin();
	for (; it != FieldDatas.end(); ++it, ++itOther)
	{
		(*it).Update(*itOther);
	}
}

void ClassData::GenerateClassFiles(const CString &strDir, const CString &strNameSpace)
{
	GenerateHeaderFile(strDir, strNameSpace);
	GenerateCPPFile(strDir, strNameSpace);
}

set<CString> ClassData::GetObjectTypeNames() const
{
	set<CString> objectTypeNames;
	for (list<FieldData>::const_iterator it = FieldDatas.begin(); it != FieldDatas.end(); ++it)
	{
		if (it->Type == Json::objectValue || it->Type == Json::nullValue
			|| it->Type == Json::arrayValue
			&& it->ItemInArrayType == Json::objectValue)
		{
			objectTypeNames.insert(it->TypeName);
		}
	}
	return objectTypeNames;
}

vector<FieldData *> ClassData::GetObjectFieldDatas()
{
	vector<FieldData *> objectFieldDatas;
	for (list<FieldData>::iterator it = FieldDatas.begin(); it != FieldDatas.end(); ++it)
	{
		if (it->Type == Json::objectValue || it->Type == Json::nullValue)
		{
			objectFieldDatas.push_back(&(*it));
		}
	}
	return objectFieldDatas;
}

void ClassData::GenerateHeaderFile(const CString &strDir, const CString &strNameSpace)
{
	CStdioFile file;
	CString strFile = strDir + "\\" + Name + ".h";
	DeleteFile(strFile);
	file.Open(strFile, CFile::modeWrite | CFile::modeCreate);

	file.WriteString("#pragma once\n");
	file.WriteString("#include \"JsonObject.h\"\n");
	file.WriteString("#include \"JsonObjects.h\"\n");
	file.WriteString("#include <vector>\n");
	file.WriteString("using namespace std;\n");

	set<CString> &objectTypeNames = GetObjectTypeNames();
	for (set<CString>::iterator it = objectTypeNames.begin(); it != objectTypeNames.end(); ++it)
	{
		file.WriteString("class " + (*it) + ";\n");
	}

	file.WriteString("\n");
	//file.WriteString("namespace " + strNameSpace + "\n");
	//file.WriteString("{\n");
	file.WriteString("class " + Name + " : public JsonObject\n");
	file.WriteString("{\n");
	file.WriteString("\tDECLARE_JSONOBJECT(" + Name + ")\n");
	file.WriteString("\n");
	file.WriteString("public:\n");
	file.WriteString("\t" + Name + "(void);\n");
	file.WriteString("\t~" + Name + "(void);\n");
	file.WriteString("\n");
	file.WriteString("public:\n");
	for (list<FieldData>::iterator itField = FieldDatas.begin(); itField != FieldDatas.end(); ++itField)
	{
		file.WriteString("\t" + itField->GetLine() + "\n");
	}
	file.WriteString("};\n");
	//file.WriteString("};\n");

	file.Close();
}

void ClassData::GenerateCPPFile(const CString &strDir, const CString &strNameSpace)
{
	CStdioFile file;
	CString strFile = strDir + "\\" + Name + ".cpp";
	DeleteFile(strFile);
	file.Open(strFile, CFile::modeWrite | CFile::modeCreate);

	file.WriteString("#include \"StdAfx.h\"\n");
	file.WriteString("#include \"" + Name + ".h\"\n");
	file.WriteString("#include \"JsonHelper.h\"\n");

	set<CString> &objectTypeNames = GetObjectTypeNames();
	for (set<CString>::iterator it = objectTypeNames.begin(); it != objectTypeNames.end(); ++it)
	{
		file.WriteString("#include \"" + (*it) + ".h\"\n");
	}

	file.WriteString("\n");
	//file.WriteString("namespace " + strNameSpace + "\n");
	//file.WriteString("{\n");

	file.WriteString(Name + "::" + Name + "(void)\n");
	file.WriteString("{\n");
	vector<FieldData *> objectFieldDatas = GetObjectFieldDatas();
	for (vector<FieldData *>::iterator itObject = objectFieldDatas.begin()
		; itObject != objectFieldDatas.end(); ++itObject)
	{
		file.WriteString("\t" + (*itObject)->VariableName + " = NULL;\n"); 
	}
	file.WriteString("}\n");

	file.WriteString("\n");
	file.WriteString(Name + "::~" + Name + "(void)\n");
	file.WriteString("{\n");
	for (vector<FieldData *>::iterator itObject = objectFieldDatas.begin()
		; itObject != objectFieldDatas.end(); ++itObject)
	{
		file.WriteString("\tdelete " + (*itObject)->VariableName + ";\n"); 
	}
	file.WriteString("}\n");

	file.WriteString("\n");
	file.WriteString("IMPLEMENT_JSONOBJECT(" + Name + ", \"" + Name + "\")\n");

	file.WriteString("\n");
	file.WriteString("void " + Name + "::Json(JsonHelper &jsonHelper)\n");
	file.WriteString("{\n");
	for (list<FieldData>::iterator itField = FieldDatas.begin(); itField != FieldDatas.end(); ++itField)
	{
		file.WriteString("\t" + itField->GetJsonLine() + "\n");
	}
	file.WriteString("}\n");

	//file.WriteString("};\n");

	file.Close();
}

void ClassData::ReplaceFieldName(const CString &oldName, const CString &newName)
{
	for (list<FieldData>::iterator it = FieldDatas.begin(); it != FieldDatas.end(); ++it)
	{
		if (it->TypeName == oldName)
			it->TypeName = newName;
	}
}
