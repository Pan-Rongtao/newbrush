#pragma once
#include "newbrush/Scene.h"
#include "newbrush/simdjson.h"
using namespace simdjson; // optional

namespace nb 
{

class NB_API NBBParser : public Object
{
public:
	void parse(const std::string &path, ref<Scene> &scene);

private:
	//value：每一层解析出的nb::Object对象或者其派生类的var包装
	void loopVisual(const dom::object &jObj, var &value, std::string &jPath);
	void loopLibrary(const dom::object &jObj, var &value, std::string &jPath);

	var jsonToVar(const dom::element &json);

	var createInstanceFromRef(const std::string &sourcePath);

	dom::parser m_parser;
};

}