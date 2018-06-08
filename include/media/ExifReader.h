/******************************************************************************

* Copyright (c) 2016，德赛西威汽车电子有限公司

* All rights reserved

* 编写者: 潘荣涛

* 编写日期: 2017-03

* 简要描述: ExifReader
				
		EXIF（Exchangeable Image File）是“可交换图像文件”的缩写，当中包含了
		专门为数码相机的照片而定制的元数据，可以记录数码照片的拍摄参数、缩略图
		及其他属性信息：
			1、拍摄日期
			2、拍摄器材（机身、镜头、闪光灯等）
			3、拍摄参数（快门速度、光圈F值、ISO速度、焦距、测光模式等）
			4、图像处理参数（锐化、对比度、饱和度、白平衡等）
			5、图像描述及版权信息
			6、GPS定位数据
			7、缩略图（一张图片可能包含多个缩略图数据）

* 修改记录:

*****************************************************************************/
#pragma once
#include <vector>
#include "system/String.h"
#include "media/Bitmap.h"

namespace nb{ namespace Media{

class ExifReader_Internal;
class NB_EXPORT ExifReader
{
public:
	struct ThumbnailProperties
	{
		int Width;
		int Height;
		int Bytes;
	};

public:
	//打开
	//异常：文件不存在
	void Open(const nb::System::String &fileName);

	//获取宽度
	int GetWidth() const;

	//获取高度
	int GetHeight() const;

	//获取缩略图基本信息
	void GetThumbnailsProperties(std::vector<ThumbnailProperties> &results) const;

	//获取缩略图
	void GetThumbnails(std::vector<nb::Media::Bitmap> &results) const;

public:
	//构建一个ExifReader读取器
	ExifReader();

	//构建一个ExifReader，它指向路径为fileName的文件
	//异常：文件不存在
	explicit ExifReader(const nb::System::String &fileName);

	~ExifReader();

private:
	ExifReader(const ExifReader &other);
	void operator = (const ExifReader &other);

	ExifReader_Internal		*m_internal;
};

}}
