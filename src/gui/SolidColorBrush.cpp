#include "system/Colors.h"
#include "system/Rect.h"
#include "gui/SolidColorBrush.h"

using namespace nb::System;
using namespace nb::Media;
 
SolidColorBrush::SolidColorBrush()
{
	SetColor(Colors::Black());
}

SolidColorBrush::SolidColorBrush(const Color &color)
{
	SetColor(color);
}

SolidColorBrush::SolidColorBrush(const SolidColorBrush &other)
{
	SetColor(other.GetColor());
}

void SolidColorBrush::operator = (const SolidColorBrush &other)
{
	SetColor(other.GetColor());
}

SolidColorBrush::~SolidColorBrush()
{
}

void SolidColorBrush::SetColor(const Color &color)
{
	m_color = color;
}

const Color &SolidColorBrush::GetColor() const
{
	return m_color;
}
