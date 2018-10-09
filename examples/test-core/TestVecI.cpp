#include "TestVecI.h"
#include "core/Vec2.h"
#include "core/Vec3.h"
#include "core/Vec4.h"

using namespace nb::core;

void TestVecI::Test()
{
	Vec2I vc2_0;
	Vec2I vc2_1(1, 6);
	Vec2I vc2_2(vc2_1);
	Vec2I vc2_3 = vc2_2;

	float norm1 = vc2_3.lenght();
	vc2_3.x() = 4;
	vc2_3.y() = 2;
	vc2_3[0] = 9;
	vc2_3[1] = 5;

	int x = vc2_3.x();
	int y = vc2_3.y();


	///////////
	Vec3I vc3_0(3, -9, 2);
	int x1 = vc3_0.x();
	int y1 = vc3_0.y();
	int z1 = vc3_0.z();
	Vec3I vc3_1(Vec2I(11, 2), -2);
	int x2 = vc3_1.x();
	int y2 = vc3_1.y();
	int z2 = vc3_1.z();
	Vec3I vc3_2(-5, Vec2I(2, 4));
	int x3 = vc3_2.x();
	int y3 = vc3_2.y();
	int z3 = vc3_2.z();
	Vec2I xy = vc3_2.xy();
	Vec2I yz = vc3_2.yz();

	/////////////
	Vec4I vc4_0(4, 1, 1, 2);
	int x4 = vc4_0.x();
	int y4 = vc4_0.y();
	int z4 = vc4_0.z();
	int w4 = vc4_0.w();
	Vec4I vc4_1(Vec3I(-1, 3, 2), 9);
	int x5 = vc4_1.x();
	int y5 = vc4_1.y();
	int z5 = vc4_1.z();
	int w5 = vc4_1.w();
	Vec4I vc4_2(-8, Vec3I(-1, 3, 2));
	int x6 = vc4_2.x();
	int y6 = vc4_2.y();
	int z6 = vc4_2.z();
	int w6 = vc4_2.w();
	Vec4I vc4_3(Vec2I(-8, 0), Vec2I(3, 2));
	int x7 = vc4_3.x();
	int y7 = vc4_3.y();
	int z7 = vc4_3.z();
	int w7 = vc4_3.w();
	Vec4I vc4_4(11, Vec2I(-8, 0), 5);
	int x8 = vc4_4.x();
	int y8 = vc4_4.y();
	int z8 = vc4_4.z();
	int w8 = vc4_4.w();
	Vec4I vc4_5(7, 7, Vec2I(3, 2));
	int x9 = vc4_5.x();
	int y9 = vc4_5.y();
	int z9 = vc4_5.z();
	int w9 = vc4_5.w();

	Vec2I xy1 = vc4_5.xy();
	Vec2I yz1 = vc4_5.yz();
	Vec2I zw1 = vc4_5.zw();
	Vec3I xyz = vc4_5.xyz();
	Vec3I yzw = vc4_5.yzw();

}