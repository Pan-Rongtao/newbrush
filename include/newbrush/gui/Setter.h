#pragma once
#include "newbrush/core/Property.h"
#include "newbrush/core/DependencyProperty.h"
#include "Poco/Dynamic/Var.h"

namespace nb{
namespace gui{

class NB_API Setter
{
public:
	DependencyProperty	property;	// Ù–‘
	Var					value;		// Ù–‘÷µ
};


}}
