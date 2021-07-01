#include "catch2/catch.hpp"
#include "newbrush/Binding.h"
#include "newbrush/Log.h"

using namespace nb;

enum class Enum
{
	v0,
	v1,
	v2,
};

class BindingObject : public Object
{
	RTTR_ENABLE(Object)
public:

	bool bool_p = false;
	char char_p = 0;
	signed char schar_p = 0;
	unsigned char uchar_p= 0;
	wchar_t wchar_p= 0;
	char16_t char16_p= 0;
	char32_t char32_p= 0;
	short short_p= 0;
	unsigned short ushort_p= 0;
	int int32_p= 0;
	unsigned int uint32_p= 0;
	long long_p= 0;
	unsigned long ulong_p= 0;
	long long longlong_p= 0;
	unsigned ulonglong_p= 0;
	float float_p= 0;
	double double_p= 0;
	long double longdouble_p= 0;
	std::string string_p = "";
	std::wstring wstring_p = L"";
	Enum enum_p = Enum::v0;
	Point point_p = {0};
	Point3D point3d_p;
	Size size_p;
	Rect rect_p;
	Color color_p;
	ref<Color> colorptr_p = nullptr;
	Thickness thickness_p;
	TimeSpan timespan_p;
	Date date_p;
	Time time_p;

	int int32_p1= 0;
	int int32_p2= 0;
	std::string string_p1 = "";

	glm::vec2 vec2_p{ 0.0f };
	glm::vec3 vec3_p{ 0.0f };
	glm::vec4 vec4_p{ 0.0f };
};

RTTR_REGISTRATION
{
	registration::class_<BindingObject>("BindingObject")(policy::ctor::as_std_shared_ptr)
	.property("bool_p", &BindingObject::bool_p)
	.property("char_p", &BindingObject::char_p)
	.property("schar_p", &BindingObject::schar_p)
	.property("uchar_p", &BindingObject::uchar_p)
	.property("wchar_p", &BindingObject::wchar_p)
	.property("char16_p", &BindingObject::char16_p)
	.property("char32_p", &BindingObject::char32_p)
	.property("short_p", &BindingObject::short_p)
	.property("string_p", &BindingObject::string_p)
	.property("ushort_p", &BindingObject::ushort_p)
	.property("int32_p", &BindingObject::int32_p)
	.property("uint32_p", &BindingObject::uint32_p)
	.property("long_p", &BindingObject::long_p)
	.property("ulong_p", &BindingObject::ulong_p)
	.property("longlong_p", &BindingObject::longlong_p)
	.property("ulonglong_p", &BindingObject::ulonglong_p)
	.property("float_p", &BindingObject::float_p)
	.property("double_p", &BindingObject::double_p)
	.property("longdouble_p", &BindingObject::longdouble_p)
	.property("string_p", &BindingObject::string_p)
	.property("wstring_p", &BindingObject::wstring_p)
	.property("enum_p", &BindingObject::enum_p)
	.property("point_p", &BindingObject::point_p)
	.property("point3d_p", &BindingObject::point3d_p)
	.property("size_p", &BindingObject::size_p)
	.property("rect_p", &BindingObject::rect_p)
	.property("color_p", &BindingObject::color_p)
	.property("colorptr_p", &BindingObject::colorptr_p)
	.property("thickness_p", &BindingObject::thickness_p)
	.property("timespan_p", &BindingObject::timespan_p)
	.property("date_p", &BindingObject::date_p)
	.property("time_p", &BindingObject::time_p)

	.property("int32_p1", &BindingObject::int32_p1)
	.property("int32_p2", &BindingObject::int32_p2)
	.property("string_p1", &BindingObject::string_p1)

	.property("vec2_p", &BindingObject::vec2_p)
	.property("vec3_p", &BindingObject::vec3_p)
	.property("vec4_p", &BindingObject::vec4_p)
	;

}

TEST_CASE("TestBinding", "[TestBinding]")
{
	auto bindingObject = createRef<BindingObject>();

	auto m_dataRoot = nb::makeDataObject("root");
	m_dataRoot->add(makeDataVar<bool>("bool_v", true));
	m_dataRoot->add(makeDataVar<char>("char_v", 'a'));
	m_dataRoot->add(makeDataVar<signed char>("schar_v", 'b'));
	m_dataRoot->add(makeDataVar<unsigned char>("uchar_v", 'c'));
	m_dataRoot->add(makeDataVar<wchar_t>("wchar_v", 1));
	m_dataRoot->add(makeDataVar<char16_t>("char16_v", 2));
	m_dataRoot->add(makeDataVar<char32_t>("char32_v", 3));
	m_dataRoot->add(makeDataVar<short>("short_v", 4));
	m_dataRoot->add(makeDataVar<unsigned short>("ushort_v", 5));
	m_dataRoot->add(makeDataVar<int>("int32_v", 6));
	m_dataRoot->add(makeDataVar<unsigned int>("uint32_v", 7));
	m_dataRoot->add(makeDataVar<long>("long_v", 8));
	m_dataRoot->add(makeDataVar<unsigned long>("ulong_v", 9));
	m_dataRoot->add(makeDataVar<long long>("longlong_v", 10));
	m_dataRoot->add(makeDataVar<unsigned long long>("ulonglong_v", 11));
	m_dataRoot->add(makeDataVar<float>("float_v", 1.0f));
	m_dataRoot->add(makeDataVar<double>("double_v", 2.0));
	m_dataRoot->add(makeDataVar<long double>("longdouble_v", 3.0));
	m_dataRoot->add(makeDataVar<std::string>("string_v", "abcdefg"));
	m_dataRoot->add(makeDataVar<std::wstring>("wstring_v", L"hijklmn"));
	m_dataRoot->add(makeDataVar<Enum>("enum_v", Enum::v1));
	m_dataRoot->add(makeDataVar<Point>("point_v", Point(2)));
	m_dataRoot->add(makeDataVar<ref<Color>>("colorptr_v", createRef<Color>(Colors::red)));

	auto _2rdObj = makeDataObject("obj");
	_2rdObj->add(makeDataFloat("x", 100.0));
	m_dataRoot->add(_2rdObj);

	auto array = makeDataArray("array");
	auto temp = makeDataObject("template");
	temp->add(makeDataBool("x"));
	temp->add(makeDataInt("y"));
	temp->add(makeDataFloat("z"));
	temp->add(makeDataString("w"));
	array->setTemplate(temp);

	auto item0 = makeDataObject("template");
	item0->add(makeDataBool("x", true));
	item0->add(makeDataInt("y", 1));
	item0->add(makeDataFloat("z", 2.0));
	item0->add(makeDataString("w", "yes"));
	array->addItem(item0);

	//check bindingObject's values before binding
	{
		CHECK(bindingObject->bool_p == false);
		CHECK(bindingObject->char_p == 0);
		CHECK(bindingObject->schar_p == 0);
		CHECK(bindingObject->uchar_p == 0);
		CHECK(bindingObject->wchar_p == 0);
		CHECK(bindingObject->char16_p == 0);
		CHECK(bindingObject->char32_p == 0);
		CHECK(bindingObject->short_p == 0);
		CHECK(bindingObject->ushort_p == 0);
		CHECK(bindingObject->int32_p == 0);
		CHECK(bindingObject->uint32_p == 0);
		CHECK(bindingObject->long_p == 0);
		CHECK(bindingObject->ulong_p == 0);
		CHECK(bindingObject->longlong_p == 0);
		CHECK(bindingObject->ulonglong_p == 0);
		CHECK(bindingObject->float_p == 0);
		CHECK(bindingObject->double_p == 0);
		CHECK(bindingObject->longdouble_p == 0);
		CHECK(bindingObject->string_p == "");
		CHECK(bindingObject->wstring_p == L"");
		CHECK(bindingObject->enum_p == Enum::v0);
		CHECK(bindingObject->point_p == 0.0f);
		CHECK(bindingObject->colorptr_p == nullptr);
		CHECK(bindingObject->int32_p1 == 0);
		CHECK(bindingObject->int32_p2 == 0);
		CHECK(bindingObject->string_p1 == "");
	}

	BindingMaster::addBinding(bindingObject, bindingObject->prop("bool_p"), createRef<Binding>(m_dataRoot, "bool_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("char_p"), createRef<Binding>(m_dataRoot, "char_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("schar_p"), createRef<Binding>(m_dataRoot, "schar_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("uchar_p"), createRef<Binding>(m_dataRoot, "uchar_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("wchar_p"), createRef<Binding>(m_dataRoot, "wchar_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("char16_p"), createRef<Binding>(m_dataRoot, "char16_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("char32_p"), createRef<Binding>(m_dataRoot, "char32_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("short_p"), createRef<Binding>(m_dataRoot, "short_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("ushort_p"), createRef<Binding>(m_dataRoot, "ushort_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("int32_p"), createRef<Binding>(m_dataRoot, "int32_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("uint32_p"), createRef<Binding>(m_dataRoot, "uint32_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("long_p"), createRef<Binding>(m_dataRoot, "long_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("ulong_p"), createRef<Binding>(m_dataRoot, "ulong_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("longlong_p"), createRef<Binding>(m_dataRoot, "longlong_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("ulonglong_p"), createRef<Binding>(m_dataRoot, "ulonglong_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("float_p"), createRef<Binding>(m_dataRoot, "float_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("double_p"), createRef<Binding>(m_dataRoot, "double_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("longdouble_p"), createRef<Binding>(m_dataRoot, "longdouble_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("string_p"), createRef<Binding>(m_dataRoot, "string_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("wstring_p"), createRef<Binding>(m_dataRoot, "wstring_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("enum_p"), createRef<Binding>(m_dataRoot, "enum_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("point_p"), createRef<Binding>(m_dataRoot, "point_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("colorptr_p"), createRef<Binding>(m_dataRoot, "colorptr_v"));
	BindingMaster::addBinding(bindingObject, bindingObject->prop("string_p1"), createRef<Binding>(m_dataRoot, "obj.x"));
	
	auto bd = createRef<Binding>(m_dataRoot, "int32_v");
	BindingMaster::addBinding(bindingObject, bindingObject->prop("int32_p1"), bd);
	BindingMaster::addBinding(bindingObject, bindingObject->prop("int32_p2"), bd);

	//check bindingObject's values after binding
	{
		CHECK(bindingObject->bool_p == true);
		CHECK(bindingObject->char_p == 'a');
		CHECK(bindingObject->schar_p == 'b');
		CHECK(bindingObject->uchar_p == 'c');
		CHECK(bindingObject->wchar_p == 1);
		CHECK(bindingObject->char16_p == 2);
		CHECK(bindingObject->char32_p == 3);
		CHECK(bindingObject->short_p == 4);
		CHECK(bindingObject->ushort_p == 5);
		CHECK(bindingObject->int32_p == 6);
		CHECK(bindingObject->uint32_p == 7);
		CHECK(bindingObject->long_p == 8);
		CHECK(bindingObject->ulong_p == 9);
		CHECK(bindingObject->longlong_p == 10);
		CHECK(bindingObject->ulonglong_p == 11);
		CHECK(nb::epsilonEqual(bindingObject->float_p, 1.0f));
		CHECK(nb::epsilonEqual(bindingObject->double_p, 2.0));
		CHECK(nb::epsilonEqual(bindingObject->longdouble_p, 3.0));
		CHECK(bindingObject->string_p == "abcdefg");
		CHECK(bindingObject->wstring_p == L"hijklmn");
		CHECK(bindingObject->enum_p == Enum::v1);
		CHECK(bindingObject->point_p == 2.0f);
		CHECK(*(bindingObject->colorptr_p) == Colors::red);
		CHECK(bindingObject->int32_p1 == 6);
		CHECK(bindingObject->int32_p2 == 6);
		CHECK(bindingObject->string_p1 == "100");
	}

	m_dataRoot->get("bool_v")->set(false);
	m_dataRoot->get("char_v")->set('x');
	m_dataRoot->get("schar_v")->set('y');
	m_dataRoot->get("uchar_v")->set('z');
	m_dataRoot->get("wchar_v")->set(wchar_t(11));
	m_dataRoot->get("char16_v")->set(char16_t(22));
	m_dataRoot->get("char32_v")->set(char32_t(33));
	m_dataRoot->get("short_v")->set(44);
	m_dataRoot->get("ushort_v")->set(55);
	m_dataRoot->get("int32_v")->set(66);
	m_dataRoot->get("uint32_v")->set(77);
	m_dataRoot->get("long_v")->set((long)88);
	m_dataRoot->get("ulong_v")->set((unsigned long)99);
	m_dataRoot->get("longlong_v")->set((long long)111);
	m_dataRoot->get("ulonglong_v")->set((unsigned long long)222);
	m_dataRoot->get("float_v")->set(5.55);
	m_dataRoot->get("double_v")->set(6.66);
	m_dataRoot->get("longdouble_v")->set((long double)7.77);
	m_dataRoot->get("string_v")->set("desay");
	m_dataRoot->get("wstring_v")->set(std::wstring(L"sv"));
	m_dataRoot->get("enum_v")->set(Enum::v2);
	m_dataRoot->get("point_v")->set(Point(9.0, 9.0));
	m_dataRoot->get("colorptr_v")->set(createRef<Color>(Colors::blue));
	m_dataRoot->getObject("obj")->get("x")->set(123.01);

	//check bindingObject's values after set data
	{
		CHECK(bindingObject->bool_p == false);
		CHECK(bindingObject->char_p == 'x');
		CHECK(bindingObject->schar_p == 'y');
		CHECK(bindingObject->uchar_p == 'z');
		CHECK(bindingObject->wchar_p == 11);
		CHECK(bindingObject->char16_p == 22);
		CHECK(bindingObject->char32_p == 33);
		CHECK(bindingObject->short_p == 44);
		CHECK(bindingObject->ushort_p == 55);
		CHECK(bindingObject->int32_p == 66);
		CHECK(bindingObject->uint32_p == 77);
		CHECK(bindingObject->long_p == 88);
		CHECK(bindingObject->ulong_p == 99);
		CHECK(bindingObject->longlong_p == 111);
		CHECK(bindingObject->ulonglong_p == 222);
		CHECK(nb::epsilonEqual(bindingObject->float_p, 5.55f));
		CHECK(nb::epsilonEqual(bindingObject->double_p, 6.66));
		CHECK(nb::epsilonEqual(bindingObject->longdouble_p, 7.77));
		CHECK(bindingObject->string_p == "desay");
		CHECK(bindingObject->wstring_p == L"sv");
		CHECK(bindingObject->enum_p == Enum::v2);
		CHECK(bindingObject->point_p == 9.0f);
		CHECK(*(bindingObject->colorptr_p) == Colors::blue);
		CHECK(bindingObject->int32_p1 == 66);
		CHECK(bindingObject->int32_p2 == 66);
		CHECK(bindingObject->string_p1 == "123.01");
	}


}
