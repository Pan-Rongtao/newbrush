#pragma once
#include "../TestBase.h"
#include "core/DependencyObject.h"
#include "core/DependencyProperty.h"

using namespace nb;

class TestDependencyProperty : public TestBase, public DependencyObject
{
public:
	void test();

	static DependencyProperty BoolPoperty();
	static DependencyProperty IntProperty();
	static DependencyProperty FloatProperty();
	static DependencyProperty DoubleProperty();
	static DependencyProperty StringProperty();
	static DependencyProperty WStringProperty();
	static DependencyProperty PointProperty();
	static DependencyProperty SharedPtrProperty();

};