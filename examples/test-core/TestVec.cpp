#include "TestVec.h"
#include "core/Vec2.h"
#include "core/Vec3.h"
#include "core/Vec4.h"

using namespace nb::core;

void TestVec::Test()
{
	////////////////////////
	Vec2 vc2_0;
	Vec2 vc2_1(1, 2);
	Vec2 vc2_2(vc2_1);
	Vec2 vc2_3 = vc2_2;

	int norm1 = vc2_3.dimension();
	vc2_3.x() = 1.2f;
	vc2_3.y() = 3.4f;

	float x = vc2_3.x();
	float y = vc2_3.y();


	///////////
	Vec3 vc3_0(1.1f, 2.2f, 3.3f);
	float x1 = vc3_0.x();
	float y1 = vc3_0.y();
	float z1 = vc3_0.z();
	Vec3 vc3_1(Vec2(4.1f, 5.2f), 3.3f);
	float x2 = vc3_1.x();
	float y2 = vc3_1.y();
	float z2 = vc3_1.z();
	Vec3 vc3_2(9.1f, Vec2(4.1f, 5.2f));
	float x3 = vc3_2.x();
	float y3 = vc3_2.y();
	float z3 = vc3_2.z();
	Vec2 xy = vc3_2.xy();
	Vec2 yz = vc3_2.yz();

	/////////////
	Vec4 vc4_0(3.3f, 4.4f, 5.5f, 6.6f);
	float x4 = vc4_0.x();
	float y4 = vc4_0.y();
	float z4 = vc4_0.z();
	float w4 = vc4_0.w();
	Vec4 vc4_1(Vec3(-1, 3, 2), 9);
	float x5 = vc4_1.x();
	float y5 = vc4_1.y();
	float z5 = vc4_1.z();
	float w5 = vc4_1.w();
	Vec4 vc4_2(-8, Vec3(-1, 3, 2));
	float x6 = vc4_2.x();
	float y6 = vc4_2.y();
	float z6 = vc4_2.z();
	float w6 = vc4_2.w();
	Vec4 vc4_3(Vec2(-8, 0), Vec2(3, 2));
	float x7 = vc4_3.x();
	float y7 = vc4_3.y();
	float z7 = vc4_3.z();
	float w7 = vc4_3.w();
	Vec4 vc4_4(11, Vec2(-8, 0), 5);
	float x8 = vc4_4.x();
	float y8 = vc4_4.y();
	float z8 = vc4_4.z();
	float w8 = vc4_4.w();
	Vec4 vc4_5(7, 7, Vec2(3, 2));
	float x9 = vc4_5.x();
	float y9 = vc4_5.y();
	float z9 = vc4_5.z();
	float w9 = vc4_5.w();

	Vec2 xy1 = vc4_5.xy();
	Vec2 yz1 = vc4_5.yz();
	Vec2 zw1 = vc4_5.zw();
	Vec3 xyz = vc4_5.xyz();
	Vec3 yzw = vc4_5.yzw();

}