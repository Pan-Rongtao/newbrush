#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//使用RGB存储格式
#include "freeImage/FreeImage.h"
#include "core/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace media{

class GifReader_Internal
{
public:
	GifReader_Internal();
	~GifReader_Internal();

	bool open(const nb::core::String &path);

	void close();

	bool hasData() const;

	int frameCount() const;

	Bitmap frame(int index) const;


private:
	GifReader_Internal(const GifReader_Internal &other);
	void operator = (const GifReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
