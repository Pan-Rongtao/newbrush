#include "TestExifReader.h"
#include "media/Bitmap.h"
#include "media/ExifReader.h"

using namespace nb::core;
using namespace nb::media;

static int FILE_COUNT = 23;
void TestExifReader::test()
{
	ExifReader reader;
//	reader.Open("d:/err_exif.jpg");

	for(int i = 0; i != FILE_COUNT; ++i)
	{
		char sFile[100] = {0};
		snprintf(sFile, sizeof(sFile), "e:/Pics/%d.jpg", i);
		try{
			reader.open(sFile);
		}
		catch(...) {

		}
		std::vector<Bitmap> thumbs;
		reader.getThumbnails(thumbs);
		/*
		for(int j = 0; j != thumbs.size(); ++i)
		{
			int k = NB_TICK_COUT;
			Bitmap &bm = thumbs[j];
			int w = bm.GetWidth();
			int h = bm.GetHeight();
			int bytes = bm.GetBytesCount();

			char arr[100] = {0};
			sprintf(arr, "d:/%d.jpg", i);
			bm.saveAsFile(arr);
			int kk = NB_TICK_COUT;
			printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
			bool xx = 10;
		}
		*/

		if(!thumbs.empty())
		{
			auto k = NB_TICK_COUT;
			char arr[100] = {0};
			snprintf(arr, sizeof(arr), "d:/%d.jpg", i);
			thumbs[0].save(arr);
			auto kk = NB_TICK_COUT;
		//	printf("[%d]thumb [%s] [%d]\r\n", i, sFile, kk - k);
		}
	}

	ExifReader reader1;
	reader1.open("e:/pics/111.jpg");
	std::vector<Bitmap> thumbs;
	reader1.getThumbnails(thumbs);
	Bitmap *bm = new Bitmap();
	bm->load("f:/xxx/3.jpg", 8);
	bm->save("f:/xxx/yyy.jpg");
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