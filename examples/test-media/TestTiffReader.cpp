#include "TestTiffReader.h"
#include "media/TiffReader.h"

using namespace nb::media;

void TestTiffReader::test()
{
	TiffReader TiffR;
	bool b = TiffR.open("d:/pic.tiff");
	for(int i = 0; i != TiffR.frameCount(); ++i)
	{
		Bitmap bm = TiffR.frame(i);
		char arr[20] = {0};
		snprintf(arr, sizeof(arr), "d:/%d.jpg", i);
		bm.save(arr);
	}

}