#include "gui/LineEase.h"

using namespace nb::Media;

LineEase::LineEase(void)
{
}

LineEase::~LineEase(void)
{
}

double LineEase::GetEaseDefault(double normalizedTime) const
{
	return normalizedTime;
}

void LineEase::SetEasingMode(EasingMode mode)
{
	EasingFunctionBase::m_mode = mode;
}
