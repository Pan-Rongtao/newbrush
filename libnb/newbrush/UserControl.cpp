#include "newbrush/UserControl.h"
#include "newbrush/Renderer2D.h"

using namespace nb;

void Button::setBkgndNormal(ref<Brush> brush)
{
	m_bkgndNormal = brush;
}

void Button::setBkgndPress(ref<Brush> brush)
{
	m_bkgndPress = brush;
}

void Button::setBkgndDisable(ref<Brush> brush)
{
	m_bkgndDisable = brush;
}

void Button::setBkgndCheck(ref<Brush> brush)
{
	m_bkgndCheck = brush;
}

void Button::setBkgndFocus(ref<Brush> brush)
{
	m_bkgndFocus = brush;
}

void Button::setCheck(bool check)
{
	m_checked = check;
}

bool Button::isChecked() const
{
	return m_checked;
}

ref<Button> Button::createWithTextureFrame(const TextureFrame & texFrame, bool useBrush, float x, float y)
{
	auto node = createRef<Button>(x, y, texFrame.size.x, texFrame.size.y);
	node->setMargin(Thickness(texFrame.trimmedSize.x, texFrame.trimmedSize.y, texFrame.trimmedSize.x, texFrame.trimmedSize.y));
	if (useBrush)
		node->setBkgndNormal(ImageBrush::createWitchTextureFrame(texFrame));
	return node;
}

ref<Button> Button::createWithTextureFrameName(const std::string & texAtlasKey, const std::string & frameName, bool useBrush, float x, float y)
{
	auto texFrame = TextureLibrary::getFrameFromTextureAtlas(texAtlasKey, frameName);
	return createWithTextureFrame(texFrame, useBrush, x, y);
}

void Button::onTouch(const TouchEventArgs & e)
{
	ButtonBase::onTouch(e);
}

void Button::onFocusChanged(const FocusEventArgs & e)
{
}

void Button::onRender()
{
	if (visibility() != VisibilityE::Visible)
		return;

	Rect rc = getRenderRect();
	ref<Brush> brush;
	if (isEnable())
	{
		if (isChecked())
		{
			brush = m_bkgndCheck;
		}
		else if (isPressed())
		{
			brush = m_bkgndPress;
		}
		else if (hasFocus())
		{
			brush = m_bkgndFocus;
		}
		else
		{
			brush = m_bkgndNormal;
		}
	}
	else
	{
		brush = m_bkgndDisable;
	}

	if (!brush)
	{
		brush = m_bkgndNormal;
	}

	drawBrush(brush);
}
