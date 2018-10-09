#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//使用RGB存储格式
#include "freeImage/FreeImage.h"
#include "core/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace media{

class TiffReader_Internal
{
public:
	TiffReader_Internal();
	~TiffReader_Internal();

	bool open(const nb::core::String &path);

	//关闭文件
	void close();

	//是否有数据
	bool hasData() const;

	//获取总帧数
	int frameCount() const;

	//获取指定帧的图像
	Bitmap frame(int index) const;

private:
	TiffReader_Internal(const TiffReader_Internal &other);
	void operator = (const TiffReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
