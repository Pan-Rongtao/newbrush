#include "newbrush/core/BindingMaster.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/core/Binding.h"

using namespace nb;

//每个binding实例可以对应多个obj-property
//source和path相同的不同binding实例，分别对应不同obj-property
//因此map做成这个结果，此结果性能并非最佳，后续可能考虑优化
std::map<std::shared_ptr<Binding>, BindingMaster::ObjectPropertysContainer >	BindingMaster::g_bindingmap;

void BindingMaster::addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<Binding> bd)
{
	if (!bd)
	{
		nbThrowException(std::invalid_argument, "bd is nullptr.");
	}

	auto dataContext = bd->source();
	if (!dataContext)
	{
		nbThrowException(std::invalid_argument, "bd's source is nullptr.");
	}

	auto path = bd->path();
	auto dataNode = dataContext->lookup(path);
	if (!dataNode)
	{
		nbThrowException(std::runtime_error, "bd's source has no path [%s]", path.data());
	}

	setToTarget(target, dp, dataNode->get());

	auto ret = g_bindingmap.insert({ bd, ObjectPropertysContainer{ std::make_pair(target, dp) } });
	//插入成功，表示该binding不存在，否则该binding已经有绑定的属性，需要追加对应关系即可
	if (ret.second)
	{
		if(dataContext->ValueChanged.size() == 0)
			dataContext->ValueChanged += std::bind(&BindingMaster::onBingingDataChanged, std::placeholders::_1);
	}
	else
	{
		ret.first->second.push_back({target, dp});
	}
}

void BindingMaster::onBingingDataChanged(const DataContext::ValueChangedArgs & args)
{
	for (auto iter : g_bindingmap)
	{
		auto binding = iter.first;
		auto &objPropertys = iter.second;
		if(binding->source().get() == args.root && binding->path() == args.path)
		{
			for (auto const &objPropertyPair : objPropertys)
			{
				auto target = objPropertyPair.first;
				auto dp = objPropertyPair.second;
				setToTarget(target, dp, args.value);
			}
		}
	}
}

void BindingMaster::setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, const Var &value)
{
	try {
		target->set(dp, value);
	}
	catch (...) {
		nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", value.type().name(), dp.propertyType().name());
	}
}
