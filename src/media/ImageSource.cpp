#include "media/ImageSource.h"
#include "media/Bitmap.h"

using namespace nb;

ImageSource::ImageSource()
	: ImageSource("")
{
}

ImageSource::ImageSource(const std::string & uri)
	: Bm([&](std::shared_ptr<Bitmap> v) { set(BmProperty(), v); }, [&]()->std::shared_ptr<Bitmap>& {return get<std::shared_ptr<Bitmap>>(BmProperty()); })
{
	Bm()->load(uri);
}

float ImageSource::width() const
{
	return (float)Bm()->width();
}

float ImageSource::heigth() const
{
	return (float)Bm()->height();
}

DependencyProperty ImageSource::BmProperty()
{
	static auto dp = DependencyProperty::registerDependency<ImageSource, std::shared_ptr<Bitmap>>("Bm", std::make_shared<Bitmap>());
	return dp;
}
