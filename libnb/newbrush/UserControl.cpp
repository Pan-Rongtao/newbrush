#include "newbrush/UserControl.h"
#include "newbrush/Renderer2D.h"
#include "newbrush/Helper.h"
#include "Log.h"

using namespace nb;
Button::Button()
	: ButtonBase()
{}

Button::Button(const Rect & rc)
	: ButtonBase(rc)
{}

Button::Button(float x, float y, float w, float h)
	: ButtonBase(x, y, w, h)
{
	m_icon = createRef<Node2D>();
	m_icon->setAlignmentCenter();
	m_txt = createRef<TextBlock>();
	m_txt->setAlignmentCenter();
	addChild(m_icon);
	addChild(m_txt);
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
	auto imgBrush = as<ImageBrush>(normal);
	if (imgBrush)
		m_icon->setSize({ imgBrush->frame.sourceSize.x, imgBrush->frame.sourceSize.y });

	m_iconPress = press;
	m_iconCheck = check;
	m_iconDisable = disable;
	m_iconFocus = focus;
}

void Button::setText(const std::string & text)
{
	m_txt->setText(text);
}

const std::string &Button::text() const
{
	return m_txt->text();
}

void Button::setTextColorNormal(const Color & c)
{
	m_clrNormal = c;
}

void Button::setTextColorPress(const Color & c)
{
	m_clrPress = c;
}

void Button::setTextColorCheck(const Color & c)
{
	m_clrCheck = c;
}

void Button::setTextColorDisable(const Color & c)
{
	m_clrDisable = c;
}

void Button::setTextColorFocus(const Color & c)
{
	m_clrFocus = c;
}

void Button::setTextColor(const Color & normal, const Color & press, const Color & check, const Color & disable, const Color & focus)
{
	m_clrNormal = normal;
	m_clrPress = press;
	m_clrCheck = check;
	m_clrDisable = disable;
	m_clrFocus = focus;
}

void Button::setIconOffset(const Point & offset)
{
	m_icon->setHorizontalAlignment(HorizontalAlignment::Left);
	m_icon->setVerticalAlignment(VerticalAlignment::Top);
	m_icon->setPosition(offset);
}

void Button::setTextOffset(const Point & offset)
{
	m_txt->setHorizontalAlignment(HorizontalAlignment::Left);
	m_txt->setVerticalAlignment(VerticalAlignment::Top);
	m_txt->setPosition(offset);
}

void Button::setIconTextOffset(const Point &iconOffset, const Point &textOffset)
{
	setIconOffset(iconOffset);
	setTextOffset(textOffset);
}

void Button::setFont(ref<Font> font)
{
	m_txt->setFont(font);
}

void Button::setFontSize(float size)
{
	m_txt->setFontSize(size);
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

ref<Button> Button::createWithTextureFrameName(const std::string & texAtlasKey, const std::string & frameName, float x, float y)
{
	return createWithTextureFrameName(texAtlasKey, frameName, true, x, y);
}

ref<Button> Button::createWithTextureFrameName(const std::string & texAtlasKey, const std::string & frameName, bool useBrush, float x, float y)
{
	auto texFrame = TextureLibrary::getFrameFromTextureAtlas(texAtlasKey, frameName);
	return createWithTextureFrame(texFrame, useBrush, x, y);
}

void Button::onRender()
{
	auto oldBkg = background();
	auto oldIcon = m_icon->background();
	ref<Brush> bkgBrush, iconBrush;
	Color textColor;
	if (isEnable())
	{
		if (isPressed())			{ bkgBrush = m_bkgndPress;	iconBrush = m_iconPress; textColor = m_clrPress; }
		else if (isChecked())		{ bkgBrush = m_bkgndCheck;	iconBrush = m_iconCheck; textColor = m_clrCheck; }
		else if (hasFocus())		{ bkgBrush = m_bkgndFocus;	iconBrush = m_iconFocus; textColor = m_clrFocus; }
		else						{ bkgBrush = m_bkgndNormal;	iconBrush = m_iconNormal; textColor = m_clrNormal; }
	}
	else
	{
		bkgBrush = m_bkgndDisable;
		iconBrush = m_iconDisable; 
		textColor = m_clrDisable;
	}

	if (!bkgBrush)				{ bkgBrush = oldBkg; }
	if (!iconBrush)				{ iconBrush = oldIcon; }

	this->setBackground(bkgBrush);
	m_icon->setBackground(iconBrush);
	m_txt->setColor(textColor);

	ButtonBase::onRender();
}

//////////////////////////
ToggleButton::ToggleButton()
	: ToggleButton(0.0f, 0.0f, NAN, NAN)
{}

ToggleButton::ToggleButton(const Rect & rc)
	: ToggleButton(rc.x(), rc.y(), rc.width(), rc.height())
{}

ToggleButton::ToggleButton(float x, float y, float w, float h)
	: ToggleButton(x, y, w, h, nullptr, nullptr)
{}

ToggleButton::ToggleButton(float x, float y, float w, float h, ref<Brush> iconNormal, ref<Brush> iconCheck)
	: ButtonBase(x, y, w, h)
{
	m_icon = createRef<Node2D>();
	addChild(m_icon);
	setIcon(iconNormal, iconNormal, iconCheck);
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
	m_iconCheckedPos = { width() - (m_icon->width() - std::abs(m_iconOffset.x)), m_iconOffset.y };
	m_iconUncheckedPos = m_iconOffset;
	setCheck(m_checked);
}

///////////////
void NinePatchImage::setImages(ref<ImageBrush> left, ref<ImageBrush> leftTop, ref<ImageBrush> top, ref<ImageBrush> rightTop,
	ref<ImageBrush> right, ref<ImageBrush> rightBottom, ref<ImageBrush> bottom, ref<ImageBrush> leftBottom, ref<ImageBrush> center)
{
	m_left = left;
	m_leftTop = leftTop;
	m_top = top;
	m_rightTop = rightTop;
	m_right = right;
	m_rightBottom = rightBottom;
	m_bottom = bottom;
	m_leftBottom = leftBottom;
	m_center = center;
}

void NinePatchImage::setImages(ref<ImageBrush> leftTop, ref<ImageBrush> rightTop, ref<ImageBrush> rightBottom, ref<ImageBrush> leftBottom, ref<ImageBrush> ltrb, ref<ImageBrush> center)
{
	setImages(ltrb, leftTop, ltrb, rightTop, ltrb, rightBottom, ltrb, leftBottom, center);
}

void NinePatchImage::setImages(ref<ImageBrush> leftTop, ref<ImageBrush> rightTop, ref<ImageBrush> rightBottom, ref<ImageBrush> leftBottom, ref<ImageBrush> ltrbc)
{
	setImages(leftTop, rightTop, rightBottom, leftBottom, ltrbc, ltrbc);
}

void NinePatchImage::onRender()
{
	drawBrush(background());

	auto rcMain = getRenderRect();
	Rect rcLT = { rcMain.x(), rcMain.y(), m_leftTop->frame.sourceSize.x, m_leftTop->frame.sourceSize.y };
	Rect rcRT = { rcMain.x() + rcMain.width() - m_rightTop->frame.sourceSize.x, rcMain.y(), m_rightTop->frame.sourceSize.x, m_rightTop->frame.sourceSize.y };
	Rect rcRB = { rcMain.x() + rcMain.width() - m_rightBottom->frame.sourceSize.x, rcMain.y() + rcMain.height() - m_rightBottom->frame.sourceSize.y, m_rightBottom->frame.sourceSize.x, m_rightBottom->frame.sourceSize.y };
	Rect rcLB = { rcMain.x(), rcMain.y() + rcMain.height() - m_leftBottom->frame.sourceSize.y, m_leftBottom->frame.sourceSize.x, m_leftBottom->frame.sourceSize.y };
	Rect rcLeft = { rcLT.x(), rcLT.bottom(), rcLT.width(), rcMain.height() - rcLT.height() - rcLB.height()};
	Rect rcTop = { rcLT.right(), rcLT.y(), rcMain.width() - rcLT.width() - rcRT.width(), rcLT.height() };
	Rect rcRight = { rcRT.x(), rcRT.bottom(), rcRT.width(), rcMain.height() - rcRT.height() - rcRB.height() };
	Rect rcBottom = { rcLB.right(), rcLeft.bottom(), rcMain.width() - rcLB.width() - rcRB.width(), rcLB.height() };
	Rect rcCenter = { rcTop.x(), rcLeft.y(), rcMain.width() - rcLeft.width() - rcRight.width(), rcMain.height() - rcTop.height() - rcBottom.height() };

	auto op = TreeHelper::getActualOpacity(this);
	Renderer2D::drawImage(rcLT, Transform::identityMatrix4(), m_leftTop->frame, op);
	Renderer2D::drawImage(rcRT, Transform::identityMatrix4(), m_rightTop->frame, op);
	Renderer2D::drawImage(rcRB, Transform::identityMatrix4(), m_rightBottom->frame, op);
	Renderer2D::drawImage(rcLB, Transform::identityMatrix4(), m_leftBottom->frame, op);
	Renderer2D::drawImage(rcLeft, Transform::identityMatrix4(), m_left->frame, op);
	Renderer2D::drawImage(rcTop, Transform::identityMatrix4(), m_top->frame, op);
	Renderer2D::drawImage(rcRight, Transform::identityMatrix4(), m_right->frame, op);
	Renderer2D::drawImage(rcBottom, Transform::identityMatrix4(), m_bottom->frame, op);
	Renderer2D::drawImage(rcCenter, Transform::identityMatrix4(), m_center->frame, op);

	drawChildren();
}

//////////

MovieImage::MovieImage()
	:MovieImage(0, 0, NAN, NAN)
{
}

MovieImage::MovieImage(const Rect &rc)
	: MovieImage(rc.x(), rc.y(), rc.width(), rc.height())
{
}

MovieImage::MovieImage(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
	, m_nStopMovieInFrame(-1)
	, m_reverse(false)
{
	init();
}

void MovieImage::addFrame(ref<Texture2D> tex)
{
	auto brush = createRef<ImageBrush>(tex);
	m_vecBrush.push_back(brush);
}

void MovieImage::setInterval(int nInterval)
{
	m_timer.setInterval(nInterval);
}

void MovieImage::startMovie(int nInterval)
{
	m_nCurrFrame = m_reverse == false ? 0 : m_vecBrush.size() - 1;
	m_timer.stop();
	m_timer.setInterval(nInterval);
	m_timer.start();
}

void MovieImage::startMovie()
{
	m_nCurrFrame = m_reverse == false ? 0 : m_vecBrush.size() - 1;
	m_timer.start();
}

void MovieImage::stopMovie(void)
{
	m_timer.stop();
}

void MovieImage::stopMovieInFrame(int nFrame)
{
	m_nStopMovieInFrame = nFrame;
}

void MovieImage::nextFrame(bool bCyc)
{
	int nFrams = m_vecBrush.size();
	if (nFrams <= 1) return;

	if (m_nCurrFrame >= nFrams - 1)
	{
		if (bCyc) m_nCurrFrame = 0;
		else return;
	}
	else
	{
		m_nCurrFrame++;
	}
}

void MovieImage::prevFrame(bool bCyc)
{
	int nFrams = m_vecBrush.size();
	if (nFrams <= 1) return;

	if (m_nCurrFrame <= 0)
	{
		if (bCyc) m_nCurrFrame = nFrams - 1;
		else return;
	}
	else
	{
		m_nCurrFrame--;
	}
}

void MovieImage::gotoFrame(int nFrame)
{
	if (m_nCurrFrame == nFrame) return;

	if (nFrame < 0 || nFrame >= (int)m_vecBrush.size()) return;

	m_nCurrFrame = nFrame;
}

void MovieImage::setReverse(bool reverse)
{
	m_reverse = reverse;
}

bool MovieImage::getReverse()
{
	return m_reverse;
}

void MovieImage::init(void)
{
	m_nCurrFrame = m_reverse == false ? 0 : m_vecBrush.size();
	m_timer.setInterval(100);
	m_timer.Tick += nbBindEventFunction(MovieImage::onTick);
}

void MovieImage::onTick(const EventArgs & e)
{
	if (m_nCurrFrame == m_nStopMovieInFrame)
	{
		stopMovie();
		return;
	}

	if (m_reverse == false)
	{
		nextFrame(true);
	}
	else
	{
		prevFrame(true);
	}

	if ((m_nCurrFrame == 0 && (m_reverse == false)) || ((m_nCurrFrame == (m_vecBrush.size() - 1)) && (m_reverse == true)))
	{
		MovieCompleteEvent.invoke({ this });
	}

	setBackground(m_vecBrush[m_nCurrFrame]);
}

//////////////
SlideButton::SlideButton()
	: SlideButton(0.0f, 0.0f, NAN, NAN)
{}

SlideButton::SlideButton(const Rect & rc)
	: SlideButton(rc.x(), rc.y(), rc.width(), rc.height())
{}

SlideButton::SlideButton(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
	, m_curSel(-1)
{
}

void SlideButton::setBtn(ref<ImageBrush> normal)
{
	m_btnNormal = normal;
}

void SlideButton::setTextColor(const Color & normal, const Color & select, const Color & disable)
{
	m_clrTxtNormal = normal;
	m_clrTxtSelect = select;
	m_clrTxtDisable = disable;
}

void SlideButton::addItem(const std::string & txt)
{
	m_items.emplace_back(ItemInfo{ txt, ItemState::State_Normal });
	if (m_curSel < 0)
		setCurSel(0);
}

void SlideButton::setItemText(uint32_t index, const std::string & txt)
{
	nbThrowExceptionIf(index >= (int)m_items.size(), std::out_of_range, "index[%d] is out of range[0, %d)", index, (int)m_items.size());
	m_items[index].text = txt;
}

void SlideButton::setCurSel(int index)
{
	auto oldSel = m_curSel;
	m_curSel = (index < 0 || index >= (int)m_items.size() || !isItemEnable(index)) ? -1 : index;

	if (oldSel >= 0)	m_items[oldSel].state = SlideButton::ItemState::State_Normal;
	if (m_curSel >= 0) m_items[m_curSel].state = SlideButton::ItemState::State_Select;

	if (oldSel != m_curSel)
		SelectChanged.invoke(index);
}

int SlideButton::getCurSel() const
{
	return m_curSel;
}

void SlideButton::enableItem(uint32_t index, bool enable)
{
	nbThrowExceptionIf(index >= (int)m_items.size(), std::out_of_range, "index[%d] is out of range[0, %d)", index, (int)m_items.size());
	m_items[index].state = enable ? m_items[index].state : ItemState::State_Disable;
}

bool SlideButton::isItemEnable(uint32_t index) const
{
	nbThrowExceptionIf(index >= (int)m_items.size(), std::out_of_range, "index[%d] is out of range[0, %d)", index, (int)m_items.size());
	return m_items[index].state != SlideButton::ItemState::State_Disable;
}

void SlideButton::setFont(ref<Font> font)
{
	m_font = font;
}

ref<Font> SlideButton::font() const
{
	return m_font;
}

ref<Font> SlideButton::getActualFont() const
{
	return m_font ? m_font : FontLibrary::getDefaultFont();
}

void SlideButton::setFontSize(float size)
{
	auto f = FontLibrary::addFont(getActualFont()->path(), (uint32_t)size);
	setFont(f);
}

float SlideButton::fontSize() const
{
	return getActualFont()->size();
}

void SlideButton::onTouch(const TouchEventArgs & e)
{
	auto itemWidth = getActualSize().width / m_items.size();
	if (e.action == TouchAction::Down)
	{
		int index = findItemByPos(e.x, e.y);
		if(index >= 0 && index < (int)m_items.size() && isItemEnable(index))
			setCurSel(index);
	}
}

void SlideButton::onRender()
{
	Node2D::onRender();
	auto font = getActualFont();
	Rect rc = getRenderRect();
	auto itemWidth = rc.width() / m_items.size();

	//绘制Button
	if (m_curSel >= 0 && m_btnNormal)
	{
		Rect btnRc = { rc.x() + itemWidth * m_curSel, rc.y(), itemWidth, rc.height() };
		Renderer2D::drawImage(btnRc, Transform::identityMatrix4(), m_btnNormal->frame, 1.0f);
	}
	//绘制文字
	auto op = TreeHelper::getActualOpacity(this);
	for (auto i = 0u; i < m_items.size(); ++i)
	{
		const auto &item = m_items[i];
		const auto &txt = item.text;
		auto txtSize = font->measure(txt);
		auto txtColor = item.state == ItemState::State_Normal ? m_clrTxtNormal : (item.state == ItemState::State_Select ? m_clrTxtSelect : m_clrTxtDisable);
		Point pt = { rc.x() + itemWidth * i + (itemWidth - txtSize.width) / 2, rc.y() + (rc.height() - txtSize.height) / 2.0f };
		Renderer2D::drawText(font, pt, txt, nb::colorToVec4(txtColor), op);
	}
}

int SlideButton::findItemByPos(float x, float y)
{
	Rect rc = getRenderRect();
	if (x < rc.x() || x >= rc.right())	return -1;

	auto itemWidth = getActualSize().width / m_items.size();
	return (int)((x - rc.x())/ itemWidth);
}

DotListCtrl::DotListCtrl()
	: DotListCtrl(0.0f, 0.0f, NAN, NAN)
{}

DotListCtrl::DotListCtrl(const Rect & rc)
	: DotListCtrl(rc.x(), rc.y(), rc.width(), rc.height())
{}

DotListCtrl::DotListCtrl(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
	, m_nCurSel(-1)
	, m_nDotCount(0)
	, m_eOrientation(Orientation::Horizontal)
	, m_bNeedUpdatePositions(false)
{
}

void DotListCtrl::setDotCount(int count)
{
	m_nDotCount = count;
	m_bNeedUpdatePositions = true;
}

int DotListCtrl::dotCount()
{
	return m_nDotCount;
}

void DotListCtrl::setDotImage(ref<ImageBrush> normal, ref<ImageBrush> sel)
{
	m_normalBrush = normal;
	m_selectBrush = sel;
	m_bNeedUpdatePositions = true;
}

void DotListCtrl::setCurSel(int index)
{
	m_nCurSel = index;
}

int DotListCtrl::getCurSel() const
{
	return m_nCurSel;
}

void DotListCtrl::onRender()
{
	Node2D::onRender();

	if (m_bNeedUpdatePositions)
	{
		updatePositions();
		m_bNeedUpdatePositions = false;
	}

	Rect renderRC = getRenderRect();
	auto op = getOpacity();
	for (int i = 0; i < m_nDotCount; ++i)
	{
		const Point &pt = m_vtPoints[i];
		auto brush = i == m_nCurSel ? m_selectBrush : m_normalBrush;
		if (brush)
		{
			Rect rc = Rect(renderRC.leftTop() + pt, brush->frame.sourceSize.x, brush->frame.sourceSize.y);
			Renderer2D::drawImage(rc, Transform::identityMatrix4(), brush->frame, op);
		}
	}
}

void DotListCtrl::updatePositions()
{
	m_vtPoints.clear();
	if (m_nDotCount <= 0)
	{
		return;
	}

	auto renderRC = getRenderRect();
	glm::vec2 itemSize = m_normalBrush ? m_normalBrush->frame.sourceSize : glm::vec2(0.0f);
	float y = (renderRC.height() - itemSize.y) / 2.0f;

	if (m_nDotCount == 1)
	{
		m_vtPoints.emplace_back((renderRC.width() - itemSize.x) / 2, y);
	}
	else
	{
		float itemSpace = (renderRC.width() - itemSize.x ) / (m_nDotCount -1);
		float x = 0.0f;
		for (int i = 0; i < m_nDotCount; ++i)
		{
			x = itemSpace * i;
			m_vtPoints.emplace_back(x, y);
		}
	}
}

PageCtrl::PageCtrl()
	: PageCtrl(0.0f, 0.0f, NAN, NAN)
{}

PageCtrl::PageCtrl(const Rect & rc)
	: PageCtrl(rc.x(), rc.y(), rc.width(), rc.height())
{}

PageCtrl::PageCtrl(float x, float y, float w, float h)
	: Node2D(x, y, w, h)
	, m_curPage(-1)
	, m_ptPress(-1.0f)
	, m_curOffset(0.0f)
	, m_aniFromOffset(0.0f)
	, m_aniEndOffset(0.0f)
{
	m_tlSwitchPage.duration = TimeSpan::fromMilliseconds(150);
	m_tlSwitchPage.Process += nbBindEventFunction(PageCtrl::onTimeLineProgress);
//	m_easingFunction = createRef<SineEase>();
}

void PageCtrl::addPage(ref<Node2D> page)
{
	addChild(page);
	updatePagePositions(calcOffsetFromPage(0));
	if (childCount() == 1)
	{
		setCurPage(0);
	}
}

void PageCtrl::removePage(int index)
{
	removeChild(index);
}

ref<Node2D> PageCtrl::getPage(int index)
{
	return getChildAt(index);
}

int PageCtrl::pageCount() const
{
	return childCount();
}

void PageCtrl::setCurPage(int page)
{
	auto oldPage = m_curPage;
	m_curPage = page;
	if (oldPage != m_curPage)
	{
		if(m_dotListCtrl) 
			m_dotListCtrl->setCurSel(curPage());
		CurPageChanged.invoke(m_curPage);
	}
}

int PageCtrl::curPage() const
{
	return m_curPage;
}

void PageCtrl::bindDotListCtrl(ref<DotListCtrl> dotListCtrl)
{
	m_dotListCtrl = dotListCtrl;
	m_dotListCtrl->setCurSel(curPage());
}

void PageCtrl::onTouch(const TouchEventArgs & e)
{
	if (e.action == TouchAction::Down)
	{
		m_ptPress = { e.x, e.y };
		m_offsetWhenPress = m_curOffset;
		m_tickWhenPress = getMilliseconds();
	}
	else if (e.action == TouchAction::Move)
	{
		if (m_ptPress != -1.0f)
		{
			float xOffset = e.x - m_ptPress.x;
			updatePagePositions(xOffset + m_offsetWhenPress);
		}
	}
	else if (e.action == TouchAction::Up)
	{
		m_ptPress = -1.0f;
		int toPage = -1;
		auto ticks = getMilliseconds() - m_tickWhenPress;
		auto dif = m_curOffset - m_offsetWhenPress;
		if (ticks < 200 && std::abs(dif) > 20.0f)
		{
			toPage = dif > 0 ? m_curPage - 1 : m_curPage + 1;
			toPage = nb::clamp(toPage, 0, pageCount() - 1);
		}
		else
		{
			toPage = calcPageFromOffset(m_curOffset);
		}
		m_aniFromOffset = m_curOffset;
		m_aniEndOffset = calcOffsetFromPage(toPage);
		m_tlSwitchPage.begin();
		setCurPage(toPage);
	}
}

void PageCtrl::onTimeLineProgress(const EventArgs & e)
{
	auto progress = m_tlSwitchPage.getCurrentProgress();
	if (m_easingFunction)
	{
		progress = (float)m_easingFunction->easeInCore(progress);
	}
	auto offset = m_aniFromOffset + (m_aniEndOffset - m_aniFromOffset) * progress;
	updatePagePositions(offset);
}

float PageCtrl::calcOffsetFromPage(int page)
{
	return -page * width();
}

int PageCtrl::calcPageFromOffset(float xOffset)
{
	auto offset = m_curOffset / width() - 0.5f;
	auto page = -((int)(offset * 2) / 2);
	page = nb::clamp(page, 0, pageCount() - 1);
	return page;
}

void PageCtrl::updatePagePositions(float xOffset)
{
	for (auto i = 0u; i < childCount(); ++i)
	{
		auto const &page = getChildAt(i);
		page->setX(xOffset + width() * i);
		page->setVisibility((page->x() > -width() && page->x() < width()) ? VisibilityE::Visible : VisibilityE::Hidden);
	}
	m_curOffset = xOffset;
}
