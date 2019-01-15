#pragma once
#include "../core/Size.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class NB_API ImageReader
{
public:
	//设置装载尺寸
	void setScaledSize(const nb::core::SizeI &size);

	//获取装载尺寸
	nb::core::SizeI scaledSize() const;

	//读取path的文件，并把伸缩后的图片数据保存在bm中
	void read(const nb::core::String &path, Bitmap *pBm);

	//读取path的文件，并把等比例伸缩后的数据保存到bm中
	void readUniform(const nb::core::String &path, Bitmap *pBm, nb::core::SizeI &OriginalSize);

public:
	//构建一个图片读取器，它读取的伸缩尺寸为160x160
	ImageReader();

	//构架一个图片读取器，它读取的伸缩尺寸为size
	//异常：size溢出
	ImageReader(const nb::core::SizeI &size);

	virtual ~ImageReader();

private:
	nb::core::SizeI		m_ScaleSize;
};

}}
