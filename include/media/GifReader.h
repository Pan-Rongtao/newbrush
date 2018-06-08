#pragma once
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class GifReader_Internal;
class NB_EXPORT GifReader
{
public:
	//打开一个gif文件
	bool Open(const nb::System::String &path);

	//关闭文件
	void Close();

	//是否有数据
	bool HasData() const;

	//获取总帧数
	int GetFrameCount() const;

	//获取指定帧的图像
	Bitmap GetFrame(int index) const;

public:
	//构建一个Gif读取器
	GifReader();

	~GifReader();

private:
	GifReader(const GifReader &other);
	void operator = (const GifReader &other);

	GifReader_Internal	*m_internal;
};

}}
