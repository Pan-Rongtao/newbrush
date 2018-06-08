#include "TestExifReader.h"
#include "media/Bitmap.h"
#include "media/ExifReader.h"
#include "system/Platform.h"

using nb::Media::Bitmap;
using nb::Media::ExifReader;

static int FILE_COUNT = 23;
void TestExifReader::Test()
{
	ExifReader reader;
//	reader.Open("d:/err_exif.jpg");

	for(int i = 0; i != FILE_COUNT; ++i)
	{
		char sFile[100] = {0};
		sprintf(sFile, "e:/Pics/%d.jpg", i);
		try{
			reader.Open(sFile);
		}
		catch(nb::Core::ExceptionPtr &e) {

		}
		std::vector<Bitmap> thumbs;
		reader.GetThumbnails(thumbs);
		/*
		for(int j = 0; j != thumbs.size(); ++i)
		{
			int k = nb::System::Platform::GetTickCount();
			Bitmap &bm = thumbs[j];
			int w = bm.GetWidth();
			int h = bm.GetHeight();
			int bytes = bm.GetBytesCount();

			char arr[100] = {0};
			sprintf(arr, "d:/%d.jpg", i);
			bm.SaveAsFile(arr);
			int kk = nb::System::Platform::GetTickCount();
			printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
			bool xx = 10;
		}
		*/

		if(!thumbs.empty())
		{
			int k = nb::System::Platform::GetTickCount();
			char arr[100] = {0};
			sprintf(arr, "d:/%d.jpg", i);
			thumbs[0].SaveAsFile(arr);
			int kk = nb::System::Platform::GetTickCount();
		//	printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
		}
	}

	ExifReader reader1("e:/pics/111.jpg");
	std::vector<nb::Media::Bitmap> thumbs;
	reader1.GetThumbnails(thumbs);
	Bitmap *bm = new Bitmap();
	bm->LoadFileNarrowed("f:/xxx/3.jpg", 8);
	bm->SaveAsFile("f:/xxx/yyy.jpg");
	delete bm;
/*
	ExifReader reader2("f:/xxx/0.jpg");
	std::vector<nb::Media::Bitmap> thumbs1;
	reader2.GetThumbnails(thumbs1);
	Bitmap *bm1 = &thumbs1[0];
	bm1->SaveAsFile("f:/xxx/yyy.jpg");
*/
	ExifReader reader3;
	try{
	reader3.Open("f:/15.png");
	}
	catch(...){}
	std::vector<nb::Media::Bitmap> thumbs3;
	reader3.GetThumbnails(thumbs3);

}