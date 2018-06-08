#include "gui/EasingFunctionBase.h"

using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(EasingFunctionBase, nbObject, NULL, NULL);

EasingFunctionBase::EasingFunctionBase(void)
:m_mode(EaseOut)
{
}

EasingFunctionBase::~EasingFunctionBase(void)
{
}
double EasingFunctionBase::GetEase(double normalizedTime) const
{
	double ease = 0;
	switch(m_mode)
	{
	case EaseIn:
		ease = GetEaseDefault(normalizedTime);
		break;
	case EaseOut:
		ease = 1 - GetEaseDefault(1-normalizedTime);
		break;
	case EaseInOut:
		{
 			if (normalizedTime < 0.5)
				ease = GetEaseDefault(normalizedTime*2);
 			if (normalizedTime >= 0.5)
 				ease = GetEaseDefault(0.5*2) + 1 - GetEaseDefault(1-(normalizedTime-0.5)*2);
 		}
		break;
	default:
		{
			ease = 1-GetEaseDefault(1-normalizedTime);
		}
		break;
	}
	return ease;
}
