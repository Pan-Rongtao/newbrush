#pragma once
#include <vector>
#include <string>
#include "media/Bitmap.h"
#include "media/ExifReader.h"
#include "exiv2/exiv2.hpp"

namespace nb{namespace media{

class ExifReader_Internal
{
public:
	ExifReader_Internal();

	void open(const std::string &path);

	int width() const;
	int height() const;

	void getThumbnailsProperties(std::vector<ExifReader::ThumbnailProperties> &results) const;
	void getThumbnails(std::vector<Bitmap> &results) const;

private:
	Exiv2::Image::AutoPtr	m_ImageLoaded;
};

}}

