#include "TestUIElement.h"

using namespace nb;
void TestUIElement::test()
{
	m_uielement = std::make_shared<UIElement>();
	m_uielement->addHandler(UIElement::MouseDownEvent(), RoutedEventHandler<MouseButtonEventArgs>([](const MouseButtonEventArgs &args) {
		auto x = args.ButtonState;
	}));

	MouseButtonEventArgs args(1000, MouseButtonE::Left);
	args.OriginalSource = m_uielement.get();
	args.Event = UIElement::MouseDownEvent();
	m_uielement->raiseEvent(args);
}
