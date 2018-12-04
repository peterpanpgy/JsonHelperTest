#include "StdAfx.h"
#include "ClassSystem.h"

ClassSystem::ClassSystem(void)
{
}

ClassSystem::~ClassSystem(void)
{
}

ClassData *ClassSystem::FindSameClassData(const ClassData &classData)
{
	for (list<ClassData>::iterator it = ClassDatas.begin(); it != ClassDatas.end(); ++it)
	{
		if (it->IsSame(classData))
			return &(*it);
	}
	return NULL;
}

ClassData *ClassSystem::FindSimilarClassData(const ClassData &classData)
{
	for (list<ClassData>::iterator it = ClassDatas.begin(); it != ClassDatas.end(); ++it)
	{
		if (it->IsSimilar(classData))
			return &(*it);
	}
	return NULL;
}

CString ClassSystem::GetFileContent(const CString &strFileName) 
{
  FILE* file = fopen(strFileName, "rb");
  if (!file)
  {
    return CString("");
  }

  fseek(file, 0, SEEK_END);
  long const size = ftell(file);
  unsigned long const usize = static_cast<unsigned long>(size);
  fseek(file, 0, SEEK_SET);

  CString text;
  char* buffer = new char[size + 1];
  buffer[size] = 0;
  if (fread(buffer, 1, usize, file) == usize)
    text = buffer;
  fclose(file);
  delete[] buffer;

  return text;
}

void ClassSystem::DeleteDirectory(const CString &strDir)
{   
	CFileFind finder;
	CString path;
	path.Format("%s/*.*", strDir);
	BOOL bWorking = finder.FindFile(path);
	while(bWorking)
	{
		bWorking = finder.FindNextFile();
		if(finder.IsDirectory() && !finder.IsDots())
		{
			DeleteDirectory(finder.GetFilePath());
			RemoveDirectory(finder.GetFilePath());
		}
		else
		{
			DeleteFile(finder.GetFilePath());
		}
	}
}

void ClassSystem::GenerateClasses(const CString &strFileName)
{
	CString strContent = GetFileContent(strFileName);
	Json::Reader reader;
	Json::Value root;
	JSONCPP_STRING input = strContent;
	bool parsingSuccessful = reader.parse(input.data(), input.data() + input.size(), root, false);
	if (!parsingSuccessful) return;

	ClassDatas.clear();

	int pos = strFileName.ReverseFind('.');
	CString strDir = strFileName.Left(pos);

	DeleteDirectory(strDir);
	CreateDirectory(strDir, NULL);

	pos = strDir.ReverseFind('\\');
	CString strRoot = strDir.Right(strDir.GetLength() - pos - 1);

	GenerateClasses(root, FieldData::MakeFirstUpper(strRoot), NULL);
	DealWithSameGroup();
	GenerateClassFiles(strDir, FieldData::MakeFirstUpper(strRoot));
}

void ClassSystem::DealWithSameGroup()
{
	for(int i = 0; i < (int)SameClassGroup.size(); ++i)
	{
		CString newName = SameClassGroup[i][0];
		for (int j = 1; j < (int)SameClassGroup[i].size(); ++j)
		{
			ReplaceFieldName(SameClassGroup[i][j], newName);
		}
	}
}

void ClassSystem::ReplaceFieldName(const CString &oldName, const CString &newName)
{
	for (list<ClassData>::iterator it = ClassDatas.begin(); it != ClassDatas.end(); ++it)
	{
		it->ReplaceFieldName(oldName, newName);
	}
}

void ClassSystem::GenerateClassFiles(const CString &strDir, const CString &strNameSpace)
{
	for (list<ClassData>::iterator it = ClassDatas.begin(); it != ClassDatas.end(); ++it)
	{
		it->GenerateClassFiles(strDir, strNameSpace);
	}
}

Json::Value *ClassSystem::GetNotNULLItemInArray(const CString &variableName, Json::Value &jsonArray)
{
	for (int i = 0; i < (int)jsonArray.size(); ++i)
	{
		Json::Value &jsonItem = jsonArray[i][variableName];
		if (jsonItem.type() != Json::nullValue)
			return &jsonItem;
	}
	return NULL;
}

Json::Value *ClassSystem::GetNotEmptyArray(const CString &variableName, Json::Value &jsonArray)
{
	for (int i = 0; i < (int)jsonArray.size(); ++i)
	{
		Json::Value &jsonItem = jsonArray[i][variableName];
		if (jsonItem.type() == Json::arrayValue && jsonItem.size() > 0)
			return &jsonItem;
	}
	return NULL;
}

vector<CString> ClassSystem::GetExistingClassNames()
{
	vector<CString> names;
	for (list<ClassData>::iterator it = ClassDatas.begin(); it != ClassDatas.end(); ++it)
	{
		names.push_back(it->Name);
	}
	return names;
}

void ClassSystem::GenerateClasses(Json::Value &jsonValue, const CString &className, Json::Value *pJsonArray)
{
	ClassData classData(className);
	Json::Value::Members jsonMembers = jsonValue.getMemberNames();
	int memberCount = (int)jsonMembers.size();
	for (int iMember = 0; iMember < memberCount; ++iMember)
	{
		CString variableName = jsonMembers[iMember].c_str();
		Json::Value &jsonItem = jsonValue[variableName];

		CString typeName;
		Json::ValueType type = jsonItem.type();
		Json::ValueType itemInArrayType = Json::nullValue;

		if (jsonItem.type() == Json::objectValue)
		{
			typeName = FieldData::GetClassName(variableName, false, GetExistingClassNames());
			GenerateClasses(jsonItem, typeName, NULL);
		}
		else if (jsonItem.type() == Json::nullValue)
		{
			Json::Value *pWorkingJsonItem = &jsonItem;
			if (pJsonArray != NULL)
			{
				pWorkingJsonItem = GetNotNULLItemInArray(variableName, *pJsonArray);
				if (pWorkingJsonItem != NULL)
				{
					type = pWorkingJsonItem->type();
				}
			}
			if (type == Json::objectValue || type == Json::nullValue)
			{
				typeName = FieldData::GetClassName(variableName, false, GetExistingClassNames());
				if (pWorkingJsonItem != NULL)
				{
					GenerateClasses(*pWorkingJsonItem, typeName, pJsonArray);
				}
			}
		}
		else if (jsonItem.type() == Json::arrayValue)
		{
			itemInArrayType = Json::stringValue;
			if (pJsonArray != NULL)
			{
				Json::Value *pJsonItemInArray = GetNotEmptyArray(variableName, *pJsonArray);
				if (pJsonItemInArray != NULL)
				{
					itemInArrayType = (*pJsonItemInArray)[0].type();
					ASSERT(itemInArrayType != Json::nullValue);
					if (itemInArrayType == Json::objectValue)
					{
						typeName = FieldData::GetClassName(variableName, true, GetExistingClassNames());
						GenerateClasses((*pJsonItemInArray)[0], typeName, pJsonItemInArray);
					}
				}
			}
			else if (jsonItem.size() > 0)
			{
				itemInArrayType = jsonItem[0].type();
				ASSERT(itemInArrayType != Json::nullValue);
				if (itemInArrayType == Json::objectValue)
				{
					typeName = FieldData::GetClassName(variableName, true, GetExistingClassNames());
					GenerateClasses(jsonItem[0], typeName, &jsonItem);
				}
			}
		}

		FieldData fieldData(type, itemInArrayType, typeName, FieldData::MakeField(variableName));
		classData.FieldDatas.push_back(fieldData);
	}

	if (classData.FieldDatas.size() == 0)
	{
		ClassDatas.push_back(classData);
		return;
	}
	
	ClassData *pClassData = FindSameClassData(classData);
	if (pClassData == NULL)
	{
		pClassData = FindSimilarClassData(classData);
		if (pClassData != NULL)
		{
			pClassData->Update(classData);
		}
		else
		{
			ClassDatas.push_back(classData);
		}
	}
	else if (pClassData->Name != classData.Name)
	{
		int group = FindSameClassGroup(classData.Name);
		if (group == -1)
		{
			group = FindSameClassGroup(pClassData->Name);
			if (group == -1)
			{
				vector<CString> newGroup;
				newGroup.push_back(pClassData->Name);
				newGroup.push_back(classData.Name);
				SameClassGroup.push_back(newGroup);
			}
			else
			{
				SameClassGroup[group].push_back(classData.Name);
			}
		}
	}
}

int ClassSystem::FindSameClassGroup(const CString &className)
{
	for(int i = 0; i < (int)SameClassGroup.size(); ++i)
	{
		for (int j = 0; j < (int)SameClassGroup[i].size(); ++j)
		{
			if (SameClassGroup[i][j] == className)
			{
				return i;
			}
		}
	}
	return -1;
}
