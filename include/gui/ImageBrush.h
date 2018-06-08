/*******************************************************
**	SolidBrush
**
**	图片画刷
**	
**	继承于Brush，描述用于图片绘画的刷子
**	
**		源属性
**		Stretch属性
**		水平和垂直对其方式属性
**
**		潘荣涛
**	
********************************************************/
#include "Brush.h"
#include "core/Object.h"
#include "system/Size.h"
#include "gui/ImageSource.h"
#include "gui/Stretch.h"

namespace nb{ namespace Media {

class NB_EXPORT ImageBrush : public Brush
{
public:
	//源设置
	void SetImageSource(const ImageSourcePtr &imgSource);

	//获取源
	const ImageSourcePtr &GetImageSource() const;

	//设置内容大小调整模式
	void SetStretch(Stretch mode);

	//获取内容大小调整模式
	Stretch GetStretch() const;

	nb::System::Size GetPixcelSize() const;


public:
	ImageBrush();
	ImageBrush(const ImageSourcePtr &imgSource);
	~ImageBrush();

private:
	ImageBrush(const ImageBrush &other);
	void operator = (const ImageBrush &other);

private:
	ImageSourcePtr					m_imgSource;
	Stretch							m_Stretch;
};

typedef nbObjectPtrDerive<ImageBrush, BrushPtr>	ImageBrushPtr;

}}
