#pragma once
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class TiffReader_Internal;
class NB_EXPORT TiffReader
{
public:
	//打开一个tiff文件
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
	//构建一个Tiff读取器
	TiffReader();

	~TiffReader();

private:
	TiffReader(const TiffReader &other);
	void operator = (const TiffReader &other);

	TiffReader_Internal	*m_internal;
};


}}
