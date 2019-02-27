/*******************************************************
**	Bitmap_Internal
**
**	Bitmap的私有类，使用到第三方开源库FreeImage
**	
**
**
**		潘荣涛
**	
********************************************************/
#pragma once
#define FREEIMAGE_COLORORDER	FREEIMAGE_COLORORDER_RGB	//使用RGB存储格式
#include "freeImage/FreeImage.h"
#include "media/Bitmap.h"

namespace nb{ namespace media{

class Bitmap_Internal
{
	friend class GifReader_Internal;
	friend class TiffReader_Internal;
public:
	//构建一个Bitmap_Internal，它不包含任何数据
	Bitmap_Internal();

	//构建一个Bitmap_Internal，它将从pFilePath加载，如果加载成功，他将包含数据，否则仍然不包含任何数据
	//异常：文件名不存在
	//异常：加载失败
	Bitmap_Internal(const std::string &path);

	//构建一个Bitmap_Internal，它的宽高为width和height，像素格式为format，如果format为Format_Invalid，将使用
	//异常：width < 0 或者 height < 0
	Bitmap_Internal(int width, int height, Bitmap::PixelFormat format);

	//构建一个Bitmap_Internal，它将从buffer位置加载数据，图像宽和高为width和height，像素格式为format
	//异常：width < 0 或者 height < 0
	Bitmap_Internal(const char *buffer, int width, int height, Bitmap::PixelFormat format);

	Bitmap_Internal(const Bitmap_Internal &other);
	~Bitmap_Internal();

	void operator = (const Bitmap_Internal &other);

public:
	//从文件中加载图片
	//异常：文件名不存在
	//异常：加载失败
	void load(const std::string &path, int jpegNarrow);

	//从数据块加载数据
	//异常：nLengthBytes < 0
	void load(const char *data, int bytes);

	//获取图像数据，返回纯图像数据的起始位置
	const char *data() const;

	//填充某种颜色
	void fill(unsigned int rgba);

	//是否有数据
	bool hasPixelData() const;

	//获取格式
	Bitmap::PixelFormat pixelFormat() const;

	//获取图片宽高，返回的是像素单位；如果bitmap不包括图片数据，将返回0
	int pixelWidth() const;
	int pixelHeight() const;

	//获取位深，可能值为1、4、8、16、24、32
	int bpp() const;

	int bytes() const;
	int bytesPerLine() const;
	//获取一行数据
	//异常：lineIndex < 0
	char *scanLine(int lineIndex);

	//获取单个像素颜色
	//异常：x，y越界
	unsigned int pixel(int x, int y) const;

	//设置单个像素颜色
	//异常：x，y越界
	void setPixel(int x, int y, unsigned int rgba);

	//拉伸至宽高width和height
	//异常：width < 0 或者 height < 0
	Bitmap_Internal scale(int width, int height) const;

	//复制图像的某个区域
	//异常：x，y越界；width < 0 或者 height < 0
	Bitmap_Internal copy(int x, int y, int width, int height) const;

	//转换为灰色图像
	Bitmap_Internal gray() const;

	//转换格式
	Bitmap_Internal convert(Bitmap::PixelFormat toFormat);

	//保存至文件，如果文件存在，将覆盖
	//异常：指定文件目录不存在
	void save(const std::string &path) const;

private:
	void initFreeeImage();
	void calcParam(int width, int height, Bitmap::PixelFormat format, int &bpp, int &rMask, int &gMask, int &bMask, int pitch);

	FIBITMAP		*m_pFreeImage;
};

}}
