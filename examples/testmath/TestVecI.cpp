#include "TestVecI.h"
#include "math/VecI.h"
#include "math/Vec2I.h"
#include "math/Vec3I.h"
#include "math/Vec4I.h"

using nb::Math::VecI;
using nb::Math::Vec2I;
using nb::Math::Vec3I;
using nb::Math::Vec4I;

void TestVecI::Test()
{
	VecI vc_0(3);
	vc_0[0] = 3;
	vc_0[1] = -1;
	vc_0[2] = 7;
	for(int i = 0; i != vc_0.GetDimension(); ++i)
	{
		int f = vc_0.At(i);
		int ff = vc_0[i];
		bool b = false;
	}
	VecI vc_1(3);
	vc_1[0] = 3;
	vc_1[1] = -1;
	vc_1[2] = 7;

	VecI vc_2(vc_1);

	VecI vc_3 = vc_0;

	vc_2 = vc_3 = VecI(3);

	bool b = vc_0 == vc_1;
	bool b1 = vc_2 == vc_1;
	bool b2 = vc_3 != vc_0;

	int dimension = VecI(9).GetDimension();
	
	VecI vec_4(4);
	vec_4.At(0) = -2;
	vec_4.At(1) = -4;
	vec_4.At(2) = 3;
	vec_4.At(3) = 1.2;

	float norm = vec_4.Norm();
	////////////////////////
	Vec2I vc2_0;
	Vec2I vc2_1(1, 6);
	Vec2I vc2_2(vc2_1);
	Vec2I vc2_3 = vc2_2;

	float norm1 = vc2_3.Lenght();
	vc2_3.X() = 4;
	vc2_3.Y() = 2;
	vc2_3[0] = 9;
	vc2_3[1] = 5;

	int x = vc2_3.X();
	int y = vc2_3.Y();


	///////////
	Vec3I vc3_0(3, -9, 2);
	int x1 = vc3_0.X();
	int y1 = vc3_0.Y();
	int z1 = vc3_0.Z();
	Vec3I vc3_1(Vec2I(11, 2), -2);
	int x2 = vc3_1.X();
	int y2 = vc3_1.Y();
	int z2 = vc3_1.Z();
	Vec3I vc3_2(-5, Vec2I(2, 4));
	int x3 = vc3_2.X();
	int y3 = vc3_2.Y();
	int z3 = vc3_2.Z();
	Vec2I xy = vc3_2.XY();
	Vec2I yz = vc3_2.YZ();

	/////////////
	Vec4I vc4_0(4, 1, 1, 2);
	int x4 = vc4_0.X();
	int y4 = vc4_0.Y();
	int z4 = vc4_0.Z();
	int w4 = vc4_0.W();
	Vec4I vc4_1(Vec3I(-1, 3, 2), 9);
	int x5 = vc4_1.X();
	int y5 = vc4_1.Y();
	int z5 = vc4_1.Z();
	int w5 = vc4_1.W();
	Vec4I vc4_2(-8, Vec3I(-1, 3, 2));
	int x6 = vc4_2.X();
	int y6 = vc4_2.Y();
	int z6 = vc4_2.Z();
	int w6 = vc4_2.W();
	Vec4I vc4_3(Vec2I(-8, 0), Vec2I(3, 2));
	int x7 = vc4_3.X();
	int y7 = vc4_3.Y();
	int z7 = vc4_3.Z();
	int w7 = vc4_3.W();
	Vec4I vc4_4(11, Vec2I(-8, 0), 5);
	int x8 = vc4_4.X();
	int y8 = vc4_4.Y();
	int z8 = vc4_4.Z();
	int w8 = vc4_4.W();
	Vec4I vc4_5(7, 7, Vec2I(3, 2));
	int x9 = vc4_5.X();
	int y9 = vc4_5.Y();
	int z9 = vc4_5.Z();
	int w9 = vc4_5.W();

	Vec2I xy1 = vc4_5.XY();
	Vec2I yz1 = vc4_5.YZ();
	Vec2I zw1 = vc4_5.ZW();
	Vec3I xyz = vc4_5.XYZ();
	Vec3I yzw = vc4_5.YZW();

}