#include "newbrush/core/media/Bitmap.h"
#include <stdio.h>
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("nb::Bitmap", "[Bitmap]")
{
	Bitmap bmttt;
	bmttt.load("e:/Pics/4.jpg");

	Bitmap bm48;
	bm48.load("f:/15.png");
	bm48.save("f:/xxxxxx.png");

	Bitmap bm1("f:/pics/2.jpg");
	int w = bm1.width();
	int h = bm1.height();
	int bpp = bm1.channels();
	int bytes1 = bm1.bytes();

	Bitmap bm2("f:/download/resizeApi.png");
	int w2 = bm2.width();
	int h2 = bm2.height();
	int bpp2 = bm2.channels();
	int bytes2 = bm2.bytes();
	
	Bitmap bm4;
	FILE *pFile = nullptr;
	fopen_s(&pFile, "../images/zelda0.jpg", "rb");
	fseek(pFile, 0, SEEK_END);
	int nLength = ftell(pFile);
	unsigned char *pData = new unsigned char[nLength];
	fseek(pFile, 0, SEEK_SET);
	fread(pData, nLength, 1, pFile);
	bm4.load(pData, nLength);
	bm4.save("../images/zelda_sv.jpg");
	delete[]pData;
	fclose(pFile);

//	bm4.scale(200, bm4.height());
//	bm4.save("f:/scalew200.bmp");
	
	Bitmap bm33("f:/flower.png");
	int w33 = bm33.width();
	int w34 = bm33.height();
	int bpp33 = bm33.channels();
	int s33 = bm33.bytes();
	bm33.save("f:/bpp64.png");

	Bitmap bm36("f:/pics/copy_pic.jpg");
	int w36 = bm36.width();
	int h36 = bm36.height();
	int bpp36 = bm36.channels();
	int s36 = bm36.bytes();
	bm36.save("f:/xxxxtest.png");

	Bitmap bm37("f:/32bits.bmp");
	int bpp37 = bm37.channels();
	int s37 = bm37.bytes();

}