#include <assert.h>
#include "gui/Image.h"
#include "Image_Internal.h"

using namespace nb::Gui;

using namespace nb::Core;
using namespace nb::System;
using namespace nb::Media;


NB_OBJECT_TYPE_IMPLEMENT(Image, Control, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(Image, Source, ImageSource, &Image::OnSourceChanged);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(Image, Stretch, EnumObject, NULL);

Image::Image(void)
: m_internal(NULL)
{
	m_internal = new Image_Internal(this);
	Stretch() = nb::Media::Origion;
}

Image::Image(const nb::Media::ImageSourcePtr &source)
: m_internal(NULL)
{
	m_internal = new Image_Internal(this);
	Source = source;
	Stretch() = nb::Media::Origion;
}

Image::Image(const nb::Media::ImageSourcePtr &source, nb::Media::Stretch stretch)
: m_internal(NULL)
{
	m_internal = new Image_Internal(this);
	Source = source;
	Stretch() = nb::Media::Origion;
}

//never use this bellow
Image::Image(const Image &other)
: m_internal(NULL)
{
	delete m_internal;
	m_internal = new Image_Internal(this);
	Source = other.Source;
}

Image::~Image()
{
	delete m_internal;
	m_internal = NULL;
}
//never use this bellow
void Image::operator = (const Image &other)
{
	delete m_internal;
	m_internal = new Image_Internal(this);
	Source = other.Source;
}

IElementRender *Image::GetElementRender() const
{
	return m_internal;
}

Size Image::MeasureOverride(const Size &availableSize)
{
	return GetPixcelSize();
	//return availableSize;
}

nb::System::Size Image::ArrangeOverride(const nb::System::Size &finalSize)
{
	return finalSize;
}

void Image::OnSourceChanged(PropertyValueChangedEventArgs &args)
{
	m_internal->OnSourceChanged(args);
	NotifyContentChanged();
}

Size Image::GetPixcelSize() const
{
	if(Source == NULL) return Size(0, 0);
	return Size(Source->GetPixelWidth(), Source->GetPixcelHeight());
}

