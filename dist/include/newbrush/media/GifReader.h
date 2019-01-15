#pragma once
#include "../core/String.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class GifReader_Internal;
class NB_API GifReader
{
public:
	//构建一个Gif读取器
	GifReader();

	~GifReader();

public:
	//打开一个gif文件
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
	GifReader(const GifReader &other);
	void operator = (const GifReader &other);

	GifReader_Internal	*m_internal;
};

}}
