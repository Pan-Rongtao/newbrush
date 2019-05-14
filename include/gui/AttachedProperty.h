#pragma once
#include <string>
#include "core/Any.h"
#include "UIElement.h"

namespace nb{ namespace gui{

class AttachedProperties
{
public:
	//注册一个依赖属性，如果此属性已存在，则只修改属性值
	//element：目标元素
	//property_name：属性名
	//property_v：属性值
	static void registerAttached(std::shared_ptr<UIElement> element, const std::string &property_name, const core::Any &property_v);

	//查询依赖属性值，如果查询不到，将返回一个空的Any
	//element：目标元素
	//property_name：属性名
	static core::Any findAttached(std::shared_ptr<UIElement> element, const std::string &property_name);

private:
	static std::map<std::shared_ptr<UIElement>, std::map<std::string, core::Any>>	m_attProperties;
};


}}