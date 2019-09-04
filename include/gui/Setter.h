#pragma once
#include "../core/Any.h"
#include "../gui/Property.h"
#include "../gui/DependencyProperty.h"

namespace nb{
namespace gui{

class NB_API Setter
{
public:
	DependencyProperty	property;	// Ù–‘
	Any					value;		// Ù–‘÷µ
};


}}
