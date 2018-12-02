#pragma once
#pragma warning(disable:4005)
#pragma warning(disable : 4996)

#include <list>
#include "json/json.h"
#include "JsonObject.h"
#include "JsonObjects.h"
using namespace std;

class JsonHelper
{
public:
	JsonHelper(bool isLoading);
	~JsonHelper(void);

	void SetIsLoading(bool isLoading);

	void ReadFile(const CString& strFileName);
	void WriteFile(const CString& strFileName, bool isHumanFriendly);

	void ReadText(const CString& strInput);
	void WriteText(CString& strOutput, bool isHumanFriendly);

	template<class T>
	void Json(const CString &fieldName, T &value)
	{
		if (m_pCurValue == NULL) return;
		Json((*m_pCurValue)[fieldName], value);
	}

	void Json(const CString &fieldName, const CString &className, JsonObject ** ppJsonObject);

	template<class T>
	void Json(const CString &fieldName, const CString &itemClassName, JsonObjects<T> &objects)
	{
		if (m_pCurValue == NULL) return;
		if (m_bIsLoading)
		{
			objects.Values.clear();
			Json::Value &jsonValue = (*m_pCurValue)[fieldName];
			if (jsonValue.isNull()) return;
			ASSERT(jsonValue.isArray());
			for (int i = 0; i < (int)jsonValue.size(); ++i)
			{
				Json::Value &jsonItem = jsonValue[i];
				T *anObject = NULL;
				Json(jsonItem, itemClassName, (JsonObject **)&anObject);
				objects.Values.push_back(anObject);
			}
		}
		else
		{
			Json::Value &jsonValue = (*m_pCurValue)[fieldName];
			for (int i = 0; i < (int)objects.Values.size(); ++i)
			{
				Json::Value jsonItem;
				Json(jsonItem, itemClassName, (JsonObject **)&objects.Values[i]);
				jsonValue.append(jsonItem);
			}
		}
	}

	template<class T>
	void Json(const CString &fieldName, vector<T> &values)
	{
		if (m_pCurValue == NULL) return;
		if (m_bIsLoading)
		{
			values.clear();
			Json::Value &jsonValue = (*m_pCurValue)[fieldName];
			if (jsonValue.isNull()) return;
			ASSERT(jsonValue.isArray());
			for (int i = 0; i < (int)jsonValue.size(); ++i)
			{
				Json::Value &jsonItem = jsonValue[i];
				T item;
				Json(jsonItem, item);
				values.push_back(item);
			}
		}
		else
		{
			Json::Value &jsonValue = (*m_pCurValue)[fieldName];
			jsonValue = Json::Value(Json::arrayValue);
			for (int i = 0; i < (int)values.size(); ++i)
			{
				Json::Value jsonItem;
				Json(jsonItem, values[i]);
				jsonValue.append(jsonItem);
			}
		}
	}

private:
	JsonHelper();

	void Reset();
	CString GetFileContent(const CString &strFileName);

	void Json(Json::Value &jsonValue, bool &value);
	void Json(Json::Value &jsonValue, double &value);
	void Json(Json::Value &jsonValue, int &value);
	void Json(Json::Value &jsonValue, unsigned int &value);
	void Json(Json::Value &jsonValue, CString &value);
	void Json(Json::Value &jsonValue, const CString &className, JsonObject ** ppJsonObject);

private:
	Json::Value *m_pCurValue;
	list<Json::Value *> m_StatusStack;
	Json::Value m_root;
	bool m_bIsLoading;
};


