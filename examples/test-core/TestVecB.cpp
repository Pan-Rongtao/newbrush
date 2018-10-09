#include "TestVecB.h"
#include "core/Vec2.h"
#include "core/Vec3.h"
#include "core/Vec4.h"

using namespace nb::core;

void TestVecB::Test()
{
	Vec2B vc2_0;
	Vec2B vc2_1(1, true);
	Vec2B vc2_2(vc2_1);
	Vec2B vc2_3 = vc2_2;

	float norm1 = vc2_3.lenght();
	vc2_3.x() = false;
	vc2_3.y() = true;

	bool x = vc2_3.x();
	bool y = vc2_3.y();


	///////////
	Vec3B vc3_0(true, true, false);
	bool x1 = vc3_0.x();
	bool y1 = vc3_0.y();
	bool z1 = vc3_0.z();
	Vec3B vc3_1(Vec2B(false, false), true);
	bool x2 = vc3_1.x();
	bool y2 = vc3_1.y();
	bool z2 = vc3_1.z();
	Vec3B vc3_2(true, Vec2B(false, true));
	bool x3 = vc3_2.x();
	bool y3 = vc3_2.y();
	bool z3 = vc3_2.z();
	Vec2B xy = vc3_2.xy();
	Vec2B yz = vc3_2.yz();

	/////////////
	Vec4B vc4_0(false, true, false, true);
	bool x4 = vc4_0.x();
	bool y4 = vc4_0.y();
	bool z4 = vc4_0.z();
	bool w4 = vc4_0.w();
	Vec4B vc4_1(Vec3B(-1, 3, 2), 9);
	bool x5 = vc4_1.x();
	bool y5 = vc4_1.y();
	bool z5 = vc4_1.z();
	bool w5 = vc4_1.w();
	Vec4B vc4_2(-8, Vec3B(-1, 3, 2));
	bool x6 = vc4_2.x();
	bool y6 = vc4_2.y();
	bool z6 = vc4_2.z();
	bool w6 = vc4_2.w();
	Vec4B vc4_3(Vec2B(-8, 0), Vec2B(3, 2));
	bool x7 = vc4_3.x();
	bool y7 = vc4_3.y();
	bool z7 = vc4_3.z();
	bool w7 = vc4_3.w();
	Vec4B vc4_4(11, Vec2B(-8, 0), 5);
	bool x8 = vc4_4.x();
	bool y8 = vc4_4.y();
	bool z8 = vc4_4.z();
	bool w8 = vc4_4.w();
	Vec4B vc4_5(7, 7, Vec2B(3, 2));
	bool x9 = vc4_5.x();
	bool y9 = vc4_5.y();
	bool z9 = vc4_5.z();
	bool w9 = vc4_5.w();

	Vec2B xy1 = vc4_5.xy();
	Vec2B yz1 = vc4_5.yz();
	Vec2B zw1 = vc4_5.zw();
	Vec3B xyz = vc4_5.xyz();
	Vec3B yzw = vc4_5.yzw();

}