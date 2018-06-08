#include "TestGifReader.h"
#include "media/GifReader.h"

using namespace nb::Media;

void TestGifReader::Test()
{
	GifReader gifR;
	bool b = gifR.Open("f:/pics/gif/fire.gif");
	for(int i = 0; i != gifR.GetFrameCount(); ++i)
	{
		Bitmap bm = gifR.GetFrame(i);
		char arr[20] = {0};
		sprintf(arr, "f:/pics/gif/%d.jpg", i);
		bm.SaveAsFile(arr);
	}

}