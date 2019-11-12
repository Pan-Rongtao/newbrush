#include "gui/ContentControl.h"
#include "gles/Quadrangle.h"
#include "gles/Context.h"

using namespace nb;
using namespace nb::gui;

ContentControl::ContentControl()
	: Content([&](shared_ptr<UIElement> v) { set(ContentProperty(), v); }, [&]()->shared_ptr<UIElement>& {return get<std::shared_ptr<UIElement>>(ContentProperty()); })
{
	PropertyChanged += [&](const PropertyChangedArgs &arg) 
	{
		if (arg.dp == ContentControl::ContentProperty()) 
		{
			auto content = any_cast<std::shared_ptr<UIElement>>(arg.value);
			if (childCount() == 0)	addChild(content);
			else					m_children[0] = content;
		}
	};
}

DependencyProperty ContentControl::ContentProperty()
{
	static auto dp = DependencyProperty::registerDependency<ContentControl, std::shared_ptr<UIElement>>("Content", std::make_shared<UIElement>());
	return dp;
}

void ContentControl::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());//UIElement未做裁剪，所以render区域可能会超出范围
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
//		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(rc.width(), rc.height()));
//	drawContext->queue(Renderer());
	if (Content())
		Content()->onRender(drawContext);
}

Size ContentControl::measureOverride(const Size & availableSize)
{
	if (Content())
	{
		Content()->measure(availableSize);
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
	if (Content())
	{
		//Content()->arrage(Rect(0.0, 0.0, DesiredSize));
		Content()->arrage(Rect(0.0, 0.0, finalSize));
	}
	return finalSize;
}
