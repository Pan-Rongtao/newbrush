#include "newbrush/Binding.h"

using namespace nb;

Binding::Binding()
	: Binding(nullptr, "", BindingModeE::OneWayToTarget) 
{}

Binding::Binding(const std::string &path)
	: Binding(nullptr, path, BindingModeE::OneWayToTarget) 
{}

Binding::Binding(ref<DataContext> _source, const std::string &_path, BindingModeE _mode)
	: path(_path)
	, mode(_mode)
	, m_handle(-1)
{
	setSource(_source);
}

Binding::~Binding()
{
	setSource(nullptr);
}

void Binding::setSource(ref<DataContext> source)
{
	if (source == m_source)	return;

	if (m_source && m_handle != -1)
	{
		m_source->ValueChanged.removeHandler(m_handle);
	}

	m_source = source;
	if (m_source)
	{
		m_handle = m_source->ValueChanged.addHandler([&](const DataContext::ValueChangedArgs & args)
		{
			if (args.path == path)
				this->BindDataChanged.invoke({ shared_from_this(), args.value });
		});
	}
}

//每个binding实例可以对应多个obj-property
//source和path相同的不同binding实例，分别对应不同obj-property
//因此map做成这个结果，此结果性能并非最佳，后续可能考虑优化
//g_bindingmap的key不可使用Binding*，否则连续的std::make_shared<Binding>会返回相同的this，不知道为什么！！！
using ObjectPropertysContainer = std::vector<std::pair<ref<Object>, property>>;
std::map<ref<Binding>, ObjectPropertysContainer> g_bindingmap;

void BindingMaster::addBinding(ref<Object> target, const property &prop, ref<Binding> bd)
{
	nbThrowExceptionIf(!target, std::invalid_argument, "target is nullptr.");
	nbThrowExceptionIf(!prop, std::invalid_argument, "prop is nullptr.");
	nbThrowExceptionIf(!bd, std::invalid_argument, "bd is nullptr.");

	auto source = bd->source();
	nbThrowExceptionIf(!source, std::invalid_argument, "bd's source is nullptr.");

	auto path = bd->path;
	auto dataNode = source->lookup(path);
	nbThrowExceptionIf(!dataNode, std::runtime_error, "bd's source has no path [%s]", path.data());

	setToTarget(target, prop, dataNode->get());

	auto ret = g_bindingmap.insert({ bd, ObjectPropertysContainer{ std::make_pair(target, prop) } });
	//插入成功，表示该binding不存在，否则该binding已经有绑定的属性，需要追加对应关系即可
	if (ret.second)
	{
		bd->BindDataChanged += [&](const Binding::BindDataChangedEventArgs &args) 
		{
			auto iterFind = g_bindingmap.find(args.sender);
			if (iterFind == g_bindingmap.end())
				return;
			for (auto const &objPropertyPair : iterFind->second)
			{
				auto target = objPropertyPair.first;
				auto dp = objPropertyPair.second;
				setToTarget(target, dp, args.value);
			}
		};
	}
	else
	{
		ret.first->second.push_back({ target, prop });
	}
}

void BindingMaster::clear()
{
	g_bindingmap.clear();
}

void BindingMaster::setToTarget(ref<Object> target, const property &prop, const var &value)
{
	try {
		target->setValue(prop, value);
	}
	catch (...) {
		nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", 
			value.get_type().get_name().data(), prop.get_type().get_name().data());
	}
}
