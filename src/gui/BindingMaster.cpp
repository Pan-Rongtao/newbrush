#include "newbrush/gui/BindingMaster.h"
#include "newbrush/core/DependencyObject.h"
#include "newbrush/gui/Binding.h"

using namespace nb;
using namespace nb::gui;

std::map<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>>	BindingMaster::g_bindingmap;

void BindingMaster::addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<Binding> bd)
{
	if (!bd)
	{
		nbThrowException(std::invalid_argument, "bd is nullptr.");
	}

	auto dataContext = bd->source();
	if (!dataContext)
	{
		nbThrowException(std::runtime_error, "bd's source is nullptr.");
	}

	auto path = bd->path();
	auto dataNode = dataContext->lookup(path);
	if (!dataNode)
	{
		nbThrowException(std::runtime_error, "bd's source has no path [%s]", path.data());
	}

	setToTarget(target, dp, dataNode);

	auto ret = g_bindingmap.insert(std::make_pair(bd, std::make_pair(target, dp)));
	if (ret.second)
	{
		if(dataContext->ValueChanged.size() == 0)
			dataContext->ValueChanged += std::bind(&BindingMaster::onBingingDataChanged, std::placeholders::_1);
	}
}

void BindingMaster::onBingingDataChanged(const DataContext::ValueChangedArgs & args)
{
	auto iter = std::find_if(g_bindingmap.begin(), g_bindingmap.end(), [&args](const std::pair<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>> &p)
	{
		return p.first->source().get() == args.root && p.first->path() == args.path;
	});

	if(iter != g_bindingmap.end())
	{
		auto dataNode = args.root->lookup(args.path);
		auto target = iter->second.first;
		auto dp = iter->second.second;
		setToTarget(target, dp, dataNode);
	}
}

void BindingMaster::setToTarget(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<DataContext> dataNode)
{
	try {
		target->set(dp, dataNode->get());
	}
	catch (...) {
		nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", dataNode->type().name(), dp.propertyType().name());
	}
}
