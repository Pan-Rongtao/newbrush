#include "gui/ImageSource.h"
#include "gles/Texture2D.h"
#include "core/Size.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gui;
using namespace nb::gl;

ImageSource::ImageSource()
	: ImageSource("")
{
}

ImageSource::ImageSource(const std::string & uri)
	: Bm([&](std::shared_ptr<Bitmap> v) { set(BmProperty(), v); }, [&]() {return get<std::shared_ptr<Bitmap>>(BmProperty()); })
{
	Bm = std::make_shared<Bitmap>(uri);

}

float nb::gui::ImageSource::width() const
{
	return (float)Bm()->width();
}

float nb::gui::ImageSource::heigth() const
{
	return (float)Bm()->height();
}

const DependencyProperty ImageSource::BmProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<ImageSource, std::shared_ptr<Bitmap>>("RowDefinitions", nullptr);
	return dp;
}
