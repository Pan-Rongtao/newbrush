#pragma once
#include "system/SizeI.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class ImageReader
{
public:
	//设置装载尺寸
	void SetScaledSize(const nb::System::SizeI &size);

	//获取装载尺寸
	nb::System::SizeI GetScaledSize() const;

	//读取path的文件，并把伸缩后的图片数据保存在bm中
	void Read(const nb::System::String &path, nb::Media::Bitmap *pBm);

	//读取path的文件，并把等比例伸缩后的数据保存到bm中
	void ReadUniform(const nb::System::String &path, nb::Media::Bitmap *pBm, nb::System::SizeI &OriginalSize);

public:
	//构建一个图片读取器，它读取的伸缩尺寸为160x160
	ImageReader();

	//构架一个图片读取器，它读取的伸缩尺寸为size
	//异常：size溢出
	ImageReader(const nb::System::SizeI &size);

	virtual ~ImageReader();

private:
	nb::System::SizeI		m_ScaleSize;
};

}}
