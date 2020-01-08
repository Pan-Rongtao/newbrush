#include "TestBinding.h"
#include "media/SolidColorBrush.h"

void TestBinding::test()
{
	m_window = std::make_shared<Window>();
	m_text = std::make_shared<TextBlock>();
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
	m_dataRoot = std::make_shared<ObjectData>("root");
	m_dataRoot->insertChild(std::make_shared<ValueData<bool>>("bool", false));
	m_dataRoot->insertChild(std::make_shared<ValueData<float>>("float", 1.0f));
	m_dataRoot->insertChild(std::make_shared<ValueData<double>>("double", 2.0));
	m_dataRoot->insertChild(std::make_shared<ValueData<long>>("long", 3));
	m_dataRoot->insertChild(std::make_shared<ValueData<unsigned long>>("unsigned long", 4));
	m_dataRoot->insertChild(std::make_shared<ValueData<int8_t>>("int8_t", 11));
	m_dataRoot->insertChild(std::make_shared<ValueData<int16_t>>("int16_t", 22));
	m_dataRoot->insertChild(std::make_shared<ValueData<int32_t>>("int32_t", 33));
	m_dataRoot->insertChild(std::make_shared<ValueData<int64_t>>("int64_t", 44));
	m_dataRoot->insertChild(std::make_shared<ValueData<uint8_t>>("uint8_t", 111));
	m_dataRoot->insertChild(std::make_shared<ValueData<uint16_t>>("uint16_t", 222));
	m_dataRoot->insertChild(std::make_shared<ValueData<uint32_t>>("uint32_t", 333));
	m_dataRoot->insertChild(std::make_shared<ValueData<uint64_t>>("uint64_t", 444));
	m_dataRoot->insertChild(std::make_shared<ValueData<std::string>>("string", ""));
	m_dataRoot->insertChild(std::make_shared<ValueData<VisibilityE>>("visible", VisibilityE::Hidden));
	m_dataRoot->insertChild(std::make_shared<ValueData<Point>>("offset", Point()));
	m_dataRoot->insertChild(std::make_shared<ValueData<Thickness>>("margin", Thickness()));
	m_dataRoot->insertChild(std::make_shared<ValueData<std::shared_ptr<Brush>>>("background", nullptr));

	BindingMaster::addBinding(m_text, TextBlock::FocusableProperty(), std::make_shared<Binding>(m_dataRoot, "focus"));
	BindingMaster::addBinding(m_text, TextBlock::WidthProperty(), std::make_shared<Binding>(m_dataRoot, "float"));
	BindingMaster::addBinding(m_text, TextBlock::HeightProperty(), std::make_shared<Binding>(m_dataRoot, "double"));
	BindingMaster::addBinding(m_text, TextBlock::FontWeightProperty(), std::make_shared<Binding>(m_dataRoot, "long"));
	BindingMaster::addBinding(m_text, TextBlock::MinWidthProperty(), std::make_shared<Binding>(m_dataRoot, "unsigned long"));
	BindingMaster::addBinding(m_text, TextBlock::OpacityProperty(), std::make_shared<Binding>(m_dataRoot, "int8_t"));
	BindingMaster::addBinding(m_text, TextBlock::VisibilityProperty(), std::make_shared<Binding>(m_dataRoot, "visible"));
	BindingMaster::addBinding(m_text, TextBlock::OffsetProperty(), std::make_shared<Binding>(m_dataRoot, "offset"));
	BindingMaster::addBinding(m_text, TextBlock::MarginProperty(), std::make_shared<Binding>(m_dataRoot, "margin"));
	BindingMaster::addBinding(m_text, TextBlock::BackgroundProperty(), std::make_shared<Binding>(m_dataRoot, "background"));
	BindingMaster::addBinding(m_text, TextBlock::TextProperty(), std::make_shared<Binding>(m_dataRoot, "uint64_t"));

	auto boolv = std::dynamic_pointer_cast<ValueData<bool>>((*m_dataRoot)["bool"]);
	boolv->set(true);
	boolv->set(false);
	std::dynamic_pointer_cast<ValueData<float>>((*m_dataRoot)["float"])->set(108.3f);
	std::dynamic_pointer_cast<ValueData<double>>((*m_dataRoot)["double"])->set(118.3);
	std::dynamic_pointer_cast<ValueData<long>>((*m_dataRoot)["long"])->set(120);
	std::dynamic_pointer_cast<ValueData<unsigned long>>((*m_dataRoot)["unsigned long"])->set(121);
	std::dynamic_pointer_cast<ValueData<int8_t>>((*m_dataRoot)["int8_t"])->set((int8_t)255);
	std::dynamic_pointer_cast<ValueData<VisibilityE>>((*m_dataRoot)["visible"])->set(VisibilityE::Collapsed);
	std::dynamic_pointer_cast<ValueData<Point>>((*m_dataRoot)["offset"])->set(Point(1, 2));
	std::dynamic_pointer_cast<ValueData<Thickness>>((*m_dataRoot)["margin"])->set(Thickness(1, 2, 3, 4));
	std::dynamic_pointer_cast<ValueData<std::shared_ptr<Brush>>>((*m_dataRoot)["background"])->set(std::make_shared<SolidColorBrush>(Colors::red()));
	auto x = std::dynamic_pointer_cast<ValueData<uint64_t>>((*m_dataRoot)["uint64_t"]);
	x->set(112233);
}
