#pragma once
class JsonHelper;
#include <map>
using namespace std;

class JsonObject;
typedef JsonObject* (* pfnCreateType)();

#define JSONOBJECT_INTERFACE \
public: \
	virtual void Json(JsonHelper &jsonHelper) COMA ; \

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef COMA
#define COMA =0

#pragma warning(disable : 4786)

class JsonObject
{
public:
	JsonObject(void);
	~JsonObject(void);

	JSONOBJECT_INTERFACE
};

#undef COMA
#define COMA

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class JsonObjectCreator
{
public:
	JsonObject *Create(const CString &strType) const;
	void Add(const CString &strType, pfnCreateType pfnCreate);

	static JsonObjectCreator& Inst();

private:
	JsonObjectCreator() {}
	JsonObjectCreator(const JsonObjectCreator &Create);

private:
	CMapStringToPtr m_Map;
};

inline JsonObject *JsonObjectCreator::Create(const CString &strType) const
{
	void *p;
	BOOL bl=m_Map.Lookup(strType, p);
	ASSERT(bl);
	pfnCreateType pfn=(pfnCreateType )p;
	return pfn();
}

inline void JsonObjectCreator::Add(const CString &strType, pfnCreateType pfnCreate)
{
	m_Map[strType]=pfnCreate;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class JsonObjectRuntime
{
public:
	JsonObjectRuntime() {}
	JsonObjectRuntime(const CString &strType, pfnCreateType pfnCreate) { JsonObjectCreator::Inst().Add(strType, pfnCreate); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DECLARE_JSONOBJECT(class_name) \
	static const JsonObjectRuntime class_name##Runtime; \
	static JsonObject *class_name##Create(); \
	JSONOBJECT_INTERFACE \

#define IMPLEMENT_JSONOBJECT(class_name, type) \
	const JsonObjectRuntime class_name::class_name##Runtime=JsonObjectRuntime(type, class_name::class_name##Create); \
	JsonObject *class_name::class_name##Create() \
		{ return new class_name; } \

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
