#include "TestThicknese.h"
#include "gui/Thickness.h"

using namespace nb::gui;
void TestThicknese::test()
{
	Thickness tk(10);
	Thickness tk1(-1, 2, 5, 5);

	Thickness tk2(tk1);
	
	bool b = tk.equals(tk2);
	tk2 = tk;
	bool b1 = tk2 == tk;

	bool b2 = tk2 != tk1;

	tk.left() += 1;
	tk.top() += 2;
	tk.right() += 3;
	tk.bottom() += 4;

	tk = tk - 5;
	tk = tk + 1;
	tk -= 4;
	tk += 9;

	tk.reset(0, 0, 0, 0);

}