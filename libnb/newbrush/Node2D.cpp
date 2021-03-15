#include "newbrush/Node2D.h"
#include "newbrush/Camera.h"
#include "newbrush/Mesh.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include "newbrush/GLUnit.h"
#include "newbrush/Log.h"

using namespace nb;

Node2D::Node2D()
	: Node2D(0, 0, NAN, NAN)
{
}

Node2D::Node2D(const Rect & rc)
	: Node2D(rc.x(), rc.y(), rc.width(), rc.height())
{
}

Node2D::Node2D(float x, float y, float w, float h)
	: m_position(x, y)
	, m_width(w)
	, m_height(h)
	, m_opacity(1.0f)
	, m_focusAble(true)
	, m_hasFocus(false)
	, m_visibility(VisibilityE::Visible)
	, m_horizontalAlignment(HorizontalAlignmentE::Left)
	, m_verticalAlignment(VerticalAlignmentE::Top)
	, m_isEnable(true)
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

Point Node2D::position() const
{
	return Point();
}

void Node2D::setWidth(float width)
{
	if (width != m_width)
	{
		m_width = width;
	}
}

float Node2D::width() const
{
	return m_width;
}

void Node2D::setHeight(float height)
{
	if (height != m_height)
	{
		m_height = height;
	}
}

float Node2D::height() const
{
	return m_height;
}

void Node2D::setSize(const Size & size)
{
	m_width = size.width;
	m_height = size.height;
}

Size Node2D::size() const
{
	return Size(m_width, m_height);
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

void Node2D::setHorizontalAlignment(HorizontalAlignmentE h)
{
	m_horizontalAlignment = h;
}

HorizontalAlignmentE Node2D::horizontalAlignment() const
{
	return m_horizontalAlignment;
}

void Node2D::setVerticalAlignment(VerticalAlignmentE v)
{
	m_verticalAlignment = v;
}

VerticalAlignmentE Node2D::verticalAlignment() const
{
	return m_verticalAlignment;
}

void Node2D::setAlignmentCenter()
{
	setHorizontalAlignment(HorizontalAlignmentE::Center);
	setVerticalAlignment(VerticalAlignmentE::Center);
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
	if (bkg != m_background)
	{
		m_background = bkg;
	}
}

ref<Brush> Node2D::background() const
{
	return m_background;
}

void Node2D::setTransform(ref<Transform2D> transform)
{
	m_transform = transform;
}

ref<Transform2D> Node2D::getTransform() const
{
	return m_transform;
}

glm::mat4 Node2D::getRenderTransform() const
{
	glm::mat4 mat(1.0);
	auto p = this;
	do {
		if (p->m_transform)
			mat = p->m_transform->value() * mat;
	} while ((p->getParent()) && (p = (Node2D *)p->getParent()));
	return mat;
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
	auto const &width = m_width;
	auto const &height = m_height;
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
	auto const &width = m_width;
	auto const &height = m_height;
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
	if (horizontalAlignment != HorizontalAlignmentE::Stretch)	arrangeSize.width = m_desiredSize.width;
	if (verticalAlignment != VerticalAlignmentE::Stretch)		arrangeSize.height = m_desiredSize.height;

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
	case HorizontalAlignmentE::Left:	offsetX = finalRect.x() + margin.left;												break;
	case HorizontalAlignmentE::Center:	offsetX = finalRect.x() + margin.left + (clientSize.width - renderSize.width) / 2;	break;
	case HorizontalAlignmentE::Right:	offsetX = finalRect.width() - margin.right - renderSize.width;						break;
	default:							offsetX = renderSize.width >= clientSize.width ? finalRect.left() + margin.left : finalRect.x() + margin.left + (clientSize.width - renderSize.width) / 2;	break;
	}
	switch (verticalAlignment)
	{
	case VerticalAlignmentE::Top:		offsetY = finalRect.y() + margin.top;												break;
	case VerticalAlignmentE::Center:	offsetY = finalRect.y() + margin.top + (clientSize.height - renderSize.height) / 2;	break;
	case VerticalAlignmentE::Bottom:	offsetY = finalRect.y() + (finalRect.height() - margin.bottom - renderSize.height);	break;
	default:							offsetY = renderSize.height >= clientSize.height ? finalRect.top() + margin.top : finalRect.y() + margin.top + (clientSize.height - renderSize.height) / 2;	break;
	}
	m_offsetToParent = Point(offsetX, offsetY) + m_position;
	m_actualSize = renderSize;

}

Size Node2D::measureOverride(const Size & availableSize)
{
	for (auto child : children())
	{
		auto c = as<Node2D>(child);
		auto w = c->width();
		auto h = c->height();
		c->measure(Size((std::isnan(w) ? availableSize.width : w), (std::isnan(h) ? availableSize.height : h)));
	}
	return availableSize;
}

Size Node2D::arrangeOverride(const Size & finalSize)
{
	for (auto child : children())
	{
		auto c = as<Node2D>(child);
		auto desiredSize = c->getDesiredSize();
		c->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}

void Node2D::onTouch(const TouchEventArgs & e)
{
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
	for (auto child : children())
	{
		child->onRender();
	}
}

bool Node2D::hitTest(const Point & pt) const
{
	Rect renderRect = getRenderRect();
	return renderRect.contains(pt);
}

ref<Node2D> Node2D::createWithTextureFrame(const TextureFrame & texFrame, bool useBrush, float x, float y)
{
	auto node = createRef<Node2D>(x, y, texFrame.size.x, texFrame.size.y);
	node->setMargin(Thickness(texFrame.trimmedSize.x, texFrame.trimmedSize.y, texFrame.trimmedSize.x, texFrame.trimmedSize.y));
	if(useBrush)
		node->setBackground(ImageBrush::createWitchTextureFrame(texFrame));
	return node;
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

void Node2D::touchThunk(const TouchEventArgs & e)
{
	auto hit = Node2D::hitTest(Point(e.x, e.y));

	TouchEventArgs ex = e;
	if (e.action == TouchActionE::down)
	{
		if (hit)
		{
			onTouch(e);
		}
	}
	else if (e.action == TouchActionE::move)
	{
		if (hit)
		{
			if (!m_isMouseOver)
			{
				ex.action = TouchActionE::enter;
				onTouch(ex);
				m_isMouseOver = true;
			}
			ex.action = TouchActionE::move;
			onTouch(ex);
		}
		else if(m_isMouseOver)
		{
			ex.action = TouchActionE::leave;
			onTouch(ex);
			m_isMouseOver = false;
		}
	}
	else if (e.action == TouchActionE::up)
	{
		onTouch(e);
	}
}

void Node2D::updateLayout(const Size & availabelSize)
{
	this->measure(availabelSize);
	auto const &rootDesiredSize = this->getDesiredSize();
	this->arrage(Rect(0.0, 0.0, availabelSize));


	static int frames = 0;
	static uint64_t t0 = getMilliseconds();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	{
		Renderer2D::beginBatch();
		this->onRender();
		Renderer2D::endBatch();
	}
	++frames;
	uint64_t t1 = getMilliseconds();
	if (t1 - t0 >= 5000)
	{
		float fps = frames * 1000.0f / (t1 - t0);
		frames = 0;
		t0 = t1;
		auto state = Renderer2D::getStats();
		Log::info("drawCount={}, quadCount={}, batch fps:{}", state.drawCount, state.quadCount, fps);
	}
}

void Node2D::drawBrush(ref<Brush> brush)
{
	if (brush)
	{
		static glm::mat4 mat(1.0f);
		auto renderTransform = m_transform ? m_transform->value() : mat;
		//auto renderTransform = getRenderTransform();
		Rect rc = getRenderRect();
		auto opacity = m_opacity * brush->opacity;
		if (is<SolidColorBrush>(brush))
		{
			auto _brush = as<SolidColorBrush>(brush);
			auto c = _brush->color;
			Renderer2D::drawRect(rc, renderTransform, glm::vec4(c.rf(), c.gf(), c.bf(), c.af()), opacity);
		}
		else if (is<ImageBrush>(brush))
		{
			auto _brush = as<ImageBrush>(brush);
			Rect texRect = { _brush->targetOffset.x, _brush->targetOffset.y, _brush->targetSize.x, _brush->targetSize.y };
			Renderer2D::drawImage(rc, renderTransform, _brush->texture, texRect, _brush->rotated, opacity);
		}
		else if (is<EffectBrush>(brush))
		{
			auto _brush = as<EffectBrush>(brush);
			Renderer2D::drawEffect(rc, renderTransform, _brush->material, std::vector<ref<Light>>{ _brush->light });
		}
	}
}
