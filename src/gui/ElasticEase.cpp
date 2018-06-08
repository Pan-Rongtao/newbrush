﻿
#include "gui/ElasticEase.h"
#include "system/System.h"

#include <math.h>

using namespace nb::Media;


NB_OBJECT_TYPE_IMPLEMENT(ElasticEase, EasingFunctionBase, NULL, NULL);

const double fMaxEase = sin(3.1415926f * 8.5);

ElasticEase::ElasticEase(void)
{
}

ElasticEase::~ElasticEase(void)
{
}

double ElasticEase::GetEaseDefault(double normalizedTime) const
{
	if(normalizedTime < 0) normalizedTime = 0;
	else if(normalizedTime > 1) normalizedTime = 1;

	double t = normalizedTime * 3.1415926f * 8.5;
	double v =  sin(t) * nb::System::Pow(normalizedTime, 3.0);
	double ease = v/fMaxEase;
	if(ease < -1) ease = -1;
	else if(ease > 1) ease = 1;
	return ease;
}

void ElasticEase::SetEasingMode(EasingMode mode)
{
	EasingFunctionBase::m_mode = mode;
}
