#include "newbrush/model/NBBParser.h"
#include "newbrush/model/Log.h"
#include "newbrush/model/ResourceDictionary.h"

using namespace nb;
using namespace simdjson;

#define JSON_FIELD_SCREEN	"Scene"
#define JSON_FIELD_LIBRARY	"Library"
#define JSON_FIELD_TYPE		"Type"
#define JSON_FIELD_REF		"Ref"

#define OBJECT_GET(obj, key, v, parentName)\
do{\
	auto error = obj[key].get(v);\
	if (error)\
	{\
		nbThrowException(std::runtime_error, "[%s] has no field [%s]", std::string(parentName).data(), std::string(key).data());\
	}\
}while(0)

void NBBParser::parse(const std::string & path, Scene3DPtr &scene)
{
	auto result = m_parser.load(path);
	if (result.second)
	{
		nbThrowException(std::runtime_error, "parsing[%s] fail, error=[%d], error_message=[%s]", path.data(), result.second, error_message(result.second));
	}

	auto root = m_parser.doc.root();

	dom::object jLibraryObj;
	std::string jPath = JSON_FIELD_LIBRARY;
	OBJECT_GET(root, jPath, jLibraryObj, "");
	var v;
	loopLibrary(jLibraryObj, v, jPath);

	dom::object jSceneObj;
	std::string jsonPath = JSON_FIELD_SCREEN;
	OBJECT_GET(root, jsonPath, jSceneObj, "");
	var value;
	loopVisual(jSceneObj, value, jsonPath);
	scene = variant_cast<Scene3DPtr>(value);

	int xx = 10;
}

void NBBParser::loopVisual(const dom::object &jObj, var &value, std::string &jPath)
{
	//如果有引用，则从引用路径构建，否则从Type名字构建对象
	var obj;
	std::string_view refPath;
	if (!jObj[JSON_FIELD_REF].get(refPath))
	{
		obj = createInstanceFromRef(refPath.data());
	}
	else
	{
		std::string_view classTypeName;
		OBJECT_GET(jObj, JSON_FIELD_TYPE, classTypeName, jPath);
		auto classType = type::get_by_name(classTypeName.data());
		if (!classType)
		{
			nbThrowException(std::runtime_error, "[%s.Type]<%s> is unregistered", jPath.data(), classTypeName.data());
		}
		obj = classType.create();
		if (!obj)
		{
			nbThrowException(std::runtime_error, "create instance [%s] fail, maybe constructor is not registered", classTypeName.data());
		}
	}
	
	//为对象依次设置属性（排除固定"Type"字段和"Ref"字段）
	for (auto const &e : jObj)
	{
		auto const &jPropName = e.key;
		auto const &jPropValue = e.value;
		if (jPropName == JSON_FIELD_TYPE || jPropName == JSON_FIELD_REF)	continue;
		//如果属性是object类型，表明该属性是个有属性的属性对象，嵌套构建该属性对象
		//否则如果是普通属性值，直接设置
		var propValue;
		if (jPropValue.is_object())
		{
			jPath = jPath + "." + jPropName.data();
			loopVisual(jPropValue.get_object().first, propValue, jPath);
			jPath = jPath.erase(jPath.size() - jPropName.size() - 1);
		}
		else
		{
			propValue = jsonToVar(jPropValue);
			if (!propValue)
			{
				nbThrowException(std::runtime_error, "invalid property type for [%s]", jPropName.data());
			}
		}
		nb::setValue(obj, jPropName.data(), propValue);
	}
	value = obj;
}

void NBBParser::loopLibrary(const dom::object & jObj, var & value, std::string & jPath)
{
	std::string_view classTypeName;
	auto error = jObj[JSON_FIELD_TYPE].get(classTypeName);
	//没有Type字段表示是路径而非对象
	if (error)
	{
		for (auto const &e : jObj)
		{
			auto const &jPropName = e.key;
			auto const &jPropValue = e.value;
			if (jPropValue.is_object())
			{
				var propValue;
				jPath = jPath + "/" + jPropName.data();
				loopLibrary(jPropValue.get_object().first, propValue, jPath);
				jPath = jPath.erase(jPath.size() - jPropName.size() - 1);
			}
		}
	}
	else
	{
		auto classType = type::get_by_name(classTypeName.data());
		if (!classType)
		{
			nbThrowException(std::runtime_error, "[%s.Type]<%s> is unregistered", jPath.data(), classTypeName.data());
		}
		auto obj = classType.create();
		if (!obj)
		{
			nbThrowException(std::runtime_error, "create instance [%s] fail, maybe constructor is not registered", classTypeName.data());
		}
		for (auto const &e : jObj)
		{
			auto const &jPropName = e.key;
			auto const &jPropValue = e.value;
			if (jPropName == JSON_FIELD_TYPE || jPropName == JSON_FIELD_REF)	continue;
			var propValue;
			if (jPropValue.is_object())
			{
				jPath = jPath + "/" + jPropName.data();
				loopLibrary(jPropValue.get_object().first, propValue, jPath);
				jPath = jPath.erase(jPath.size() - jPropName.size() - 1);
			}
			else
			{
				propValue = jsonToVar(jPropValue);
				if (!propValue)
				{
					nbThrowException(std::runtime_error, "invalid property type for [%s]", jPropName.data());
				}
			}
			nb::setValue(obj, jPropName.data(), propValue);
		}
		value = obj;
		nb::globalResources()->add(jPath, value);
	}

}

var NBBParser::jsonToVar(const dom::element & json)
{
	var v;
	switch (json.type())
	{
	case dom::element_type::BOOL:	v = json.get_bool().first;				break;
	case dom::element_type::INT64:	v = json.get_int64().first;				break;
	case dom::element_type::UINT64: v = json.get_uint64().first;			break;
	case dom::element_type::DOUBLE: v = json.get_double().first;			break;
	case dom::element_type::STRING:	v = json.get_string().first.to_string(); break;
	default: break;
	}
	return v;
}

var NBBParser::createInstanceFromRef(const std::string & sourcePath)
{
	auto n = sourcePath.rfind(".");
	auto resPath = sourcePath.substr(0, n);
	auto propName = sourcePath.substr(n + 1);
	auto res = nb::globalResources()->find(resPath);
	auto resT = res.get_type().get_wrapped_type();
	auto prop = resT.get_property(propName);
	var v = prop.get_value(res);
	return v;
}
