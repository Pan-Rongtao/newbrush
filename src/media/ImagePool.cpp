#include "media/ImagePool.h"
#include "ImagePool_Internal.h"

using nb::Media::ImagePool;
using nb::Media::Bitmap;
using nb::Media::ImagePoolEvent;
using nb::Media::ImageSources;

ImagePool::ImagePool()
{
	m_pInternal = new ImagePool_Internal(this, nb::System::SizeI(160, 160));
}

ImagePool::ImagePool(const nb::System::SizeI &scaleSize)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
}

ImagePool::ImagePool(const nb::System::SizeI &scaleSize, ImagePool::Cache cache)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
	SetCache(cache);
}

ImagePool::ImagePool(const nb::System::SizeI &scaleSize, ImagePool::Cache cache, const nb::System::EnumFlags<nb::Media::ImagePool::FileType> &flags, ImagePool::LoadingDirection direction)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
	SetCache(cache);
	SetFilter(flags);
	SetLoadingDirection(direction);
}

ImagePool::~ImagePool()
{
	delete m_pInternal;
	m_pInternal = NULL;
}

//never use this
ImagePool::ImagePool(const ImagePool &other)
{
}
void ImagePool::operator = (const ImagePool &other)
{
}

void ImagePool::SetCache(ImagePool::Cache cache)
{
	m_pInternal->SetCache(cache);
}

ImagePool::Cache ImagePool::GetCache() const
{
	return m_pInternal->GetCache();
}

void ImagePool::SetFilter(const nb::System::EnumFlags<FileType> &flags)
{
	m_pInternal->SetFilter(flags);
}

nb::System::EnumFlags<nb::Media::ImagePool::FileType> ImagePool::GetFilter() const
{
	return m_pInternal->GetFilter();
}

void ImagePool::SetImageMemoryLimit(nb::Media::ImagePool::FileType type, int bytesLimit)
{
	m_pInternal->SetImageMemoryLimit(type, bytesLimit);
}

void ImagePool::SetImageMemoryLimitAllType(int bytesLimit)
{
	m_pInternal->SetImageMemoryLimitAllType(bytesLimit);
}

void ImagePool::SetLoadingDirection(ImagePool::LoadingDirection direction)
{
	m_pInternal->SetLoadingDirection(direction);
}

ImagePool::LoadingDirection ImagePool::GetLoadingDirection() const
{
	return m_pInternal->GetLoadingDirection();
}

void ImagePool::SetSourceFiles(const ImageSources &filePaths)
{
	m_pInternal->SetSourceFiles(filePaths);
}

void ImagePool::AppendSource(const nb::System::String &sSource)
{
	m_pInternal->AppendSource(sSource);
}

void ImagePool::InsertSource(int index, const nb::System::String &sSource)
{
	m_pInternal->InsertSource(index, sSource);
}

void ImagePool::RemoveSource(int index)
{
	m_pInternal->RemoveSource(index);
}

void ImagePool::UpdateSourceAt(int index, const nb::System::String &sSource)
{
	m_pInternal->UpdateSourceAt(index, sSource);
}

void ImagePool::GetSourceFileList(ImageSources &ret) const
{
	m_pInternal->GetSourceFileList(ret);
}

nb::System::String ImagePool::GetSourceAt(int index) const
{
	return m_pInternal->GetSourceAt(index);
}

int ImagePool::GetSourceFileCount() const
{
	return m_pInternal->GetSourceFileCount();
}

void ImagePool::SetSentry(int sentry)
{
	m_pInternal->SetSentry(sentry);
}

int ImagePool::GetSentry() const
{
	return m_pInternal->GetSentry();
}

void ImagePool::StartLoading()
{
	m_pInternal->StartLoading();
}

void ImagePool::StopLoading(bool bClear)
{
	m_pInternal->StopLoading(bClear);
}

bool ImagePool::IsWorking() const
{
	return m_pInternal->IsWorking();
}

bool ImagePool::GetImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty)
{
	return m_pInternal->GetImageItemPropertyAndLock(index, itemProperty);
}

void ImagePool::GetImageItemPropertyUnlock(int index)
{
	m_pInternal->GetImageItemPropertyUnlock(index);
}

nb::System::SizeI ImagePool::GetScaleSize() const
{
	return m_pInternal->GetScaleSize();
}

void ImagePool::SetListener(ImagePoolEvent *p)
{
	m_pInternal->SetListener(p);
}

ImagePoolEvent *ImagePool::GetListener() const
{
	return m_pInternal->GetListener();
}
