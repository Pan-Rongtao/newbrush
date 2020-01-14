#include "TestBinding.h"
#include "media/SolidColorBrush.h"

void TestBinding::test()
{
//	m_window = std::make_shared<Window>();
	m_text = std::make_shared<UIElement>();
/*	m_text->PropertyChanged += [](const TextBlock::PropertyChangedArgs &args)
	{
		if (args.value.type() == typeid(bool))						printf("[%s]=%s\n", args.dp.name().data(), any_cast<bool>(args.value) ? "true" : "false");
		else if(args.value.type() == typeid(float))					printf("[%s]=%.2f\n", args.dp.name().data(), any_cast<float>(args.value));
		else if (args.value.type() == typeid(double))				printf("[%s]=%.2f\n", args.dp.name().data(), any_cast<double>(args.value));
		else if (args.value.type() == typeid(long))					printf("[%s]=%d\n", args.dp.name().data(), any_cast<long>(args.value));
		else if (args.value.type() == typeid(unsigned long))		printf("[%s]=%d\n", args.dp.name().data(), any_cast<unsigned long>(args.value));
		else if (args.value.type() == typeid(int8_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<int8_t>(args.value));
		else if (args.value.type() == typeid(int16_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<int16_t>(args.value));
		else if (args.value.type() == typeid(int32_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<int32_t>(args.value));
		else if (args.value.type() == typeid(int64_t))				printf("[%s]=%lld\n", args.dp.name().data(), any_cast<int64_t>(args.value));
		else if (args.value.type() == typeid(uint8_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<uint8_t>(args.value));
		else if (args.value.type() == typeid(uint16_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<uint16_t>(args.value));
		else if (args.value.type() == typeid(uint32_t))				printf("[%s]=%d\n", args.dp.name().data(), any_cast<uint32_t>(args.value));
		else if (args.value.type() == typeid(uint64_t))				printf("[%s]=%lld\n", args.dp.name().data(), any_cast<uint64_t>(args.value));
		else if (args.value.type() == typeid(std::string))			printf("[%s]=%s\n", args.dp.name().data(), any_cast<std::string>(args.value).data());
		else if(args.value.type() == typeid(Point))
		{
			auto v = any_cast<Point>(args.value);
			printf("[%s]=(%.2f, %.2f)\n", args.dp.name().data(), v.x(), v.y());
		}
		else if (args.value.type() == typeid(Thickness))
		{
			auto v = any_cast<Thickness>(args.value);
			printf("[%s]=(%.2f, %.2f, %.2f, %.2f)\n", args.dp.name().data(), v.left(), v.top(), v.right(), v.bottom());
		}
		else
		{
			printf("[%s] is changed, type[%s]\n", args.dp.name().data(), args.value.type().name());
		}
	};
	*/
	m_dataRoot = DataObject::gen("root");
	m_dataRoot->add(VarData<bool>::gen("bool", false));
	m_dataRoot->add(VarData<char>::gen("char", 'a'));
	m_dataRoot->add(VarData<signed char>::gen("signed char", 'b'));
	m_dataRoot->add(VarData<unsigned char>::gen("unsigned char", 'c'));
	m_dataRoot->add(VarData<wchar_t>::gen("wchar_t", 1));
	m_dataRoot->add(VarData<char16_t>::gen("char16_t", 2));
	m_dataRoot->add(VarData<char32_t>::gen("char32_t", 3));
	m_dataRoot->add(VarData<short>::gen("short", 4));
	m_dataRoot->add(VarData<unsigned short>::gen("unsigned short", 5));
	m_dataRoot->add(VarData<int>::gen("int", 6));
	m_dataRoot->add(VarData<unsigned int>::gen("unsigned int", 7));
	m_dataRoot->add(VarData<long>::gen("long", 8));
	m_dataRoot->add(VarData<unsigned long>::gen("unsigned long", 9));
	m_dataRoot->add(VarData<long long>::gen("long long", 10));
	m_dataRoot->add(VarData<unsigned long long>::gen("unsigned long long", 11));
	m_dataRoot->add(VarData<float>::gen("float", 1.0f));
	m_dataRoot->add(VarData<double>::gen("double", 2.0));
	m_dataRoot->add(VarData<long double>::gen("long double", 3.0));
	m_dataRoot->add(VarData<std::string>::gen("string", ""));
	m_dataRoot->add(VarData<std::wstring>::gen("wstring", L""));
	m_dataRoot->add(VarData<VisibilityE>::gen("visible", VisibilityE::Hidden));
	m_dataRoot->add(VarData<Point>::gen("point", Point()));
	m_dataRoot->add(VarData<Thickness>::gen("margin", Thickness()));
	m_dataRoot->add(VarData<std::shared_ptr<Brush>>::gen("brush", nullptr));

	auto obj = DataObject::gen("obj");
	obj->add(VarData<float>::gen("x", 100.0));
	m_dataRoot->add(obj);

	BindingMaster::addBinding(m_text, TextBlock::FocusableProperty(), std::make_shared<Binding>(m_dataRoot, "bool"));
	BindingMaster::addBinding(m_text, TextBlock::WidthProperty(), std::make_shared<Binding>(m_dataRoot, "float"));
	BindingMaster::addBinding(m_text, TextBlock::HeightProperty(), std::make_shared<Binding>(m_dataRoot, "double"));
	BindingMaster::addBinding(m_text, TextBlock::FontWeightProperty(), std::make_shared<Binding>(m_dataRoot, "long"));
	BindingMaster::addBinding(m_text, TextBlock::MinWidthProperty(), std::make_shared<Binding>(m_dataRoot, "unsigned long"));
	BindingMaster::addBinding(m_text, TextBlock::OpacityProperty(), std::make_shared<Binding>(m_dataRoot, "float"));
	BindingMaster::addBinding(m_text, TextBlock::VisibilityProperty(), std::make_shared<Binding>(m_dataRoot, "visible"));
	BindingMaster::addBinding(m_text, TextBlock::OffsetProperty(), std::make_shared<Binding>(m_dataRoot, "point"));
	BindingMaster::addBinding(m_text, TextBlock::MarginProperty(), std::make_shared<Binding>(m_dataRoot, "margin"));
	BindingMaster::addBinding(m_text, TextBlock::BackgroundProperty(), std::make_shared<Binding>(m_dataRoot, "brush"));
	BindingMaster::addBinding(m_text, TextBlock::TextProperty(), std::make_shared<Binding>(m_dataRoot, "obj.x"));

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

	auto e = m_text->get<VisibilityE>(UIElement::VisibilityProperty());
	auto e1 = m_text->get<std::string>(TextBlock::TextProperty());
}
