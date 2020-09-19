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
#include "newbrush/model/Def.h"

namespace nb{

class NB_API Bitmap
{
public:
	//创建一个空的Bitmap对象，它将不包含任何图像数据
	Bitmap();

	//从文件创建一个Bitmap
	explicit Bitmap(const std::string &path);

	~Bitmap();

	Bitmap(const Bitmap &other);
	void operator = (const Bitmap &other);

	//从文件加载并解析
	//异常：文件不存在
	//异常：加载失败
	void load(const std::string &path);

	//从数据中加载（数据为包含数据头部的数据，比如一个图片文件的数据流），长度以字节为单位
	void load(const unsigned char *buffer, uint32_t bytes);

	//是否可用
	bool isValid() const;

	//获取图像数据，返回纯图像数据的起始位置
	const unsigned char *data() const;

	//获取图像的宽、高、尺寸，如果无数据，将返回0
	int32_t width() const;
	int32_t height() const;

	//获取纯数据字节总数
	int bytes() const;

	//通道数（返回1到4）
	int channels() const;

	//伸缩
	bool scale(uint32_t width, uint32_t height);

	//保存为图像
	//path：将根据后缀判断保存的图片类型，如果不能从后缀判断出来，则保存为BMP图片
	//quality：仅对jpg格式有效的图片质量参数（0-100）
	//返回值：成功返回true，否则返回false
	bool save(const std::string &path, uint32_t quality = 1) const;
	
private:
	unsigned char	*m_data;
	int32_t			m_width;
	int32_t			m_height;
	int32_t			m_channels;
};

using BitmapPtr = std::shared_ptr<Bitmap>;
}
