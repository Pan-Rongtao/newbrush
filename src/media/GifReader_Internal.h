#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//使用RGB存储格式
#include "freeImage/FreeImage.h"
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class GifReader_Internal
{
public:
	GifReader_Internal();
	~GifReader_Internal();

	bool Open(const nb::System::String &path);

	void Close();

	bool HasData() const;

	int GetFrameCount() const;

	Bitmap GetFrame(int index) const;


private:
	GifReader_Internal(const GifReader_Internal &other);
	void operator = (const GifReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
