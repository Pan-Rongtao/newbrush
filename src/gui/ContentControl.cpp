#include "gui/ContentControl.h"

using namespace nb;
using namespace nb::gui;

ContentControl::ContentControl()
{
}

DependencyProperty ContentControl::ContentProperty()
{
	static auto dp = DependencyProperty::registerDependency<ContentControl, std::shared_ptr<UIElement>>("Content", std::make_shared<UIElement>());
	return dp;
}

void ContentControl::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = get<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);//UIElement未做裁剪，所以render区域可能会超出范围
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
//		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(rc.width(), rc.height()));
//	drawContext.queue(Renderer());
	auto content = get<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
		content->onRender(drawContext);
}

void ContentControl::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == ContentControl::ContentProperty())
	{
		auto content = any_cast<std::shared_ptr<UIElement>>(args.newValue);
		content->setParent(this);
	}
}

Size ContentControl::measureOverride(const Size & availableSize)
{
	auto content = get<std::shared_ptr<UIElement>>(ContentProperty());
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
	auto content = get<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		//Content()->arrage(Rect(0.0, 0.0, DesiredSize));
		content->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}
