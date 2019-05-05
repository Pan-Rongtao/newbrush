#include "TestGifReader.h"
#include "media/GifReader.h"

using namespace nb::media;

void TestGifReader::test()
{
	GifReader gifR;
	bool b = gifR.open("f:/pics/gif/fire.gif");
	for(int i = 0; i != gifR.frameCount(); ++i)
	{
		Bitmap bm = gifR.frame(i);
		char arr[20] = {0};
		sprintf(arr, "f:/pics/gif/%d.jpg", i);
		bm.save(arr);
	}

}