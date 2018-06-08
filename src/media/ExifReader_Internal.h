#pragma once
#include <vector>
#include "system/String.h"
#include "media/Bitmap.h"
#include "media/ExifReader.h"
#include "exiv2/exiv2.hpp"

namespace nb{namespace Media{

class ExifReader_Internal
{
public:
	ExifReader_Internal();

	void Open(const nb::System::String &fileName);

	int GetWidth() const;
	int GetHeight() const;

	void GetThumbnailsProperties(std::vector<ExifReader::ThumbnailProperties> &results) const;
	void GetThumbnails(std::vector<nb::Media::Bitmap> &results) const;

private:
	Exiv2::Image::AutoPtr	m_ImageLoaded;
};

}}

