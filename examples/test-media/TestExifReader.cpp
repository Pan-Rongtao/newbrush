#include "TestExifReader.h"
#include "media/Bitmap.h"
#include "media/ExifReader.h"
#include "core/Exception.h"

using namespace nb::core;
using namespace nb::media;

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
			reader.open(sFile);
		}
		catch(Exception &e) {

		}
		std::vector<Bitmap> thumbs;
		reader.getThumbnails(thumbs);
		/*
		for(int j = 0; j != thumbs.size(); ++i)
		{
			int k = nb::getTickCount();
			Bitmap &bm = thumbs[j];
			int w = bm.GetWidth();
			int h = bm.GetHeight();
			int bytes = bm.GetBytesCount();

			char arr[100] = {0};
			sprintf(arr, "d:/%d.jpg", i);
			bm.saveAsFile(arr);
			int kk = nb::getTickCount();
			printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
			bool xx = 10;
		}
		*/

		if(!thumbs.empty())
		{
			int k = nb::getTickCount();
			char arr[100] = {0};
			sprintf(arr, "d:/%d.jpg", i);
			thumbs[0].saveAsFile(arr);
			int kk = nb::getTickCount();
		//	printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
		}
	}

	ExifReader reader1("e:/pics/111.jpg");
	std::vector<Bitmap> thumbs;
	reader1.getThumbnails(thumbs);
	Bitmap *bm = new Bitmap();
	bm->loadFileNarrowed("f:/xxx/3.jpg", 8);
	bm->saveAsFile("f:/xxx/yyy.jpg");
	delete bm;
/*
	ExifReader reader2("f:/xxx/0.jpg");
	std::vector<nb::Media::Bitmap> thumbs1;
	reader2.GetThumbnails(thumbs1);
	Bitmap *bm1 = &thumbs1[0];
	bm1->saveAsFile("f:/xxx/yyy.jpg");
*/
	ExifReader reader3;
	try{
	reader3.open("f:/15.png");
	}
	catch(...){}
	std::vector<Bitmap> thumbs3;
	reader3.getThumbnails(thumbs3);

}