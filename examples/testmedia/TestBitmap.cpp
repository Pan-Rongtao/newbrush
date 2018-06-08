#include "TestBitmap.h"
#include "media/Bitmap.h"
#include "system/Colors.h"
#include "system/File.h"
#include "system/SizeI.h"
#include "system/Platform.h"
#include <stdio.h>

using nb::Media::Bitmap;
using nb::System::Colors;
using nb::System::SizeI;
TestBitmap::TestBitmap(void)
{
}

TestBitmap::~TestBitmap(void)
{
}

void TestBitmap::Test()
{
	Bitmap bm48;
	bm48.LoadFileNarrowed("f:/15.png", 1);
	bm48.SaveAsFile("f:/xxxxxx.png");

	Bitmap bm(200, 200);
	bm.Fill(nb::System::Colors::Green());
	int bytes = bm.GetBytesCount();
	bool b1 = bm.HasPixelData();

	Bitmap bm1("f:/pics/2.jpg");
	int w = bm1.GetWidth();
	int h = bm1.GetHeight();
	int bpp = bm1.GetBpp();
	int bytes1 = bm1.GetBytesCount();

	Bitmap bm2("f:/download/resizeApi.png");
	int w2 = bm2.GetWidth();
	int h2 = bm2.GetHeight();
	int bpp2 = bm2.GetBpp();
	int bytes2 = bm2.GetBytesCount();

	Bitmap bm3;
	bool b3 = bm3.HasPixelData();

//	bm.SaveAsFile("d:/1.bmp");

	Bitmap bm4;

	FILE *pFile = fopen("f:/pics/copy_pic.jpg", "rb");
	fseek(pFile, 0, SEEK_END);
	int nLength = ftell(pFile);
	unsigned char *pData = new unsigned char[nLength];
	fseek(pFile, 0, SEEK_SET);
	fread(pData, nLength, 1, pFile);
	bm4.LoadData(pData, nLength);
	bm4.SaveAsFile("f:/1.png");

	nb::System::File f("f:/download/22.bmp");
	f.Open(nb::System::File::OpenExistsOnly, nb::System::File::Read);
	nb::System::Stream stream = f.ReadAll();
	int len = f.GetLenght();
	bm4.LoadData((const unsigned char *)stream.GetData(), len);


	Bitmap bm5(bm4.GetData(), bm4.GetSize(), bm4.GetPixelFormat());
	int w5 = bm5.GetWidth();
	int h5 = bm5.GetHeight();
	int s5 = bm5.GetBytesCount();
	bm5.SaveAsFile("d:/xx.bmp");

	Bitmap bm6(bm1.GetData(), bm1.GetSize(), bm1.GetPixelFormat());
	int w6 = bm6.GetWidth();
	int h6 = bm6.GetHeight();
	int s6 = bm6.GetBytesCount();

	Bitmap bm7(bm2.GetData(), bm2.GetSize(), bm2.GetPixelFormat());
	int w7 = bm7.GetWidth();
	int h7 = bm7.GetHeight();
	int s7 = bm7.GetBytesCount();

	bm7.SaveAsFile("e:/1.png");
	Bitmap bm8(100, 100, Bitmap::Format_Bpp16_Rgb555);
	int w8 = bm8.GetWidth();
	int h8 = bm8.GetHeight();
	int bpp8 = bm8.GetBpp();
	int s8 = bm8.GetBytesCount();

	Bitmap bm9(200, 200, Bitmap::Format_Bpp16_Rgb565);
	int w9 = bm9.GetWidth();
	int h9 = bm9.GetHeight();
	int bpp9 = bm9.GetBpp();
	int s9 = bm9.GetBytesCount();

	Bitmap bm10(300, 300, Bitmap::Format_Bpp24_Rgb888);
	int w10 = bm10.GetWidth();
	int h10 = bm10.GetHeight();
	int bpp10 = bm10.GetBpp();
	int s10 = bm10.GetBytesCount();


	Bitmap bm11(400, 400, Bitmap::Format_Bpp32_Rgba8888);
	int w11 = bm11.GetWidth();
	int h11 = bm11.GetHeight();
	int bpp11 = bm11.GetBpp();
	int s11 = bm11.GetBytesCount();

	Bitmap bm12(bm2);
	int w12 = bm12.GetWidth();
	int h12 = bm12.GetHeight();
	int bpp12 = bm12.GetBpp();
	int s12 = bm12.GetBytesCount();

	Bitmap bm13 = bm4;
	int s13 = bm13.GetBytesCount();
	Bitmap::PixelFormat format13 = bm13.GetPixelFormat();

	Bitmap bm14("f:/download/1bits.bmp");
	int bpp14 = bm14.GetBpp();
	Bitmap::PixelFormat format14 = bm14.GetPixelFormat();

	Bitmap bm15("f:/download/4bits.bmp");
	int bpp15 = bm15.GetBpp();
	Bitmap::PixelFormat format15 = bm15.GetPixelFormat();

	Bitmap bm16("f:/download/8bits.bmp");
	int w16 = bm16.GetWidth();
	int h16 = bm16.GetHeight();
	int bpp16 = bm16.GetBpp();
	int s16 = bm16.GetBytesCount();
	Bitmap::PixelFormat format16 = bm16.GetPixelFormat();

	Bitmap bm17 = bm16.Scale(100, 100);
	int w17 = bm17.GetWidth();
	int h17 = bm17.GetHeight();
	int bpp17 = bm17.GetBpp();
	int s17 = bm17.GetBytesCount();
	bm17.SaveAsFile("d:/11.bmp");

	Bitmap bm18 = bm4.ScaleWidth(200);
	bm18.SaveAsFile("f:/scalew200.bmp");

	Bitmap bm19 = bm4.ScaleHeight(300);
	bm19.SaveAsFile("f:/scaleh300.bmp");

	Bitmap bm20 = bm4.Copy(100, 100, 200, 200);
	bm20.SaveAsFile("f:/cpy200x200.bmp");

	Bitmap bm21 = bm4.Copy(nb::System::RectI(200, 200, -100, -100));
	bm21.SaveAsFile("f:/cpy-100x100.bmp");

	Bitmap bm22 = bm2.ToGray();
	int w22 = bm22.GetWidth();
	int h22 = bm22.GetHeight();
	int bpp22 = bm22.GetBpp();
	int s22 = bm22.GetBytesCount();
	bm22.SaveAsFile("f:/gray.bmp");

	Bitmap bm23 = bm2.ConverToFormat(Bitmap::Format_Bpp8_Palette);
	bm23.SaveAsFile("f:/convertpalette8.bmp");

	Bitmap bm24 = bm2.ConverToFormat(Bitmap::Format_Bpp16_Rgb555);
	bm24.SaveAsFile("f:/convert555.png");

	Bitmap bm25 = bm2.ConverToFormat(Bitmap::Format_Bpp16_Rgb565);
	bm25.SaveAsFile("f:/convert565.png");

	Bitmap bm26 = bm2.ConverToFormat(Bitmap::Format_Bpp24_Rgb888);
	bm26.SaveAsFile("f:/convert888.png");

	Bitmap bm27 = bm2.ConverToFormat(Bitmap::Format_Bpp32_Rgba8888);
	bm27.SaveAsFile("f:/convert8888.png");

	Bitmap bm28 = bm2.ConverToFormat(Bitmap::Format_Bpp4_Palette);
	bm28.SaveAsFile("f:/convertpalette4.png");

	Bitmap bm29 = bm2.ConverToFormat(Bitmap::Format_Bpp1_Palette);
	bm29.SaveAsFile("f:/convertpalette1.bmp");

	Bitmap bm33("f:/flower.png");
	int w33 = bm33.GetWidth();
	int w34 = bm33.GetHeight();
	int bpp33 = bm33.GetBpp();
	int s33 = bm33.GetBytesCount();
	bm33.SaveAsFile("f:/bpp64.png");
/*
	Bitmap bm35("f:/pics/111.jpg");
	bm35 = bm35.Scale(1440, 900);
	int w35 = bm35.GetWidth();
	int h35 = bm35.GetHeight();
	bm35.SaveAsFile("f:/fakescale.jpg");
*/
	Bitmap bm36("f:/pics/copy_pic.jpg");
	int w36 = bm36.GetWidth();
	int h36 = bm36.GetHeight();
	int bpp36 = bm36.GetBpp();
	int s36 = bm36.GetBytesCount();
	bm36.SaveAsFile("f:/xxxxtest.png");


	Bitmap bm37("f:/32bits.bmp");
	SizeI sz = bm37.GetSize();
	int bpp37 = bm37.GetBpp();
	int s37 = bm37.GetBytesCount();


	int k = nb::System::Platform::GetTickCount();
	Bitmap bm41("f:/4.jpg");
	bm41.Scale(160, 160);
//	printf("cost [%d]\r\n", nb::System::Platform::GetTickCount() - k);

	int kkk = nb::System::Platform::GetTickCount();
	k = nb::System::Platform::GetTickCount();
	Bitmap bm43;
	//bm43.LoadFile("f:/21.jpg");
	bm43.LoadFileNarrowed("f:/21.jpg", 8);
	printf("load cost [%d]\r\n", nb::System::Platform::GetTickCount() - k);
//	bm43.SaveAsFile("f:/21_s.jpg");
	k = nb::System::Platform::GetTickCount();
	bm43 = bm43.Scale(160, 160);
	printf("scale cost [%d]\r\n", nb::System::Platform::GetTickCount() - k);
	printf("all cost [%d]\r\n", nb::System::Platform::GetTickCount() - kkk);
	bm43.SaveAsFile("f:/21_160.jpg");

	k = nb::System::Platform::GetTickCount();
	Bitmap bm44("f:/01.jpg");
	bm44.Scale(160, 160);
//	printf("cost [%d]\r\n", nb::System::Platform::GetTickCount() - k);

	Bitmap bm45("f:/pics/pic_8bit/0.jpg");
	int bpp45 = bm45.GetBpp();
	Bitmap::PixelFormat fm45 = bm45.GetPixelFormat();

	Bitmap bm46("f:/pic/0.jpg");
	bm46 = bm46.Scale(160, 96);
	bm46.SaveAsFile("d:/111.jpg");


	Bitmap bm47("F:/Pics/Pic_8Bit/1.jpg");
	bm47 = bm47.Scale(100, 100);
	bm47.SaveAsFile("f:/x.jpg");


/*
	for(int i = 0; i != 13; ++i)
	{
		char arr[10] = {0};
		sprintf(arr, "%d", i);
		std::string s = std::string("f:/error1/") + arr + ".jpg";
		Bitmap bm(s.data());
		SizeI sz = bm.GetSize();
		int bpp = bm.GetBpp();
		std::string s_save = std::string("f:/error1/") + arr + "_xx.jpg";
		bm = bm.BgrToRgb();
		bm.SaveAsFile(s_save.data());
	}
	*/
}