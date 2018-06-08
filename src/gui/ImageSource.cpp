#include "gui/ImageSource.h"
#include "gles/Texture.h"

using namespace nb::Media;
using namespace nb::gl::Gles;
using namespace nb::System;

NB_OBJECT_NO_ASSEMBLY_TYPE_IMPLEMENT(ImageSource, nbObject);

ImageSource::ImageSource()
: m_Texture(NULL)
{
}

ImageSource::ImageSource(const String &path)
{
	SetUri(path);
}

void ImageSource::SetUri(const String &path)
{
	m_Texture = new Texture2D();
	m_Texture->LoadFromPath(path);
}

const String ImageSource::GetUri() const
{
	return "";
//	return m_Texture == NULL ? "" : m_Texture->GetLoadedPath();
}

int ImageSource::GetPixelWidth() const
{
	return m_Texture == NULL ? 0 : m_Texture->GetPixcelWidth();
}

int ImageSource::GetPixcelHeight() const
{
	return m_Texture == NULL ? 0 : m_Texture->GetPixcelHeight();
}

nb::gl::Gles::Texture2D *ImageSource::GetTexture() const
{
	return m_Texture;
}
