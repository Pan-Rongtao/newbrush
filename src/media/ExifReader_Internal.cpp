#include "ExifReader_Internal.h"

using namespace nb::core;
using namespace nb::media;

ExifReader_Internal::ExifReader_Internal()
{

}

void ExifReader_Internal::open(const String &fileName)
{
	try{
		m_ImageLoaded = Exiv2::ImageFactory::open(fileName.ToUtf8().GetData());
		m_ImageLoaded->readMetadata();
	}
	catch(Exiv2::Error e)
	{
		NB_THROW_EXCEPTION(e.what());
	}
}

int ExifReader_Internal::width() const
{
	return m_ImageLoaded.get() == NULL ? 0 : m_ImageLoaded->pixelWidth();
}

int ExifReader_Internal::height() const
{
	return m_ImageLoaded.get() == NULL ? 0 : m_ImageLoaded->pixelHeight();
}

void ExifReader_Internal::getThumbnailsProperties(std::vector<ExifReader::ThumbnailProperties> &results) const
{
	if(m_ImageLoaded.get() == NULL)
		return;

	Exiv2::PreviewManager manager(*m_ImageLoaded);
	Exiv2::PreviewPropertiesList properties = manager.getPreviewProperties();
	for(int i = 0; i != properties.size(); ++i)
	{
		ExifReader::ThumbnailProperties thumb;
		thumb.Width = properties[i].width_;
		thumb.Height = properties[i].height_;
		thumb.Bytes = properties[i].size_;
		results.push_back(thumb);
	}
}

void ExifReader_Internal::getThumbnails(std::vector<Bitmap> &results) const
{
	if(m_ImageLoaded.get() == NULL)
		return;

	Exiv2::PreviewManager manager(*m_ImageLoaded);
	Exiv2::PreviewPropertiesList properties = manager.getPreviewProperties();
	for(int i = 0; i != properties.size(); ++i)
	{
		Exiv2::PreviewImage preview = manager.getPreviewImage(properties[i]);
		const unsigned char *data = preview.pData();
		int size = preview.size();
		Bitmap bm;
		bm.loadData(data, size);
		results.push_back(bm);
	}
}
