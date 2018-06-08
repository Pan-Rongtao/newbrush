/*******************************************************
**	Image
**
**	
**	
**		提供显示图片的一种基础控件
**			
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "Control.h"
#include "ImageSource.h"
#include "Stretch.h"

namespace nb{ namespace Gui{

class Image_Internal;
class NB_EXPORT Image : public Control
{
	NB_OBJECT_TYPE_DECLARE();

public:
	//源属性
	NB_X_OBJECT_PROPERTY_DECLARE(Source, nb::Media::ImageSource);
	//伸缩模式属性
	NB_OBJECT_ENUM_PROPERTY_DECLARE(Stretch, nb::Media::Stretch);

	nb::System::Size GetPixcelSize() const;

public:
	//构建一个Image，源为空，拉伸模式为Uniform
	Image();

	//构建一个Image，源为source，拉伸模式为Uniform
	Image(const nb::Media::ImageSourcePtr &source);

	//构建一个Image，源为source，拉伸模式为stretch
	Image(const nb::Media::ImageSourcePtr &source, nb::Media::Stretch stretch);
	~Image();

	IElementRender *GetElementRender() const;

protected:
	virtual System::Size MeasureOverride(const System::Size &availableSize);
	virtual System::Size ArrangeOverride(const System::Size &finalSize);

public:
	Image(const Image &other); //hp暂时改为公有的
private:
	void operator = (const Image &other);

	void OnSourceChanged(Core::PropertyValueChangedEventArgs &args);

private:
	Image_Internal	*m_internal;
};

typedef nbObjectPtrDerive<Image, ControlPtr> ImagePtr;

}}
