#include "WrapPanelTestPage.h"
#include "../../../Include/Gui/WrapPanel.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"

using namespace nb::Gui;

WrapPanelTestPage::WrapPanelTestPage(void)
{
	nb::Gui::WrapPanelPtr wrapPanel = new nb::Gui::WrapPanel();
	SetRootPanel(wrapPanel);
	wrapPanel->Orientation() = Orientation_Hor;

	nb::Gui::WrapPanelPtr wrapPanelChild = new nb::Gui::WrapPanel();
	wrapPanelChild->Orientation() = Orientation_Vert;
	
	nb::Gui::Rectangle *r5 = new nb::Gui::Rectangle();
	r5->Fill = new nb::Media::SolidColorBrush(nb::System::Color(255, 255, 0));
	r5->Width() = Float(351);
	r5->Height() = Float(30);

	wrapPanelChild->Children()->Add(r5);
	nb::Gui::Rectangle *r4 = new nb::Gui::Rectangle();
	r4->Fill = new nb::Media::SolidColorBrush(nb::System::Color(255, 0, 255));
	r4->Width() = Float(50);
	r4->Height() = Float(50);
	wrapPanelChild->Children()->Add(r4);
	
	
	nb::Gui::Rectangle *r6 = new nb::Gui::Rectangle();
	r6->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 255));
	r6->Width() = Float(301);
	r6->Height() = Float(30);
	wrapPanelChild->Children()->Add(r6);
	
	nb::Gui::Rectangle *r1 = new nb::Gui::Rectangle();
	r1->Fill = new nb::Media::SolidColorBrush(nb::System::Color(255, 0, 0));
	r1->Width() = Float(100);
	r1->Height() = Float(50);
	r1->VertAlignment() = nb::Gui::VerticalAlignment_Center;
	wrapPanel->Children()->Add(r1);

	nb::Gui::Rectangle *r2 = new nb::Gui::Rectangle();
	r2->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 0));
	r2->Width() = Float(300);
	r2->Height() = Float(48);
	wrapPanel->Children()->Add(r2);
	
	wrapPanel->Children()->Add(wrapPanelChild);
	
	nb::Gui::Rectangle *r3 = new nb::Gui::Rectangle();
	r3->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 0, 255));
	r3->Width() = Float(400);
	r3->Height() = Float(80);
	wrapPanel->Children()->Add(r3);
}

WrapPanelTestPage::~WrapPanelTestPage(void)
{
}
