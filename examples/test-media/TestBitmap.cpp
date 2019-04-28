#include "TestBitmap.h"
#include "media/Bitmap.h"
#include "core/File.h"
#include "core/Size.h"
#include <stdio.h>

using namespace nb::core;
using namespace nb::media;

TestBitmap::TestBitmap(void)
{
}

TestBitmap::~TestBitmap(void)
{
}

void TestBitmap::Test()
{
	Bitmap bmttt;
	bmttt.load("e:/Pics/4.jpg");

	Bitmap bm48;
	bm48.load("f:/15.png", 1);
	bm48.save("f:/xxxxxx.png");

	Bitmap bm(200, 200);
	bm.fill(Colors::green());
	int bytes = bm.bytes();
	bool b1 = bm.hasPixelData();

	Bitmap bm1("f:/pics/2.jpg");
	int w = bm1.width();
	int h = bm1.height();
	int bpp = bm1.bpp();
	int bytes1 = bm1.bytes();

	Bitmap bm2("f:/download/resizeApi.png");
	int w2 = bm2.width();
	int h2 = bm2.height();
	int bpp2 = bm2.bpp();
	int bytes2 = bm2.bytes();

	Bitmap bm3;
	bool b3 = bm3.hasPixelData();

//	bm.save("d:/1.bmp");

	Bitmap bm4;

	FILE *pFile = fopen("f:/pics/copy_pic.jpg", "rb");
	fseek(pFile, 0, SEEK_END);
	int nLength = ftell(pFile);
	char *pData = new char[nLength];
	fseek(pFile, 0, SEEK_SET);
	fread(pData, nLength, 1, pFile);
	bm4.load(pData, nLength);
	bm4.save("f:/1.png");
	delete[]pData;
	fclose(pFile);

	File f("f:/download/22.bmp");
	f.Open(File::OpenExistsOnly, File::Read);
	Stream stream = f.ReadAll();
	auto len = f.GetLenght();
	bm4.load((const char *)stream.GetData(), (int)len);


	Bitmap bm5(bm4.data(), bm4.width(), bm4.height(), bm4.pixelFormat());
	int w5 = bm5.width();
	int h5 = bm5.height();
	int s5 = bm5.bytes();
	bm5.save("d:/xx.bmp");

	Bitmap bm6(bm1.data(), bm1.width(), bm1.height(), bm1.pixelFormat());
	int w6 = bm6.width();
	int h6 = bm6.height();
	int s6 = bm6.bytes();

	Bitmap bm7(bm2.data(), bm2.width(), bm2.height(), bm2.pixelFormat());
	int w7 = bm7.width();
	int h7 = bm7.height();
	int s7 = bm7.bytes();

	bm7.save("e:/1.png");
	Bitmap bm8(100, 100, Bitmap::Format_Bpp16_Rgb555);
	int w8 = bm8.width();
	int h8 = bm8.height();
	int bpp8 = bm8.bpp();
	int s8 = bm8.bytes();

	Bitmap bm9(200, 200, Bitmap::Format_Bpp16_Rgb565);
	int w9 = bm9.width();
	int h9 = bm9.height();
	int bpp9 = bm9.bpp();
	int s9 = bm9.bytes();

	Bitmap bm10(300, 300, Bitmap::Format_Bpp24_Rgb888);
	int w10 = bm10.width();
	int h10 = bm10.height();
	int bpp10 = bm10.bpp();
	int s10 = bm10.bytes();


	Bitmap bm11(400, 400, Bitmap::Format_Bpp32_Rgba8888);
	int w11 = bm11.width();
	int h11 = bm11.height();
	int bpp11 = bm11.bpp();
	int s11 = bm11.bytes();

	Bitmap bm12(bm2);
	int w12 = bm12.width();
	int h12 = bm12.height();
	int bpp12 = bm12.bpp();
	int s12 = bm12.bytes();

	Bitmap bm13 = bm4;
	int s13 = bm13.bytes();
	Bitmap::PixelFormat format13 = bm13.pixelFormat();

	Bitmap bm14("f:/download/1bits.bmp");
	int bpp14 = bm14.bpp();
	Bitmap::PixelFormat format14 = bm14.pixelFormat();

	Bitmap bm15("f:/download/4bits.bmp");
	int bpp15 = bm15.bpp();
	Bitmap::PixelFormat format15 = bm15.pixelFormat();

	Bitmap bm16("f:/download/8bits.bmp");
	int w16 = bm16.width();
	int h16 = bm16.height();
	int bpp16 = bm16.bpp();
	int s16 = bm16.bytes();
	Bitmap::PixelFormat format16 = bm16.pixelFormat();

	Bitmap bm17 = bm16.scale(100, 100);
	int w17 = bm17.width();
	int h17 = bm17.height();
	int bpp17 = bm17.bpp();
	int s17 = bm17.bytes();
	bm17.save("d:/11.bmp");

	Bitmap bm18 = bm4.scale(200, bm4.height());
	bm18.save("f:/scalew200.bmp");

	Bitmap bm19 = bm4.scale(bm4.width(), 300);
	bm19.save("f:/scaleh300.bmp");

	Bitmap bm20 = bm4.copy(100, 100, 200, 200);
	bm20.save("f:/cpy200x200.bmp");

	Bitmap bm21 = bm4.copy(200, 200, -100, -100);
	bm21.save("f:/cpy-100x100.bmp");

	Bitmap bm22 = bm2.gray();
	int w22 = bm22.width();
	int h22 = bm22.height();
	int bpp22 = bm22.bpp();
	int s22 = bm22.bytes();
	bm22.save("f:/gray.bmp");

	Bitmap bm23 = bm2.convert(Bitmap::Format_Bpp8_Palette);
	bm23.save("f:/convertpalette8.bmp");

	Bitmap bm24 = bm2.convert(Bitmap::Format_Bpp16_Rgb555);
	bm24.save("f:/convert555.png");

	Bitmap bm25 = bm2.convert(Bitmap::Format_Bpp16_Rgb565);
	bm25.save("f:/convert565.png");

	Bitmap bm26 = bm2.convert(Bitmap::Format_Bpp24_Rgb888);
	bm26.save("f:/convert888.png");

	Bitmap bm27 = bm2.convert(Bitmap::Format_Bpp32_Rgba8888);
	bm27.save("f:/convert8888.png");

	Bitmap bm28 = bm2.convert(Bitmap::Format_Bpp4_Palette);
	bm28.save("f:/convertpalette4.png");

	Bitmap bm29 = bm2.convert(Bitmap::Format_Bpp1_Palette);
	bm29.save("f:/convertpalette1.bmp");

	Bitmap bm33("f:/flower.png");
	int w33 = bm33.width();
	int w34 = bm33.height();
	int bpp33 = bm33.bpp();
	int s33 = bm33.bytes();
	bm33.save("f:/bpp64.png");
/*
	Bitmap bm35("f:/pics/111.jpg");
	bm35 = bm35.scale(1440, 900);
	int w35 = bm35.width();
	int h35 = bm35.height();
	bm35.save("f:/fakescale.jpg");
*/
	Bitmap bm36("f:/pics/copy_pic.jpg");
	int w36 = bm36.width();
	int h36 = bm36.height();
	int bpp36 = bm36.bpp();
	int s36 = bm36.bytes();
	bm36.save("f:/xxxxtest.png");


	Bitmap bm37("f:/32bits.bmp");
	int bpp37 = bm37.bpp();
	int s37 = bm37.bytes();


	uint64_t k = NB_GET_TICK_COUT;
	Bitmap bm41("f:/4.jpg");
	bm41.scale(160, 160);
//	printf("cost [%d]\r\n", NB_GET_TICK_COUT - k);

	uint64_t kkk = NB_GET_TICK_COUT;
	k = NB_GET_TICK_COUT;
	Bitmap bm43;
	//bm43.LoadFile("f:/21.jpg");
	bm43.load("f:/21.jpg", 8);
	printf("load cost [%lld]\r\n", NB_GET_TICK_COUT - k);
//	bm43.save("f:/21_s.jpg");
	k = NB_GET_TICK_COUT;
	bm43 = bm43.scale(160, 160);
	printf("scale cost [%lld]\r\n", NB_GET_TICK_COUT - k);
	printf("all cost [%lld]\r\n", NB_GET_TICK_COUT - kkk);
	bm43.save("f:/21_160.jpg");

	k = NB_GET_TICK_COUT;
	Bitmap bm44("f:/01.jpg");
	bm44.scale(160, 160);
//	printf("cost [%d]\r\n", NB_GET_TICK_COUT - k);

	Bitmap bm45("f:/pics/pic_8bit/0.jpg");
	int bpp45 = bm45.bpp();
	Bitmap::PixelFormat fm45 = bm45.pixelFormat();

	Bitmap bm46("f:/pic/0.jpg");
	bm46 = bm46.scale(160, 96);
	bm46.save("d:/111.jpg");


	Bitmap bm47("F:/Pics/Pic_8Bit/1.jpg");
	bm47 = bm47.scale(100, 100);
	bm47.save("f:/x.jpg");


/*
	for(int i = 0; i != 13; ++i)
	{
		char arr[10] = {0};
		sprintf(arr, "%d", i);
		std::string s = std::string("f:/error1/") + arr + ".jpg";
		Bitmap bm(s.data());
		SizeI sz = bm.size();
		int bpp = bm.bpp();
		std::string s_save = std::string("f:/error1/") + arr + "_xx.jpg";
		bm = bm.BgrToRgb();
		bm.save(s_save.data());
	}
	*/
}