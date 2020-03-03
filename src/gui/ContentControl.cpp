#include "newbrush/gui/ContentControl.h"

using namespace nb;
using namespace nb::gui;

ContentControl::ContentControl()
{
}

DependencyProperty ContentControl::ContentProperty()
{
	static auto dp = DependencyProperty::registerDependency<ContentControl, std::shared_ptr<UIElement>>("Content", nullptr);
	return dp;
}

void ContentControl::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);//UIElement未做裁剪，所以render区域可能会超出范围
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
//		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(rc.width(), rc.height()));
//	drawContext.queue(Renderer());
	auto content = getValue<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
		content->onRender(drawContext);
}

uint32_t ContentControl::childrenCount() const
{
	auto content = getValue<std::shared_ptr<UIElement>>(ContentControl::ContentProperty());
	return content ? 1 : 0;
}

UIElement * ContentControl::getChild(uint32_t index)
{
	auto content = getValue<std::shared_ptr<UIElement>>(ContentControl::ContentProperty());
	return content.get();
}

void ContentControl::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	Control::onPropertyChanged(args);
	if (args.property == ContentControl::ContentProperty())
	{
		auto content = args.newValue.extract<std::shared_ptr<UIElement>>();
		content->setParent(this);
	}
}

Size ContentControl::measureOverride(const Size & availableSize)
{
	auto content = getValue<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		content->measure(availableSize);
		//return Content()->DesiredSize;
		return availableSize;
	}
	else
	{
		return Control::measureOverride(availableSize);
	}
}

Size ContentControl::arrangeOverride(const Size & finalSize)
{
	auto content = getValue<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		//Content()->arrage(Rect(0.0, 0.0, DesiredSize));
		content->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}
