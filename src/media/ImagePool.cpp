#include "media/ImagePool.h"
#include "ImagePool_Internal.h"

using namespace nb::core;
using namespace nb::System;
using namespace nb::media;

ImagePool::ImagePool()
{
	m_pInternal = new ImagePool_Internal(this, SizeI(160, 160));
}

ImagePool::ImagePool(const SizeI &scaleSize)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
}

ImagePool::ImagePool(const SizeI &scaleSize, ImagePool::Cache cache)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
	setCache(cache);
}

ImagePool::ImagePool(const SizeI &scaleSize, ImagePool::Cache cache, const EnumFlags<ImagePool::FileType> &flags, ImagePool::LoadingDirection direction)
{
	m_pInternal = new ImagePool_Internal(this, scaleSize);
	setCache(cache);
	setFilter(flags);
	setLoadingDirection(direction);
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

void ImagePool::setCache(ImagePool::Cache cache)
{
	m_pInternal->setCache(cache);
}

ImagePool::Cache ImagePool::cache() const
{
	return m_pInternal->cache();
}

void ImagePool::setFilter(const EnumFlags<FileType> &flags)
{
	m_pInternal->setFilter(flags);
}

EnumFlags<ImagePool::FileType> ImagePool::filter() const
{
	return m_pInternal->filter();
}

void ImagePool::setImageMemoryLimit(ImagePool::FileType type, int bytesLimit)
{
	m_pInternal->setImageMemoryLimit(type, bytesLimit);
}

void ImagePool::setImageMemoryLimitAllType(int bytesLimit)
{
	m_pInternal->setImageMemoryLimitAllType(bytesLimit);
}

void ImagePool::setLoadingDirection(ImagePool::LoadingDirection direction)
{
	m_pInternal->setLoadingDirection(direction);
}

ImagePool::LoadingDirection ImagePool::loadingDirection() const
{
	return m_pInternal->loadingDirection();
}

void ImagePool::setSourceFiles(const ImageSources &filePaths)
{
	m_pInternal->setSourceFiles(filePaths);
}

void ImagePool::appendSource(const String &sSource)
{
	m_pInternal->appendSource(sSource);
}

void ImagePool::insertSource(int index, const String &sSource)
{
	m_pInternal->insertSource(index, sSource);
}

void ImagePool::removeSource(int index)
{
	m_pInternal->removeSource(index);
}

void ImagePool::updateSourceAt(int index, const String &sSource)
{
	m_pInternal->updateSourceAt(index, sSource);
}

void ImagePool::getSourceFileList(ImageSources &ret) const
{
	m_pInternal->getSourceFileList(ret);
}

String ImagePool::sourceAt(int index) const
{
	return m_pInternal->sourceAt(index);
}

int ImagePool::sourceFileCount() const
{
	return m_pInternal->sourceFileCount();
}

void ImagePool::setSentry(int sentry)
{
	m_pInternal->setSentry(sentry);
}

int ImagePool::sentry() const
{
	return m_pInternal->sentry();
}

void ImagePool::startLoading()
{
	m_pInternal->startLoading();
}

void ImagePool::stopLoading(bool bClear)
{
	m_pInternal->stopLoading(bClear);
}

bool ImagePool::isWorking() const
{
	return m_pInternal->isWorking();
}

bool ImagePool::getImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty)
{
	return m_pInternal->getImageItemPropertyAndLock(index, itemProperty);
}

void ImagePool::getImageItemPropertyUnlock(int index)
{
	m_pInternal->getImageItemPropertyUnlock(index);
}

SizeI ImagePool::scaleSize() const
{
	return m_pInternal->scaleSize();
}

void ImagePool::setListener(ImagePoolEvent *p)
{
	m_pInternal->setListener(p);
}

ImagePoolEvent *ImagePool::getListener() const
{
	return m_pInternal->getListener();
}
