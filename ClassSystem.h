#pragma once
#include "ClassData.h"
#include <list>
using namespace std;

class ClassSystem
{
public:
	ClassSystem(void);
	~ClassSystem(void);
	
	void GenerateClasses(const CString &strFileName);
	
private:
	ClassData *FindSameClassData(const ClassData &classData);
	ClassData *FindSimilarClassData(const ClassData &classData);
	CString GetFileContent(const CString &strFileName);
	void GenerateClasses(Json::Value &jsonValue, const CString &className, Json::Value *pJsonArray);
	void GenerateDefaultClasses();
	void GenerateClassFiles(const CString &strDir, const CString &strNameSpace);
	int FindSameClassGroup(const CString &className);
	void DealWithSameGroup();
	void ReplaceFieldName(const CString &oldName, const CString &newName);

	static Json::Value *GetNotNULLItemInArray(const CString &variableName, Json::Value &jsonArray);
	static Json::Value *GetNotEmptyArray(const CString &variableName, Json::Value &jsonArray);

public:
	list<ClassData> ClassDatas;
	vector<vector<CString>> SameClassGroup;
};

