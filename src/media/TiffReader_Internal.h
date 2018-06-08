#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//使用RGB存储格式
#include "freeImage/FreeImage.h"
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class TiffReader_Internal
{
public:
	TiffReader_Internal();
	~TiffReader_Internal();

	bool Open(const nb::System::String &path);

	//关闭文件
	void Close();

	//是否有数据
	bool HasData() const;

	//获取总帧数
	int GetFrameCount() const;

	//获取指定帧的图像
	Bitmap GetFrame(int index) const;

private:
	TiffReader_Internal(const TiffReader_Internal &other);
	void operator = (const TiffReader_Internal &other);

	FIMULTIBITMAP		*m_pFreeImage;
};

}}
