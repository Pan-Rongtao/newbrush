#include "TestVecB.h"
#include "math/VecB.h"
#include "math/Vec2B.h"
#include "math/Vec3B.h"
#include "math/Vec4B.h"

using nb::Math::VecB;
using nb::Math::Vec2B;
using nb::Math::Vec3B;
using nb::Math::Vec4B;

void TestVecB::Test()
{
	VecB vc_0(3);
	vc_0[0] = false;
	vc_0[1] = true;
	vc_0[2] = false;
	for(int i = 0; i != vc_0.GetDimension(); ++i)
	{
		bool f = vc_0.At(i);
		bool ff = vc_0[i];
		bool b = false;
	}
	VecB vc_1(3);
	vc_1[0] = false;
	vc_1[1] = false;
	vc_1[2] = false;

	VecB vc_2(vc_1);

	VecB vc_3 = vc_0;

	vc_2 = vc_3 = VecB(3);

	bool b = vc_0 == vc_1;
	bool b1 = vc_2 == vc_1;
	bool b2 = vc_3 != vc_0;

	int dimension = VecB(9).GetDimension();
	
	VecB vec_4(4);
	vec_4.At(0) = false;
	vec_4.At(1) = false;
	vec_4.At(2) = true;
	vec_4.At(3) = false;

	float norm = vec_4.Norm();
	////////////////////////
	Vec2B vc2_0;
	Vec2B vc2_1(1, true);
	Vec2B vc2_2(vc2_1);
	Vec2B vc2_3 = vc2_2;

	float norm1 = vc2_3.Lenght();
	vc2_3.X() = false;
	vc2_3.Y() = true;

	bool x = vc2_3.X();
	bool y = vc2_3.Y();


	///////////
	Vec3B vc3_0(true, true, false);
	bool x1 = vc3_0.X();
	bool y1 = vc3_0.Y();
	bool z1 = vc3_0.Z();
	Vec3B vc3_1(Vec2B(false, false), true);
	bool x2 = vc3_1.X();
	bool y2 = vc3_1.Y();
	bool z2 = vc3_1.Z();
	Vec3B vc3_2(true, Vec2B(false, true));
	bool x3 = vc3_2.X();
	bool y3 = vc3_2.Y();
	bool z3 = vc3_2.Z();
	Vec2B xy = vc3_2.XY();
	Vec2B yz = vc3_2.YZ();

	/////////////
	Vec4B vc4_0(false, true, false, true);
	bool x4 = vc4_0.X();
	bool y4 = vc4_0.Y();
	bool z4 = vc4_0.Z();
	bool w4 = vc4_0.W();
	Vec4B vc4_1(Vec3B(-1, 3, 2), 9);
	bool x5 = vc4_1.X();
	bool y5 = vc4_1.Y();
	bool z5 = vc4_1.Z();
	bool w5 = vc4_1.W();
	Vec4B vc4_2(-8, Vec3B(-1, 3, 2));
	bool x6 = vc4_2.X();
	bool y6 = vc4_2.Y();
	bool z6 = vc4_2.Z();
	bool w6 = vc4_2.W();
	Vec4B vc4_3(Vec2B(-8, 0), Vec2B(3, 2));
	bool x7 = vc4_3.X();
	bool y7 = vc4_3.Y();
	bool z7 = vc4_3.Z();
	bool w7 = vc4_3.W();
	Vec4B vc4_4(11, Vec2B(-8, 0), 5);
	bool x8 = vc4_4.X();
	bool y8 = vc4_4.Y();
	bool z8 = vc4_4.Z();
	bool w8 = vc4_4.W();
	Vec4B vc4_5(7, 7, Vec2B(3, 2));
	bool x9 = vc4_5.X();
	bool y9 = vc4_5.Y();
	bool z9 = vc4_5.Z();
	bool w9 = vc4_5.W();

	Vec2B xy1 = vc4_5.XY();
	Vec2B yz1 = vc4_5.YZ();
	Vec2B zw1 = vc4_5.ZW();
	Vec3B xyz = vc4_5.XYZ();
	Vec3B yzw = vc4_5.YZW();

}