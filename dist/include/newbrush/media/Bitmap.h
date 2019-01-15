/*******************************************************
**	Bitmap
**
**	点阵图类
**	
**	提供点阵图的构造方式和对图像的简单操作，如伸缩等
**	
**
**	
**	图片数据可来源于文件，或者内存块数据
**	
**  
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Def.h"
#include "../core/String.h"
#include "../core/Point.h"
#include "../core/Color.h"
#include "../core/Size.h"
#include "../core/Rect.h"

namespace nb{ namespace media {

class Bitmap_Internal;
class NB_API Bitmap
{
public:
	//注意：Pixel的实际存储格式是BGR的，B在高位，R在低位，如果需要B R调换，调用BgrToRgb函数（已改成RGB）
	enum PixelFormat
	{
		Format_Invalid = 0,		//不可用的图像
		Format_Bpp1_Palette,	//1位调色板图像
		Format_Bpp4_Palette,	//4位调色板图像
		Format_Bpp8_Palette,	//8位调色板图像
		Format_Bpp16_Rgb555,	//16位Rgb图像，保留位-1, R-5, G-1, B-5
		Format_Bpp16_Rgb565,	//16位Rgb图像，R-5, G-6, B-5
		Format_Bpp24_Rgb888,	//24位Rgb图像，R-8, G-8, B-8
		Format_Bpp32_Rgba8888,	//32Rgba位图像, R-8, G-8, B-8，A-8
	};

public:
	//创建一个空的Bitmap对象，它将不包含任何图像数据
	Bitmap();

	//从文件创建一个Bitmap
	explicit Bitmap(const nb::core::String &filePath);

	//创建一个指定尺寸的Bitmap，图像数据未初始化(PixelFormat=Format_Bpp32_Argb8888)
	Bitmap(int width, int height);
	explicit Bitmap(const nb::core::SizeI &size);

	//创建一个指定尺寸的Bitmap，并指定它的PixelFormat，图像数据未初始化
	Bitmap(int width, int height, PixelFormat format);
	Bitmap(const nb::core::SizeI &size, PixelFormat format);

	//创建一个指定尺寸的Bitmap，并指定它的PixelFormat，加载数据（数据为纯图片数据，非文件头包含）
	Bitmap(const unsigned char *buffer, int width, int height, PixelFormat format);
	Bitmap(const unsigned char *buffer, const nb::core::SizeI &size, PixelFormat format);

	~Bitmap();

	Bitmap(const Bitmap &other);

	void operator = (const Bitmap &other);

public:
	//从文件加载并解析
	//异常：文件不存在
	//异常：加载失败
	void loadFile(const char *pFilePath);
	void loadFile(const nb::core::String &filePath);

	//从文件加载，并在解析成特定的缩小倍数
	//jpeg_narrow：jpeg缩小倍数，只针对jpeg有效；只能取1、2、4、8；如果不是这几个值，取最近的一个
	//异常：文件不存在
	//异常：加载失败
	//说明：该方式在加载jpeg文件时将比正常的加载文件后Scale效率高
	void loadFileNarrowed(const nb::core::String &filePath, int jpegNarrow);

	//从数据中加载（数据为包含数据头部的数据，比如一个图片文件的数据流），长度以字节为单位
	//异常：nLengthBytes < 0
	void loadData(const unsigned char *data, int nLengthBytes);

	//获取图像数据，返回纯图像数据的起始位置
	const unsigned char *data() const;

	//填充某种颜色（未实现，请勿使用）
	void fill(const nb::core::Color &c);

	//获取图像的宽、高、尺寸，如果无数据，将返回0
	int width() const;
	int height() const;
	nb::core::SizeI size() const;

	//获取纯数据字节总数
	int bytesCount() const;

	//每行数据起始
	unsigned char *scanLine(int lineIndex);

	//是否为空
	bool isNull() const;

	//是否有数据
	bool hasPixelData() const;

	//获取图像格式
	PixelFormat pixelFormat() const;

	//获取像素位深(bpp)，根据PixelFormat返回1、4、8、16、24、32
	int bpp() const;

	//获取像素点的颜色值，（未实现，勿使用！）
	//异常：x，y越界溢出
	nb::core::Color pixel(int x, int y) const;
	nb::core::Color pixel(const nb::core::PointI &p) const;

	//设置像素点的颜色值，（未实现，勿使用！）
	//异常：x，y越界溢出
	void setPixel(int x, int y, const nb::core::Color &c);
	void setPixel(const nb::core::PointI &p, const nb::core::Color &c);


	//拉伸至宽高width和height（该操作可能消耗较多时间）
	//异常：width < 0 或者 height < 0
	Bitmap scale(int width, int height) const;
	Bitmap scale(const nb::core::SizeI &size) const;
	Bitmap scaleWidth(int width) const;
	Bitmap scaleHeight(int height) const;

	//复制图像的某个区域
	//异常：x、y、width、height越界
	Bitmap copy() const;
	Bitmap copy(int x, int y, int width, int height) const;
	Bitmap copy(const nb::core::RectI &rc) const;

	//转换为灰色图像
	Bitmap toGray() const;

	//格式转换
	Bitmap converToFormat(PixelFormat format);

	//保存为图像，将根据后缀判断保存的图片类型，如果不能从后缀判断出来，则保存为BMP图片
	//异常：文件路径不存在
	void saveAsFile(const char *pFilePath) const;
	void saveAsFile(const nb::core::String &filePath) const;

	//从BGR数据格式转换为RGB
	//注意，如果原format并非是BGR的格式而是Palette格式，将不做转换
	//Bitmap BgrToRgb() const;

private:
	Bitmap_Internal		*m_internal;
};

}}
