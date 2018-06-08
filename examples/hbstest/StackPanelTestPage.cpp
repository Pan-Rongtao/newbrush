#include "StackPanelTestPage.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"

using namespace nb::Gui;

StackPanelTestPage::StackPanelTestPage(void)
{
	nb::Gui::StackPanelPtr stackPanel = new nb::Gui::StackPanel();
	stackPanel->Orientation() = Orientation_Vert;
	nb::Gui::Rectangle *r1 = new nb::Gui::Rectangle();
	r1->Fill = new nb::Media::SolidColorBrush(nb::System::Color(255, 0, 0));
	r1->Width() = Float(100);
	r1->Height() = Float(50);
	stackPanel->Children()->Add(r1);

	nb::Gui::Rectangle *r2 = new nb::Gui::Rectangle();
	r2->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 0));
	r2->Width() = Float(100);
	r2->Height() = Float(30);
	stackPanel->Children()->Add(r2);

	nb::Gui::Rectangle *r3 = new nb::Gui::Rectangle();
	r3->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 255));
	r3->Width() = Float(300);
	r3->Height() = Float(30);
	stackPanel->Children()->Add(r3);

	nb::Gui::WrapPanelPtr wrapPanelChild = new nb::Gui::WrapPanel();
	wrapPanelChild->Orientation() = Orientation_Hor;
	nb::Gui::Rectangle *r4 = new nb::Gui::Rectangle();
	r4->Fill = new nb::Media::SolidColorBrush(nb::System::Color(255, 0, 0));
	r4->Width() = Float(100);
	r4->Height() = Float(50);
	wrapPanelChild->Children()->Add(r4);

	nb::Gui::Rectangle *r5 = new nb::Gui::Rectangle();
	r5->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 0));
	r5->Width() = Float(100);
	r5->Height() = Float(30);
	wrapPanelChild->Children()->Add(r5);

	nb::Gui::Rectangle *r6 = new nb::Gui::Rectangle();
	r6->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 255));
	r6->Width() = Float(300);
	r6->Height() = Float(30);
	wrapPanelChild->Children()->Add(r6);

	stackPanel->Children()->Add(wrapPanelChild);

	SetRootPanel(stackPanel);
}

StackPanelTestPage::~StackPanelTestPage(void)
{
}
