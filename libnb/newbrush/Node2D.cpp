#include "newbrush/Node2D.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Application.h"

using namespace nb;

Node2D::Node2D()
	: Node2D(0, 0, NAN, NAN)
{}

Node2D::Node2D(const Rect & rc)
	: Node2D(rc.x(), rc.y(), rc.width(), rc.height())
{}

Node2D::Node2D(float x, float y, float w, float h)
	: Node2D(x, y, w, h, nullptr)
{}

Node2D::Node2D(float x, float y, float w, float h, ref<Brush> background)
	: m_position(x, y)
	, m_size(w, h)
	, m_opacity(1.0f)
	, m_focusAble(true)
	, m_hasFocus(false)
	, m_visibility(VisibilityE::Visible)
	, m_horizontalAlignment(HorizontalAlignment::Left)
	, m_verticalAlignment(VerticalAlignment::Top)
	, m_isEnable(true)
	, m_isMouseOver(false)
	, m_parent(nullptr)
	, m_background(background)
{
}

float Node2D::x() const
{
	return m_position.x;
}

void Node2D::setX(float x)
{
	m_position.x = x;
}

float Node2D::y() const
{
	return m_position.y;
}

void Node2D::setY(float y)
{
	m_position.y = y;
}

void Node2D::setPosition(const Point & pt)
{
	m_position = pt;
}

const Point &Node2D::position() const
{
	return m_position;
}

void Node2D::setWidth(float width)
{
	m_size.width = width;
}

float Node2D::width() const
{
	return m_size.width;
}

void Node2D::setHeight(float height)
{
	m_size.height = height;
}

float Node2D::height() const
{
	return m_size.height;
}

void Node2D::setSize(const Size & size)
{
	m_size = size;
}

const Size &Node2D::size() const
{
	return m_size;
}

void Node2D::setRect(const Rect & rc)
{
	m_position = rc.leftTop();
	m_size = rc.size();
}

Rect Node2D::rect() const
{
	return Rect(m_position, m_size);
}

void Node2D::setMargin(const Thickness & margin)
{
	m_margin = margin;
}

const Thickness & Node2D::margin() const
{
	return m_margin;
}

void Node2D::setOpacity(float opacity)
{
	m_opacity = opacity;
}

float Node2D::getOpacity() const
{
	return m_opacity;
}

void Node2D::setHorizontalAlignment(HorizontalAlignment h)
{
	m_horizontalAlignment = h;
}

HorizontalAlignment Node2D::horizontalAlignment() const
{
	return m_horizontalAlignment;
}

void Node2D::setVerticalAlignment(VerticalAlignment v)
{
	m_verticalAlignment = v;
}

VerticalAlignment Node2D::verticalAlignment() const
{
	return m_verticalAlignment;
}

void Node2D::setAlignmentCenter()
{
	setHorizontalAlignment(HorizontalAlignment::Center);
	setVerticalAlignment(VerticalAlignment::Center);
}

void Node2D::setVisibility(VisibilityE visibility)
{
	m_visibility = visibility;
}

VisibilityE Node2D::visibility() const
{
	return m_visibility;
}

void Node2D::setBackground(ref<Brush> bkg)
{
	m_background = bkg;
}

ref<Brush> Node2D::background() const
{
	return m_background;
}

void Node2D::setClipRect(const Rect & clipRC)
{
	m_clipRC = clipRC;
}

const Rect &Node2D::getClipRect() const
{
	return m_clipRC;
}

void Node2D::setTransform(ref<Transform2D> transform)
{
	m_transform = transform;
}

ref<Transform2D> Node2D::getTransform() const
{
	return m_transform;
}

void Node2D::setEnable(bool bEnable)
{
	m_isEnable = bEnable;
}

bool Node2D::isEnable() const
{
	return m_isEnable;
}

bool Node2D::hasFocus() const
{
	return m_hasFocus;
}

//直接忽略返回的情况
//1、如果不可见
//2、与上次measure参数一致
//3、已经在处理measure中，防止measure函数内有某种操作导致重新进入measure函数（比如设置某些属性）
//4、child不脏（还未了解）
//该函数是为了确认DesiredSize
void Node2D::measure(const Size & availabelSize)
{
	if (m_visibility != VisibilityE::Visible)
	{
		return;
	}

	auto const &margin = m_margin;// Thickness(m_position.x, m_position.y, 0.0f, 0.0f);
	auto const &width = m_size.width;
	auto const &height = m_size.height;
	auto const &minWidth = 0.0f;
	auto const &minHeight = 0.0f;
	auto const &maxWidth = std::numeric_limits<float>::max();
	auto const &maxHeight = std::numeric_limits<float>::max();
	//减去magin计算出本来的constrainedSize
	auto constrainedSize = Size(availabelSize.width - margin.left - margin.right, availabelSize.height - margin.top - margin.bottom);
	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	constrainedSize.width = clamp<float>(minWidth, maxWidth, std::isnan(width) ? constrainedSize.width : width);
	constrainedSize.height = clamp<float>(minHeight, maxHeight, std::isnan(height) ? constrainedSize.height : height);

	//measureOverride返回控件期望大小desiredSizeTemp，需要调整到保证在(Min, Max)区间
	//如果手动设置了Width，调整Width到(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, constrainedSize.width())
	//同样的规则应用于Height
	auto desiredSizeTemp = measureOverride(constrainedSize);
	desiredSizeTemp.width = clamp<float>(minWidth, maxWidth, std::isnan(width) ? desiredSizeTemp.width : width);
	desiredSizeTemp.height = clamp<float>(minHeight, maxHeight, std::isnan(height) ? desiredSizeTemp.height : height);

	//由于child不关注和计算magin，因此需重新+margin
	desiredSizeTemp += Size(margin.left + margin.right, margin.top + margin.bottom);
	//保证在（0, availabelSize)区间
	desiredSizeTemp.width = clamp(0.0f, availabelSize.width, desiredSizeTemp.width);
	desiredSizeTemp.height = clamp(0.0f, availabelSize.height, desiredSizeTemp.height);
	m_desiredSize = desiredSizeTemp;
}

void Node2D::arrage(const Rect & finalRect)
{
	if (m_visibility != VisibilityE::Visible)
		return;

	auto const &margin = m_margin;// Thickness(m_position.x, m_position.y, 0.0f, 0.0f);
	auto const &width = m_size.width;
	auto const &height = m_size.height;
	auto const &minWidth = 0.0f;
	auto const &minHeight = 0.0f;
	auto const &maxWidth = std::numeric_limits<float>::max();
	auto const &maxHeight = std::numeric_limits<float>::max();
	//减去magin计算出本来的arrangeSize以及clientSize
	auto arrangeSize = Size(finalRect.width() - margin.left - margin.right, finalRect.height() - margin.top - margin.bottom);
	auto clientSize = arrangeSize;
	//调整arrange大于DesiredSize
	//arrangeSize.reset(std::max(DesiredSize().width(), arrangeSize.width()), std::max(DesiredSize().height(), arrangeSize.height()));
	//如果Aligment不是Stretch，直接将arrangeSize设置为DesiredSize，以保证传入arrangeOverride的arrangeSize没有Stretch
	auto const &horizontalAlignment = m_horizontalAlignment;
	auto const &verticalAlignment = m_verticalAlignment;
	if (horizontalAlignment != HorizontalAlignment::Stretch)	arrangeSize.width = m_desiredSize.width;
	if (verticalAlignment != VerticalAlignment::Stretch)		arrangeSize.height = m_desiredSize.height;

	//如果手动设置了Width，调整Width到bound(MinWidth, MaxWidth, Width)
	//否则，调整Width到(MinWidth, MaxWidth, arrangeSize.width())
	//同样的规则应用于Height
	arrangeSize.width = clamp(minWidth, maxWidth, std::isnan(width) ? arrangeSize.width : width);
	arrangeSize.height = clamp(minHeight, maxHeight, std::isnan(height) ? arrangeSize.height : height);

	//arrangeOverride后的RenderSize是不需要调整的非裁剪区域，而不是最终的可见区域
	auto innerInkSize = arrangeOverride(arrangeSize);
	auto renderSize = innerInkSize;
	//裁剪，保证innerInkSize在Max之内
	if (std::isnan(width) && innerInkSize.width > maxWidth)	
		innerInkSize.width = maxWidth;
	if (std::isnan(height) && innerInkSize.height > maxHeight)	
		innerInkSize.height = maxHeight;

	float offsetX = 0.0f, offsetY = 0.0f;
	switch (horizontalAlignment)
	{
	case HorizontalAlignment::Left:	offsetX = finalRect.x() + margin.left;												break;
	case HorizontalAlignment::Center:	offsetX = finalRect.x() + margin.left + (clientSize.width - renderSize.width) / 2;	break;
	case HorizontalAlignment::Right:	offsetX = finalRect.width() - margin.right - renderSize.width;						break;
	default:							offsetX = renderSize.width >= clientSize.width ? finalRect.left() + margin.left : finalRect.x() + margin.left + (clientSize.width - renderSize.width) / 2;	break;
	}
	switch (verticalAlignment)
	{
	case VerticalAlignment::Top:		offsetY = finalRect.y() + margin.top;												break;
	case VerticalAlignment::Center:	offsetY = finalRect.y() + margin.top + (clientSize.height - renderSize.height) / 2;	break;
	case VerticalAlignment::Bottom:	offsetY = finalRect.y() + (finalRect.height() - margin.bottom - renderSize.height);	break;
	default:							offsetY = renderSize.height >= clientSize.height ? finalRect.top() + margin.top : finalRect.y() + margin.top + (clientSize.height - renderSize.height) / 2;	break;
	}
	m_offsetToParent = Point(offsetX, offsetY) + m_position;
	m_actualSize = renderSize;
}

Size Node2D::measureOverride(const Size & availableSize)
{
	for (auto child : children())
	{
		auto w = child->width();
		auto h = child->height();
		child->measure(Size((std::isnan(w) ? availableSize.width : w), (std::isnan(h) ? availableSize.height : h)));
	}
	return availableSize;
}

Size Node2D::arrangeOverride(const Size & finalSize)
{
	for (auto child : children())
	{
		child->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}

void Node2D::onTouch(const TouchEventArgs & e)
{
	Touch.invoke(e);
}

void Node2D::onScroll(const ScrollEventArgs & e)
{
	Scroll.invoke(e);
}

void Node2D::onKey(const KeyEventArgs & e)
{
	Key.invoke(e);
}

void Node2D::onFocusChanged(const FocusEventArgs & e)
{
	m_hasFocus = e.focused;
}

void Node2D::onRender()
{
	if (m_visibility != VisibilityE::Visible)
		return;

	drawBrush(m_background);
	drawChildren();

	if (m_scene)
	{
		Renderer2D::endBatch();

		float oldViewportX, oldViewportY, oldViewportWidth, oldViewportHeight;
		GLUtils::getViewport(oldViewportX, oldViewportY, oldViewportWidth, oldViewportHeight);

		auto camera = m_scene->getCamera();
		Rect rc = getRenderRect();

		GLUtils::viewport(rc.x(), oldViewportHeight - rc.bottom(), rc.width(), rc.height());
		camera->setAspect(rc.width() / rc.height());

		m_scene->onRender();

		GLUtils::viewport(oldViewportX, oldViewportY, oldViewportWidth, oldViewportHeight);
		camera->setAspect(oldViewportWidth / oldViewportHeight);

		Renderer2D::_beginBatch(false);
	}
}

bool Node2D::hitTest(const Point & pt) const
{
	Rect renderRect = getRenderRect();
	return renderRect.contains(pt);
}

ref<Node2D> Node2D::createWithTextureFrame(const TextureFrame & texFrame, bool useBrush, float x, float y)
{
	auto node = createRef<Node2D>(x, y, texFrame.sourceSize.x, texFrame.sourceSize.y);
	if(useBrush)
		node->setBackground(createRef<ImageBrush>(texFrame));
	return node;
}

ref<Node2D> Node2D::createWithTextureFrameName(const std::string & texAtlasKey, const std::string & frameName, float x, float y)
{
	return createWithTextureFrameName(texAtlasKey, frameName, true, x, y);
}

ref<Node2D> Node2D::createWithTextureFrameName(const std::string & texAtlasKey, const std::string & frameName, bool useBrush, float x, float y)
{
	auto texFrame = TextureLibrary::getFrameFromTextureAtlas(texAtlasKey, frameName);
	return createWithTextureFrame(texFrame, useBrush, x, y);
}

const Size & Node2D::getDesiredSize() const
{
	return m_desiredSize;
}

const Size & Node2D::getActualSize() const
{
	return m_actualSize;
}

const Point & Node2D::getOffsetToParent() const
{
	return m_offsetToParent;
}

Rect Node2D::getRenderRect() const
{
	Rect rc = { TreeHelper::getWolrdOffset((Node2D *)this), m_actualSize };
	return rc;
}

void Node2D::addChild(ref<Node2D> child)
{
	insertChild(childCount(), child);
}

void Node2D::insertChild(unsigned index, ref<Node2D> child)
{
	nbThrowExceptionIf(!child, std::invalid_argument, "child is nullptr");
	nbThrowExceptionIf(index > childCount(), std::out_of_range, "index");

	child->m_parent = this;
	m_children.insert(m_children.begin() + index, child);
}

void Node2D::removeChild(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	m_children.erase(m_children.begin() + index);
}

void Node2D::removeChild(ref<Node2D> child)
{
	for (auto iter = m_children.begin(); iter != m_children.end(); ++iter)
	{
		if (*iter == child)
		{
			m_children.erase(iter);
			return;
		}
	}
}

unsigned Node2D::childCount() const
{
	return m_children.size();
}

bool Node2D::hasChild() const
{
	return childCount() > 0;
}

ref<Node2D> Node2D::getChildAt(unsigned index)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	return m_children[index];
}

void Node2D::setChildAt(unsigned index, ref<Node2D> newChild)
{
	nbThrowExceptionIf(index >= childCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)childCount());
	newChild->m_parent = this;
	m_children[index] = newChild;
}

void Node2D::clearChildren()
{
	m_children.clear();
}

const std::vector<ref<Node2D>>& Node2D::children() const
{
	return m_children;
}

Node2D * Node2D::getParent() const
{
	return m_parent;
}

void Node2D::setScene(ref<Scene> scene)
{
	m_scene = scene;
}

ref<Scene> Node2D::getScene()
{
	return m_scene;
}

void Node2D::touchThunk(const TouchEventArgs & e)
{
	auto hit = Node2D::hitTest(Point(e.x, e.y));

	TouchEventArgs ex = e;
	if (e.action == TouchAction::Down)
	{
		if (hit)
		{
			onTouch(e);
		}
	}
	else if (e.action == TouchAction::Move)
	{
		if (hit)
		{
			if (!m_isMouseOver)
			{
				ex.action = TouchAction::Enter;
				onTouch(ex);
				m_isMouseOver = true;
			}
			ex.action = TouchAction::Move;
			onTouch(ex);
		}
		else
		{
			if (m_isMouseOver)
			{
				ex.action = TouchAction::Leave;
				onTouch(ex);
				m_isMouseOver = false;
			}
			else
			{
				ex.action = TouchAction::Move;
				onTouch(ex);
			}
		}
	}
	else if (e.action == TouchAction::Up)
	{
		onTouch(e);
	}
}

void Node2D::scrollThunk(const ScrollEventArgs & e)
{
	onScroll(e);
}

void Node2D::keyThunk(const KeyEventArgs & e)
{
	onKey(e);
}

void Node2D::updateLayout(const Size & availabelSize)
{
	SystemHelper::updateFPS();

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->measure(availabelSize);
	auto const &rootDesiredSize = this->getDesiredSize();
	this->arrage(Rect(0.0, 0.0, availabelSize));
	
	Renderer2D::beginBatch();
	this->onRender();
	Renderer2D::endBatch();
}

void Node2D::drawChildren()
{
	for (auto child : children())
	{
		if (child->visibility() == VisibilityE::Visible)
			child->onRender();
	}
}

void Node2D::drawBrush(ref<Brush> brush)
{
	if (brush)
	{
		auto renderTransform = m_transform ? m_transform->value() : Transform::identityMatrix4();
		Rect rc = getRenderRect();
		auto opacity = TreeHelper::getActualOpacity(this);
		if (is<SolidColorBrush>(brush))
		{
			auto _brush = as<SolidColorBrush>(brush);
			auto c = _brush->color;
			Renderer2D::drawRect(rc, renderTransform, nb::colorToVec4(c), opacity, m_clipRC);
		}
		else if (is<ImageBrush>(brush))
		{
			auto _brush = as<ImageBrush>(brush);
			Renderer2D::drawImage(rc, renderTransform, _brush->frame, opacity, m_clipRC);
		}
		else if (is<EffectBrush>(brush))
		{
			auto _brush = as<EffectBrush>(brush);
			Renderer2D::drawEffect(rc, renderTransform, _brush->material, std::vector<ref<Light>>{ _brush->light }, m_clipRC);
		}
	}
}
