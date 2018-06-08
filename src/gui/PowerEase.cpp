#include "gui/PowerEase.h"
#include "system/System.h"

#include <math.h>

using namespace nb::Media;


NB_OBJECT_TYPE_IMPLEMENT(PowerEase, EasingFunctionBase, NULL, NULL);

const double p = 3.0;

PowerEase::PowerEase(void)
{
}

PowerEase::~PowerEase(void)
{
}

 double PowerEase::GetEaseDefault(double normalizedTime) const
 {
 	if(normalizedTime < 0) normalizedTime = 0;
 	else if(normalizedTime > 1) normalizedTime = 1;
 
	double v = nb::System::Pow(normalizedTime, p);
 	double ease = v;
  	//if(ease < -1) ease = -1;
  	//else if(ease > 1) ease = 1;
 	return ease;
 }

void PowerEase::SetEasingMode(EasingMode mode)
{
	EasingFunctionBase::m_mode = mode;
}
