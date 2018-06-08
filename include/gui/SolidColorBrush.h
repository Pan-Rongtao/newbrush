/*******************************************************
**	SolidBrush
**
**	纯色画刷
**	
**	继承于Brush
**	
**		只有颜色这个属性值
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Brush.h"
#include "system/Color.h"

namespace nb{ namespace Media{

class NB_EXPORT SolidColorBrush : public Brush
{
//public funs.
public:
	//设置画刷颜色
	void SetColor(const nb::System::Color &color);

	//获取画刷颜色
	const nb::System::Color &GetColor() const;


//constructors
public:
	SolidColorBrush();
	explicit SolidColorBrush(const nb::System::Color &color);
	~SolidColorBrush();

private:
	SolidColorBrush(const SolidColorBrush &other);
	void operator = (const SolidColorBrush &other);

	nb::System::Color					m_color;
};

typedef nbObjectPtrDerive<SolidColorBrush, BrushPtr> SolidColorBrushPtr;

}}
