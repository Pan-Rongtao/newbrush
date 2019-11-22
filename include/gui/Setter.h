#pragma once
#include "../core/Any.h"
#include "../core/Property.h"
#include "../core/DependencyProperty.h"

namespace nb{
namespace gui{

class NB_API Setter
{
public:
	DependencyProperty	property;	// Ù–‘
	Any					value;		// Ù–‘÷µ
};


}}
