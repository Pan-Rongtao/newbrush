#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/core/Binding.h"
#include "newbrush/core/BindingMaster.h"
#include "newbrush/core/DataContext.h"
#include "newbrush/gui/TextBlock.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test nb::Binding", "[Binding]")
{
	auto m_element = std::make_shared<UIElement>();

	auto m_dataRoot = DataObject::gen("root");
	m_dataRoot->add(DataVar<bool>::gen("bool", false));
	m_dataRoot->add(DataVar<char>::gen("char", 'a'));
	m_dataRoot->add(DataVar<signed char>::gen("signed char", 'b'));
	m_dataRoot->add(DataVar<unsigned char>::gen("unsigned char", 'c'));
	m_dataRoot->add(DataVar<wchar_t>::gen("wchar_t", 1));
	m_dataRoot->add(DataVar<char16_t>::gen("char16_t", 2));
	m_dataRoot->add(DataVar<char32_t>::gen("char32_t", 3));
	m_dataRoot->add(DataVar<short>::gen("short", 4));
	m_dataRoot->add(DataVar<unsigned short>::gen("unsigned short", 5));
	m_dataRoot->add(DataVar<int>::gen("int", 6));
	m_dataRoot->add(DataVar<unsigned int>::gen("unsigned int", 7));
	m_dataRoot->add(DataVar<long>::gen("long", 8));
	m_dataRoot->add(DataVar<unsigned long>::gen("unsigned long", 9));
	m_dataRoot->add(DataVar<long long>::gen("long long", 10));
	m_dataRoot->add(DataVar<unsigned long long>::gen("unsigned long long", 11));
	m_dataRoot->add(DataVar<float>::gen("float", 1.0f));
	m_dataRoot->add(DataVar<double>::gen("double", 2.0));
	m_dataRoot->add(DataVar<long double>::gen("long double", 3.0));
	m_dataRoot->add(DataVar<std::string>::gen("string", ""));
	m_dataRoot->add(DataVar<std::wstring>::gen("wstring", L""));
	m_dataRoot->add(DataVar<VisibilityE>::gen("visible", VisibilityE::Hidden));
	m_dataRoot->add(DataVar<Point>::gen("point", Point()));
	m_dataRoot->add(DataVar<Thickness>::gen("margin", Thickness()));
	m_dataRoot->add(DataVar<std::shared_ptr<Brush>>::gen("brush", nullptr));

	auto obj = DataObject::gen("obj");
	obj->add(DataVar<float>::gen("x", 100.0));
	m_dataRoot->add(obj);

	auto array = DataArray::gen("array");
	auto temp = DataObject::gen("template");
	temp->add(DataVar<bool>::gen("x"));
	temp->add(DataVar<int>::gen("y"));
	temp->add(DataVar<float>::gen("z"));
	temp->add(DataVar<std::string>::gen("w"));
	array->setTemplate(temp);

	auto item0 = DataObject::gen("template");
	item0->add(DataVar<bool>::gen("x", true));
	item0->add(DataVar<int>::gen("y", 1));
	item0->add(DataVar<float>::gen("z", 2.0));
	item0->add(DataVar<std::string>::gen("w", "yes"));
	array->addItem(item0);

	BindingMaster::addBinding(m_element, TextBlock::FocusableProperty(), std::make_shared<Binding>(m_dataRoot, "bool"));
	BindingMaster::addBinding(m_element, TextBlock::WidthProperty(), std::make_shared<Binding>(m_dataRoot, "float"));
	BindingMaster::addBinding(m_element, TextBlock::HeightProperty(), std::make_shared<Binding>(m_dataRoot, "double"));
	BindingMaster::addBinding(m_element, TextBlock::FontWeightProperty(), std::make_shared<Binding>(m_dataRoot, "long"));
	BindingMaster::addBinding(m_element, TextBlock::MinWidthProperty(), std::make_shared<Binding>(m_dataRoot, "unsigned long"));
	BindingMaster::addBinding(m_element, TextBlock::OpacityProperty(), std::make_shared<Binding>(m_dataRoot, "float"));
	BindingMaster::addBinding(m_element, TextBlock::VisibilityProperty(), std::make_shared<Binding>(m_dataRoot, "visible"));
	BindingMaster::addBinding(m_element, TextBlock::OffsetProperty(), std::make_shared<Binding>(m_dataRoot, "point"));
	BindingMaster::addBinding(m_element, TextBlock::MarginProperty(), std::make_shared<Binding>(m_dataRoot, "margin"));
	BindingMaster::addBinding(m_element, TextBlock::BackgroundProperty(), std::make_shared<Binding>(m_dataRoot, "brush"));
	BindingMaster::addBinding(m_element, TextBlock::TextProperty(), std::make_shared<Binding>(m_dataRoot, "obj.x"));
	
	auto bd = std::make_shared<Binding>(m_dataRoot, "int");
	BindingMaster::addBinding(m_element, TextBlock::MinHeightProperty(), std::make_shared<Binding>(m_dataRoot, "int"));
	BindingMaster::addBinding(m_element, TextBlock::MaxHeightProperty(), std::make_shared<Binding>(m_dataRoot, "int"));

	m_dataRoot->get("bool")->set(true);
	m_dataRoot->get("char")->set('x');
	m_dataRoot->get("signed char")->set('y');
	m_dataRoot->get("unsigned char")->set('z');
	m_dataRoot->get("wchar_t")->set(wchar_t(11));
	m_dataRoot->get("char16_t")->set(char16_t(22));
	m_dataRoot->get("char32_t")->set(char32_t(33));
	m_dataRoot->get("short")->set(44);
	m_dataRoot->get("unsigned short")->set(55);
	m_dataRoot->get("int")->set(66);
	m_dataRoot->get("unsigned int")->set(77);
	m_dataRoot->get("long")->set(88);
	m_dataRoot->get("unsigned long")->set(99);
	m_dataRoot->get("long long")->set(111);
	m_dataRoot->get("unsigned long long")->set(222);
	m_dataRoot->get("float")->set(5.55);
	m_dataRoot->get("double")->set(6.66);
	m_dataRoot->get("long double")->set((long double)7.77);
	m_dataRoot->get("string")->set("desay");
	m_dataRoot->get("wstring")->set("sv");
	m_dataRoot->get("visible")->set(VisibilityE::Visible);
	m_dataRoot->get("point")->set(Point(1.0, 1.0));
	m_dataRoot->get("margin")->set(Thickness(10));
	std::shared_ptr<Brush> brush = std::make_shared<SolidColorBrush>(Colors::red());
	m_dataRoot->get("brush")->set(brush);
	m_dataRoot->getObject("obj")->get("x")->set(123.00);

	auto e = m_element->getValue<VisibilityE>(UIElement::VisibilityProperty());
	auto e1 = m_element->getValue<std::string>(TextBlock::TextProperty());

	auto minHeight = m_element->getValue<float>(TextBlock::MinHeightProperty());
	auto maxHeight = m_element->getValue<float>(TextBlock::MaxHeightProperty());
}
