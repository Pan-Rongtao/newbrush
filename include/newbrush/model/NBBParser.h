#pragma once
#include "newbrush/model/Scene3D.h"
#include "newbrush/model/simdjson.h"
using namespace simdjson; // optional

namespace nb {

class NB_API NBBParser : public Object
{
public:
	void parse(const std::string &path, Scene3DPtr &scene);

private:

	enum class Type
	{
		boolProperty,
		intProperty,
		floatProperty,
		stringProperty,

	};

	//value：每一层解析出的nb::Object对象或者其派生类的var包装
	void loopVisual(const dom::object &jObj, var &value, std::string &jPath);
	void loopLibrary(const dom::object &jObj, var &value, std::string &jPath);

	var jsonToVar(const dom::element &json);

	var createInstanceFromRef(const std::string &sourcePath);

	dom::parser m_parser;
};

}