#pragma once
#include "../core/String.h"
#include "Bitmap.h"

namespace nb{ namespace media{

class TiffReader_Internal;
class NB_API TiffReader
{
public:
	//构建一个Tiff读取器
	TiffReader();

	~TiffReader();

public:
	//打开一个tiff文件
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
	TiffReader(const TiffReader &other);
	void operator = (const TiffReader &other);

	TiffReader_Internal	*m_internal;
};


}}
