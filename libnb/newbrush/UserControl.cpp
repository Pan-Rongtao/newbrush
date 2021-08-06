#include "newbrush/UserControl.h"
#include "newbrush/Renderer2D.h"

using namespace nb;
Button::Button()
	: ButtonBase()
{
}

Button::Button(const Rect & rc)
	: ButtonBase(rc)
{
}

Button::Button(float x, float y, float w, float h)
	: ButtonBase(x, y, w, h)
{
	m_icon = createRef<Node2D>();
	addChild(m_icon);
}

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

void Button::setIcon(ref<Brush> normal, ref<Brush> press, ref<Brush> check, ref<Brush> disable, ref<Brush> focus)
{
	m_iconNormal = normal;
	m_iconPress = press;
	m_iconCheck = check;
	m_iconDisable = disable;
	m_iconFocus = focus;
}

void Button::setTextColor(const Color & normal, const Color & press, const Color & check, const Color & disable, const Color & focus)
{
	m_clrNormal = normal;
	m_clrPress = press;
	m_clrCheck = check;
	m_clrDisable = disable;
	m_clrFocus = focus;
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
	auto node = createRef<Button>(x, y, texFrame.sourceSize.x, texFrame.sourceSize.y);
	if (useBrush)
		node->setBkgndNormal(createRef<ImageBrush>(texFrame));
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
	ref<Brush> bkgBrush, iconBrush;
	if (isEnable())
	{
		if (isChecked())		{ bkgBrush = m_bkgndCheck;	 iconBrush = m_iconCheck; }
		else if (isPressed())	{ bkgBrush = m_bkgndPress;	iconBrush = m_iconPress; }
		else if (hasFocus())	{ bkgBrush = m_bkgndFocus;	iconBrush = m_iconFocus; }
		else					{ bkgBrush = m_bkgndNormal;	iconBrush = m_iconNormal; }
	}
	else
	{
		bkgBrush = m_bkgndDisable;
		iconBrush = m_iconDisable;
	}

	if (!bkgBrush)				{ bkgBrush = m_bkgndNormal; }
	if (!iconBrush)				{ iconBrush = m_iconNormal; }

	this->setBackground(bkgBrush);
	m_icon->setBackground(iconBrush);

	ButtonBase::onRender();
}

//////////////////////////
ToggleButton::ToggleButton()
	: ButtonBase()
{}

ToggleButton::ToggleButton(const Rect & rc)
	: ButtonBase(rc)
{}

ToggleButton::ToggleButton(float x, float y, float w, float h)
	: ButtonBase(x, y, w, h)
{
	m_icon = createRef<Node2D>();
	addChild(m_icon);
}

void ToggleButton::setBkgndNormal(ref<Brush> brush)
{ 
	m_bkgndNormal = brush; 
}

void ToggleButton::setBkgndPress(ref<Brush> brush) 
{ 
	m_bkgndPress = brush; 
}

void ToggleButton::setBkgndCheck(ref<Brush> brush) 
{ 
	m_bkgndCheck = brush; 
}

void ToggleButton::setBkgndDisable(ref<Brush> brush) 
{ 
	m_bkgndDisable = brush; 
}

void ToggleButton::setBkgndFocus(ref<Brush> brush) 
{ 
	m_bkgndFocus = brush;
}

void ToggleButton::setIcon(ref<Brush> normal, ref<Brush> press, ref<Brush> check, ref<Brush> disable, ref<Brush> focus)
{
	m_iconNormal = normal;
	auto imgBrush = as<ImageBrush>(normal);
	if (imgBrush)
		m_icon->setSize({ imgBrush->frame.sourceSize.x, imgBrush->frame.sourceSize.y });
	updateIconPositions();

	m_iconPress = press;
	m_iconCheck = check;
	m_iconDisable = disable;
	m_iconFocus = focus;
}

void ToggleButton::setCheck(bool check)
{
	m_icon->setPosition(check ? m_iconCheckedPos : m_iconUncheckedPos);
	bool b = m_checked != check;
	m_checked = check;
	if(b)
		CheckChanged.invoke({ this });
}

bool ToggleButton::isChecked() const
{
	return m_checked;
}

void ToggleButton::setIconOffset(const Point & offset)
{
	m_iconOffset = offset;
	updateIconPositions();
}

void ToggleButton::onRender()
{
	ref<Brush> bkgBrush, iconBrush;
	if (isEnable())
	{
		if (isChecked())		{ bkgBrush = m_bkgndCheck;	iconBrush = m_iconCheck; }
		else if (isPressed())	{ bkgBrush = m_bkgndPress;	iconBrush = m_iconPress; }
		else if (hasFocus())	{ bkgBrush = m_bkgndFocus;	iconBrush = m_iconFocus; }
		else					{ bkgBrush = m_bkgndNormal;	iconBrush = m_iconNormal; }
	}
	else
	{
		bkgBrush = m_bkgndDisable;
		iconBrush = m_iconDisable;
	}

	if (!bkgBrush)				{ bkgBrush = m_bkgndNormal;}
	if (!iconBrush)				{ iconBrush = m_iconNormal;}

	this->setBackground(bkgBrush);
	m_icon->setBackground(iconBrush);

	ButtonBase::onRender();
}

void ToggleButton::onClick()
{
	setCheck(!isChecked());
}

void ToggleButton::updateIconPositions()
{
	m_iconCheckedPos = { size().width - (m_icon->size().width - std::abs(m_iconOffset.x)), m_iconOffset.y };
	m_iconUncheckedPos = m_iconOffset;
	setCheck(m_checked);
}
