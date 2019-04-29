#include "gui/Image.h"

using namespace nb::gui;
using namespace nb::core;

Image::Image()
	: Source(nullptr)
	, Stretch(Origion)
{
	Source.notify(std::bind(&Image::onSourceChanged, this, std::placeholders::_1, std::placeholders::_2));
	Stretch.notify(std::bind(&Image::onStretchChanged, this, std::placeholders::_1, std::placeholders::_2));
//	Stretch.setNotify([this] {});
}

Image::Image(const std::shared_ptr<ImageSource> &source)
	: Source(source)
	, Stretch(Origion)
{
	Source.notify(std::bind(&Image::onSourceChanged, this, std::placeholders::_1, std::placeholders::_2));
	Stretch.notify(std::bind(&Image::onStretchChanged, this, std::placeholders::_1, std::placeholders::_2));
}

Image::Image(const std::shared_ptr<ImageSource> &source, nb::gui::Stretch stretch)
	: Source(source)
	, Stretch(stretch)
{
	Source.notify(std::bind(&Image::onSourceChanged, this, std::placeholders::_1, std::placeholders::_2));
	Stretch.notify(std::bind(&Image::onStretchChanged, this, std::placeholders::_1, std::placeholders::_2));
}

Size Image::measureOverride(const Size & availableSize) const
{
	std::shared_ptr<ImageSource> source = Source;
	return Size((float)source->Width, (float)source->Height);
}

Size Image::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}

Image::Image(const Image &other)
{
}

Image::~Image()
{
}

void Image::operator = (const Image &other)
{
}

void Image::onSourceChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{
	
}

void Image::onStretchChanged(const nb::gui::Stretch &_old, const nb::gui::Stretch &_new)
{
	
}