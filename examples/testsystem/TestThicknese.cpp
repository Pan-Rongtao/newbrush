#include "TestThicknese.h"
#include "gui/Thickness.h"

using namespace nb::Gui;
TestThicknese::TestThicknese(void)
{
}

TestThicknese::~TestThicknese(void)
{
}

void TestThicknese::Test()
{
	Thickness tk(10);
	Thickness tk1(-1, 2, 5, 5);

	Thickness tk2(tk1);
	
	bool b = tk.Equals(tk2);
	tk2 = tk;
	bool b1 = tk2 == tk;

	bool b2 = tk2 != tk1;

	tk.Left() += 1;
	tk.Top() += 2;
	tk.Right() += 3;
	tk.Bottom() += 4;

	tk = tk - 5;
	tk = tk + 1;
	tk -= 4;
	tk += 9;

	tk.Reset(0, 0, 0, 0);

}