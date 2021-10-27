#include "catch2/catch.hpp"
#include "newbrush/Binding.h"
#include "newbrush/Log.h"
#include "Data.h"

using namespace nb;

TEST_CASE("Binding", "[Binding]")
{
	auto obj = createRef<RttrObject>();

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

	//check obj's values before binding
	{
		CHECK(obj->bool_p == false);
		CHECK(obj->char_p == 0);
		CHECK(obj->schar_p == 0);
		CHECK(obj->uchar_p == 0);
		CHECK(obj->wchar_p == 0);
		CHECK(obj->char16_p == 0);
		CHECK(obj->char32_p == 0);
		CHECK(obj->short_p == 0);
		CHECK(obj->ushort_p == 0);
		CHECK(obj->int32_p == 0);
		CHECK(obj->uint32_p == 0);
		CHECK(obj->long_p == 0);
		CHECK(obj->ulong_p == 0);
		CHECK(obj->longlong_p == 0);
		CHECK(obj->ulonglong_p == 0);
		CHECK(obj->float_p == 0);
		CHECK(obj->double_p == 0);
		CHECK(obj->longdouble_p == 0);
		CHECK(obj->string_p == "");
		CHECK(obj->wstring_p == L"");
		CHECK(obj->enum_p == Enum::v0);
		CHECK(obj->point_p == 0.0f);
		CHECK(obj->colorptr_p == nullptr);
		CHECK(obj->int32_p1 == 0);
		CHECK(obj->int32_p2 == 0);
		CHECK(obj->string_p1 == "");
	}

	BindingMaster::addBinding(obj, obj->prop("bool_p"), createRef<Binding>(m_dataRoot, "bool_v"));
	BindingMaster::addBinding(obj, obj->prop("char_p"), createRef<Binding>(m_dataRoot, "char_v"));
	BindingMaster::addBinding(obj, obj->prop("schar_p"), createRef<Binding>(m_dataRoot, "schar_v"));
	BindingMaster::addBinding(obj, obj->prop("uchar_p"), createRef<Binding>(m_dataRoot, "uchar_v"));
	BindingMaster::addBinding(obj, obj->prop("wchar_p"), createRef<Binding>(m_dataRoot, "wchar_v"));
	BindingMaster::addBinding(obj, obj->prop("char16_p"), createRef<Binding>(m_dataRoot, "char16_v"));
	BindingMaster::addBinding(obj, obj->prop("char32_p"), createRef<Binding>(m_dataRoot, "char32_v"));
	BindingMaster::addBinding(obj, obj->prop("short_p"), createRef<Binding>(m_dataRoot, "short_v"));
	BindingMaster::addBinding(obj, obj->prop("ushort_p"), createRef<Binding>(m_dataRoot, "ushort_v"));
	BindingMaster::addBinding(obj, obj->prop("int32_p"), createRef<Binding>(m_dataRoot, "int32_v"));
	BindingMaster::addBinding(obj, obj->prop("uint32_p"), createRef<Binding>(m_dataRoot, "uint32_v"));
	BindingMaster::addBinding(obj, obj->prop("long_p"), createRef<Binding>(m_dataRoot, "long_v"));
	BindingMaster::addBinding(obj, obj->prop("ulong_p"), createRef<Binding>(m_dataRoot, "ulong_v"));
	BindingMaster::addBinding(obj, obj->prop("longlong_p"), createRef<Binding>(m_dataRoot, "longlong_v"));
	BindingMaster::addBinding(obj, obj->prop("ulonglong_p"), createRef<Binding>(m_dataRoot, "ulonglong_v"));
	BindingMaster::addBinding(obj, obj->prop("float_p"), createRef<Binding>(m_dataRoot, "float_v"));
	BindingMaster::addBinding(obj, obj->prop("double_p"), createRef<Binding>(m_dataRoot, "double_v"));
	BindingMaster::addBinding(obj, obj->prop("longdouble_p"), createRef<Binding>(m_dataRoot, "longdouble_v"));
	BindingMaster::addBinding(obj, obj->prop("string_p"), createRef<Binding>(m_dataRoot, "string_v"));
	BindingMaster::addBinding(obj, obj->prop("wstring_p"), createRef<Binding>(m_dataRoot, "wstring_v"));
	BindingMaster::addBinding(obj, obj->prop("enum_p"), createRef<Binding>(m_dataRoot, "enum_v"));
	BindingMaster::addBinding(obj, obj->prop("point_p"), createRef<Binding>(m_dataRoot, "point_v"));
	BindingMaster::addBinding(obj, obj->prop("colorptr_p"), createRef<Binding>(m_dataRoot, "colorptr_v"));
	BindingMaster::addBinding(obj, obj->prop("string_p1"), createRef<Binding>(m_dataRoot, "obj.x"));
	
	auto bd = createRef<Binding>(m_dataRoot, "int32_v");
	BindingMaster::addBinding(obj, obj->prop("int32_p1"), bd);
	BindingMaster::addBinding(obj, obj->prop("int32_p2"), bd);

	//check obj's values after binding
	{
		CHECK(obj->bool_p == true);
		CHECK(obj->char_p == 'a');
		CHECK(obj->schar_p == 'b');
		CHECK(obj->uchar_p == 'c');
		CHECK(obj->wchar_p == 1);
		CHECK(obj->char16_p == 2);
		CHECK(obj->char32_p == 3);
		CHECK(obj->short_p == 4);
		CHECK(obj->ushort_p == 5);
		CHECK(obj->int32_p == 6);
		CHECK(obj->uint32_p == 7);
		CHECK(obj->long_p == 8);
		CHECK(obj->ulong_p == 9);
		CHECK(obj->longlong_p == 10);
		CHECK(obj->ulonglong_p == 11);
		CHECK(nb::epsilonEqual(obj->float_p, 1.0f));
		CHECK(nb::epsilonEqual(obj->double_p, 2.0));
		CHECK(nb::epsilonEqual(obj->longdouble_p, 3.0));
		CHECK(obj->string_p == "abcdefg");
		CHECK(obj->wstring_p == L"hijklmn");
		CHECK(obj->enum_p == Enum::v1);
		CHECK(obj->point_p == 2.0f);
		CHECK(*(obj->colorptr_p) == Colors::red);
		CHECK(obj->int32_p1 == 6);
		CHECK(obj->int32_p2 == 6);
		CHECK(obj->string_p1 == "100");
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

	//check obj's values after set data
	{
		CHECK(obj->bool_p == false);
		CHECK(obj->char_p == 'x');
		CHECK(obj->schar_p == 'y');
		CHECK(obj->uchar_p == 'z');
		CHECK(obj->wchar_p == 11);
		CHECK(obj->char16_p == 22);
		CHECK(obj->char32_p == 33);
		CHECK(obj->short_p == 44);
		CHECK(obj->ushort_p == 55);
		CHECK(obj->int32_p == 66);
		CHECK(obj->uint32_p == 77);
		CHECK(obj->long_p == 88);
		CHECK(obj->ulong_p == 99);
		CHECK(obj->longlong_p == 111);
		CHECK(obj->ulonglong_p == 222);
		CHECK(nb::epsilonEqual(obj->float_p, 5.55f));
		CHECK(nb::epsilonEqual(obj->double_p, 6.66));
		CHECK(nb::epsilonEqual(obj->longdouble_p, 7.77));
		CHECK(obj->string_p == "desay");
		CHECK(obj->wstring_p == L"sv");
		CHECK(obj->enum_p == Enum::v2);
		CHECK(obj->point_p == 9.0f);
		CHECK(*(obj->colorptr_p) == Colors::blue);
		CHECK(obj->int32_p1 == 66);
		CHECK(obj->int32_p2 == 66);
		CHECK(obj->string_p1 == "123.01");
	}


}
