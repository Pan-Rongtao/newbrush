#include "gui/BindingMaster.h"
#include "core/DependencyObject.h"
#include "gui/Binding.h"

using namespace nb;
using namespace nb::gui;

std::map<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>>	BindingMaster::g_bindingmap;

void BindingMaster::addBinding(std::shared_ptr<DependencyObject> target, const DependencyProperty & dp, std::shared_ptr<Binding> bd)
{
	auto source = std::dynamic_pointer_cast<ObjectData>(bd->source());
	auto path = bd->path();
	auto valueNode = std::dynamic_pointer_cast<ValueDataBase>(source->lookup(path));
	if (!valueNode)
		nbThrowException(std::runtime_error, "binding data must be a value type, check soure.path[%s]", path.data());
	valueNode->ValueChanged += std::bind(&BindingMaster::onBingingDataChanged, std::placeholders::_1);
	g_bindingmap.insert(std::make_pair(bd, std::make_pair(target, dp)));
}

void BindingMaster::onBingingDataChanged(const ValueDataBase::ValueChangedArgs & args)
{
	auto iter = std::find_if(g_bindingmap.begin(), g_bindingmap.end(), [&args](const std::pair<std::shared_ptr<Binding>, std::pair<std::shared_ptr<DependencyObject>, DependencyProperty>> &p)
	{
		return p.first->source() == args.root && p.first->path() == args.path;
	});

	if(iter != g_bindingmap.end())
	{
		auto binding = iter->first;
		auto bindingData = std::dynamic_pointer_cast<ValueDataBase>(std::dynamic_pointer_cast<ObjectData>(binding->source())->lookup(binding->path()));
		auto target = iter->second.first;
		auto dp = iter->second.second;
		auto propertyType = dp.propertyType();

		try {
			target->set(dp, bindingData->getAny());
		}catch(...)
		{
			nbThrowException(std::logic_error, "binding data type[%s] is unmatched with target property type[%s]", bindingData->type().name(), propertyType.name());
		}
	}
}
