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
#include <string>
#include "Bitmap.h"

namespace nb{ namespace media{

class ExifReader_Internal;
class NB_API ExifReader
{
public:
	struct ThumbnailProperties
	{
		int Width;
		int Height;
		int Bytes;
	};

public:
	//构建一个ExifReader读取器
	ExifReader();

	ExifReader(const ExifReader &other) = delete;
	void operator = (const ExifReader &other) = delete;

	~ExifReader();

	//打开
	//异常：文件不存在
	void open(const std::string &path);

	//获取宽度
	int width() const;

	//获取高度
	int height() const;

	//获取缩略图基本信息
	void getThumbnailsProperties(std::vector<ThumbnailProperties> &results) const;

	//获取缩略图
	void getThumbnails(std::vector<Bitmap> &results) const;

private:
	ExifReader_Internal		*m_internal;
};

}}
