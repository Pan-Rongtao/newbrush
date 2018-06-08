#include "TestTiffReader.h"
#include "media/TiffReader.h"

using namespace nb::Media;

void TestTiffReader::Test()
{
	TiffReader TiffR;
	bool b = TiffR.Open("d:/pic.tiff");
	for(int i = 0; i != TiffR.GetFrameCount(); ++i)
	{
		Bitmap bm = TiffR.GetFrame(i);
		char arr[20] = {0};
		sprintf(arr, "d:/%d.jpg", i);
		bm.SaveAsFile(arr);
	}

}