#pragma once
#include "FieldData.h"
#include <list>
#include <set>
using namespace std;

class ClassData
{
public:
	ClassData(void);
	ClassData(const CString &name);
	~ClassData(void);

	bool IsSame(const ClassData &classData) const;
	bool IsSimilar(const ClassData &classData) const;
	void Update(const ClassData &classData);

	void GenerateClassFiles(const CString &strDir, const CString &strNameSpace);
	void ReplaceFieldName(const CString &oldName, const CString &newName);

private:
	void GenerateHeaderFile(const CString &strDir, const CString &strNameSpace);
	void GenerateCPPFile(const CString &strDir, const CString &strNameSpace);
	set<CString> GetObjectTypeNames() const;
	vector<FieldData *> GetObjectFieldDatas();

public:
	CString Name;
	list<FieldData> FieldDatas;
};

