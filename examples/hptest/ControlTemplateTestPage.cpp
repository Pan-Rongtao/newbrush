#include "ControlTemplateTestPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/Button.h"
#include "../../../Include/Gui/UIElementFactory.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Core/ObjectFactory.h"
#include "../../../Include/Gui/Image.h"
#include "../../../Include/Gui/ImageBrush.h"

using namespace nb::Gui;
using namespace nb::Media;

ControlTemplateTestPage::ControlTemplateTestPage(void)
{
//	nb::Core::ObjectFactory factory(nbType::GetType<Grid>());
//	nb::Core::ObjectFactory *x = new nb::Core::ObjectFactory(nbType::GetType<RowDefinitionCollection>());
//	factory.SetRefValue(Grid::GetRowDefCollectionProperty(), x);
//	factory.CreateObject();

	nb::Gui::RectanglePtr r = new nb::Gui::Rectangle();
	nb::Gui::Rectangle *x = r;
	r->Fill = new nb::Media::SolidColorBrush(); 

//	r->SetRefValue(r->FillzProperty(), new nb::Media::SolidColorBrush());
//	r->SetRefValue(r->FillzProperty(), new nb::Media::SolidColorBrush());


	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);

//	grid->RowDefCollection = new RowDefinitionCollection();
//	grid->ColDefCollection = new ColDefinitionCollection();

/*	UIElementFactoryPtr factory = new UIElementFactory(nbType::GetType<nb::Gui::Grid>());
	factory->SetRefValue(Grid::GetRowDefCollectionProperty(), new RowDefinitionCollection());
	factory->SetRefValue(Grid::GetColDefCollectionProperty(), new ColDefinitionCollection());



	UIElementFactoryPtr factChild = new UIElementFactory(nbType::GetType<nb::Gui::Rectangle>());
	factory->AppendChild(factChild);

	factChild->SetValueValue(UIElement::GetWidthProperty(), Float(150));
	factChild->SetValueValue(UIElement::GetHeightProperty(), Float(50));
	factChild->SetRefValue(nb::Gui::Rectangle::GetFillProperty(), new nb::Media::SolidColorBrush(Color(100, 0, 0)));


	UIElementPtr rect = factory->CreateElement();

	grid->AddChild(rect);

	Grid::SetRow(rect, 0);
	Grid::SetCol(rect, 0);*/

//	Float *x = (Float *)&factory->GetValueValue(Grid::WidthTestProperty());

//	ImageBrushPtr brush = new ImageBrush("F:\\G3\\G3_ModelZ\\Dist\\ResidentFlash\\navigation\\app\\res\\img\\Main\\Clear_Coast.png");
//	ImageSourcePtr source = new ImageSource("F:\\G3\\G3_ModelZ\\Dist\\ResidentFlash\\navigation\\app\\res\\img\\Main\\Clear_Coast.png");
//	Image *im = new Image();
//	im->SetSource(source);
//	grid->Children()->Add(im);

	for(int i=0; i<1; i++)
	{
	Button *btn = new Button();
	btn->Width() = 80;
	btn->Height() = 50;
	grid->Children()->Add(btn);
	}


}

ControlTemplateTestPage::~ControlTemplateTestPage(void)
{
}
