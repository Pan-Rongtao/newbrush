#include "gui/BounceEase.h"
#include <math.h>

using namespace nb::gui;

const double fMaxEase = sin(3.1415926f * 8.5);

BounceEase::BounceEase(void)
{
}

BounceEase::~BounceEase(void)
{
}

 double BounceEase::GetEaseDefault(double normalizedTime) const
 {
 	if(normalizedTime < 0) normalizedTime = 0;
 	else if(normalizedTime > 1) normalizedTime = 1;
 	double t = normalizedTime * 3.1415926f * 8.5;
 	double v = sin(t) * pow(normalizedTime, 3.0);
 	double ease = std::abs(v/fMaxEase);
 	return ease;
 }

void BounceEase::SetEasingMode(EasingMode mode)
{
	EasingFunctionBase::m_mode = mode;
}
