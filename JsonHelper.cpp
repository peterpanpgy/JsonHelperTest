#include "StdAfx.h"
#include "JsonHelper.h"

JsonHelper::JsonHelper(void)
{
	Reset();
}

JsonHelper::JsonHelper(bool isLoading)
{
	Reset();
	SetIsLoading(isLoading);
}

JsonHelper::~JsonHelper(void)
{
}

void JsonHelper::SetIsLoading(bool isLoading)
{
	m_bIsLoading = isLoading;
	if (isLoading == false)
	{
		m_pCurValue = &m_root;
	}
}

CString JsonHelper::GetFileContent(const CString &strFileName) 
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

void JsonHelper::ReadFile(const CString& strFileName)
{
	Reset();
	m_bIsLoading = true;
	CString strContent = GetFileContent(strFileName);
	ReadText(strContent);
}
 
void JsonHelper::ReadText(const CString& strInput)
{
	Reset();
	m_bIsLoading = true;
	Json::Reader reader;
	JSONCPP_STRING input = strInput;
	bool parsingSuccessful = reader.parse(input.data(), input.data() + input.size(), m_root, false);
	if (!parsingSuccessful) return;
	m_pCurValue = &m_root;
}

void JsonHelper::WriteText(CString& strOutput, bool isHumanFriendly)
{
	m_bIsLoading = false;
	Json::Writer *pWriter = NULL;
	if (isHumanFriendly) pWriter = new Json::StyledWriter;
	else pWriter = new Json::FastWriter;

	strOutput = pWriter->write(m_root).c_str();

	delete pWriter;
}

void JsonHelper::WriteFile(const CString& strFileName, bool isHumanFriendly)
{
	m_bIsLoading = false;
	CString strContent;
	WriteText(strContent, isHumanFriendly);

	FILE* fout = fopen(strFileName, "wt");
	if (!fout) 
	{
		return;
	}
	fprintf(fout, "%s\n", strContent);
	fclose(fout);
}

void JsonHelper::Reset()
{
	m_pCurValue = NULL;
	m_StatusStack.clear();
	m_root.clear();
}

void JsonHelper::Json(const CString &fieldName, const CString &className, JsonObject ** ppJsonObject)
{
	if (m_pCurValue == NULL) return;
	Json((*m_pCurValue)[fieldName], className, ppJsonObject);
}

void JsonHelper::Json(Json::Value &jsonValue, bool &value)
{
	if (m_bIsLoading)
		value = jsonValue.asBool();
	else
		jsonValue = value;
}

void JsonHelper::Json(Json::Value &jsonValue, double &value)
{
	if (m_bIsLoading)
		value = jsonValue.asDouble();
	else
		jsonValue = value;
}

void JsonHelper::Json(Json::Value &jsonValue, int &value)
{
	if (m_bIsLoading)
		value = jsonValue.asInt();
	else
		jsonValue = value;
}

void JsonHelper::Json(Json::Value &jsonValue, unsigned int &value)
{
	if (m_bIsLoading)
		value = jsonValue.asUInt();
	else
		jsonValue = value;
}

void JsonHelper::Json(Json::Value &jsonValue, CString &value)
{
	if (m_bIsLoading)
		value = jsonValue.asString().c_str();
	else
		jsonValue = (LPCTSTR)value;
}

void JsonHelper::Json(Json::Value &jsonValue, const CString &className, JsonObject ** ppJsonObject)
{
	if (m_bIsLoading)
	{
		if (jsonValue.isNull())
		{
			(*ppJsonObject) = NULL;
			return;
		}
		ASSERT(jsonValue.isObject());
		(*ppJsonObject) = JsonObjectCreator::Inst().Create(className);
	}
	else
	{
		if ((*ppJsonObject) == NULL)
		{
			jsonValue = Json::Value(Json::nullValue);
			return;
		}
		jsonValue = Json::Value(Json::objectValue);
	}

	m_StatusStack.push_back(m_pCurValue);
	m_pCurValue = &jsonValue;

	(*ppJsonObject)->Json(*this);

	m_pCurValue = *(--m_StatusStack.end());
	m_StatusStack.pop_back();
}
