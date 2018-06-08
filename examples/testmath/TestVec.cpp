#include "TestVec.h"
#include "math/Vec.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

using nb::Math::Vec;
using nb::Math::Vec2;
using nb::Math::Vec3;
using nb::Math::Vec4;

void TestVec::Test()
{
	Vec vc_0(3);
	vc_0[0] = 1.0;
	vc_0[1] = 2.0;
	vc_0[2] = 3.0;
	for(int i = 0; i != vc_0.GetDimension(); ++i)
	{
		float f = vc_0.At(i);
		float ff = vc_0[i];
		bool b = false;
	}
	Vec vc_1(3);
	vc_1[0] = 1.0;
	vc_1[1] = 2.0;
	vc_1[2] = 2.0;

	Vec vc_2(vc_1);

	Vec vc_3 = vc_0;

	vc_2 = vc_3 = Vec(3);

	bool b = vc_0 == vc_1;
	bool b1 = vc_2 == vc_1;
	bool b2 = vc_3 != vc_0;

	int dimension = Vec(9).GetDimension();
	
	Vec vec_4(4);
	vec_4.At(0) = 2;
	vec_4.At(1) = 5;
	vec_4.At(2) = 3;
	vec_4.At(3) = 6;

	float norm = vec_4.Norm();
	////////////////////////
	Vec2 vc2_0;
	Vec2 vc2_1(1, 2);
	Vec2 vc2_2(vc2_1);
	Vec2 vc2_3 = vc2_2;

	int norm1 = vc2_3.GetDimension();
	vc2_3.X() = 1.2f;
	vc2_3.Y() = 3.4f;

	float x = vc2_3.X();
	float y = vc2_3.Y();


	///////////
	Vec3 vc3_0(1.1f, 2.2f, 3.3f);
	float x1 = vc3_0.X();
	float y1 = vc3_0.Y();
	float z1 = vc3_0.Z();
	Vec3 vc3_1(Vec2(4.1f, 5.2f), 3.3f);
	float x2 = vc3_1.X();
	float y2 = vc3_1.Y();
	float z2 = vc3_1.Z();
	Vec3 vc3_2(9.1f, Vec2(4.1f, 5.2f));
	float x3 = vc3_2.X();
	float y3 = vc3_2.Y();
	float z3 = vc3_2.Z();
	Vec2 xy = vc3_2.XY();
	Vec2 yz = vc3_2.YZ();

	/////////////
	Vec4 vc4_0(3.3f, 4.4f, 5.5f, 6.6f);
	float x4 = vc4_0.X();
	float y4 = vc4_0.Y();
	float z4 = vc4_0.Z();
	float w4 = vc4_0.W();
	Vec4 vc4_1(Vec3(-1, 3, 2), 9);
	float x5 = vc4_1.X();
	float y5 = vc4_1.Y();
	float z5 = vc4_1.Z();
	float w5 = vc4_1.W();
	Vec4 vc4_2(-8, Vec3(-1, 3, 2));
	float x6 = vc4_2.X();
	float y6 = vc4_2.Y();
	float z6 = vc4_2.Z();
	float w6 = vc4_2.W();
	Vec4 vc4_3(Vec2(-8, 0), Vec2(3, 2));
	float x7 = vc4_3.X();
	float y7 = vc4_3.Y();
	float z7 = vc4_3.Z();
	float w7 = vc4_3.W();
	Vec4 vc4_4(11, Vec2(-8, 0), 5);
	float x8 = vc4_4.X();
	float y8 = vc4_4.Y();
	float z8 = vc4_4.Z();
	float w8 = vc4_4.W();
	Vec4 vc4_5(7, 7, Vec2(3, 2));
	float x9 = vc4_5.X();
	float y9 = vc4_5.Y();
	float z9 = vc4_5.Z();
	float w9 = vc4_5.W();

	Vec2 xy1 = vc4_5.XY();
	Vec2 yz1 = vc4_5.YZ();
	Vec2 zw1 = vc4_5.ZW();
	Vec3 xyz = vc4_5.XYZ();
	Vec3 yzw = vc4_5.YZW();

}