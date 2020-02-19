#pragma once
#include "newbrush/core/Property.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/RoutedEvent.h"
#include "Poco/Dynamic/Var.h"

namespace nb{
namespace gui{

class NB_API SetterBase
{
protected:
	SetterBase() = default;
	virtual ~SetterBase() = default;
};

class NB_API Setter : public SetterBase
{
public:
	Setter();
	Setter(const DependencyProperty &dp, const Var &v);

	DependencyProperty	property;	// Ù–‘
	Var					value;		// Ù–‘÷µ
};

class NB_API EventSetter : public SetterBase
{
public:
	RoutedEvent			event;
//	RoutedEventHandler	handler;
};

using SetterBasePtr = std::shared_ptr<SetterBase>;

}}
