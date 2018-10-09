#include "ImagePool_Internal.h"
#include <algorithm>
#include "core/Exception.h"
#include "media/ImageReader.h"
#include "core/File.h"
#include "core/Singleton.h"

using namespace nb::core;
using namespace nb::System;
using namespace nb::media;

CriticalSection  ImagePool_Internal::SharedPathsManager::g_Lock;

ImagePool_Internal::ImagePool_Internal(ImagePool *pOwner, const SizeI &scaleSize)
: m_bStopFlag(false)
, m_ImgReader(scaleSize)
, m_Cache(ImagePool::Cache::CacheMode_Count_Limit, -1)
, m_LoadingDirection(ImagePool::Direction_Radiant)
, m_nSentry(0)
, m_pEventInterface(NULL)
, m_pOwner(pOwner)
{
	setFilter(ImagePool::FileType_Jpeg | ImagePool::FileType_Bmp | ImagePool::FileType_Png);
}

ImagePool_Internal::~ImagePool_Internal()
{
	clear();
}

void ImagePool_Internal::setCache(ImagePool::Cache cache)
{
	m_Cache = cache;
	//此处应该重新计算缓存动作
}

ImagePool::Cache ImagePool_Internal::cache() const
{
	ImagePool::Cache cache = m_Cache;
	return cache;
}

void ImagePool_Internal::setFilter(EnumFlags<ImagePool::FileType> flags)
{
	if(flags.testFlag(ImagePool::FileType_Unknown) || flags.testFlag(ImagePool::FileType_Reserve))
		NB_THROW_EXCEPTION("module out of bound.");

	m_FilterManager.SetFilter(flags);
	//此处应该重新计算缓存动作
}

EnumFlags<ImagePool::FileType> ImagePool_Internal::filter() const
{
	return m_FilterManager.filter();
}

void ImagePool_Internal::setImageMemoryLimit(ImagePool::FileType type, int bytesLimit)
{
	m_FilterManager.setBytesLimit(type, bytesLimit);
}

void ImagePool_Internal::setImageMemoryLimitAllType(int bytesLimit)
{
	m_FilterManager.setBytesLimitAllType(bytesLimit);
}

void ImagePool_Internal::setLoadingDirection(ImagePool::LoadingDirection direction)
{
	m_LoadingDirection = direction;
}

ImagePool::LoadingDirection ImagePool_Internal::loadingDirection() const
{
	ImagePool::LoadingDirection direction = m_LoadingDirection;
	return direction;
}

void ImagePool_Internal::setSourceFiles(const ImageSources &filePaths)
{
	m_ImageItemManager.setSourceFiles(filePaths);
}

void ImagePool_Internal::appendSource(const String &sSource)
{
	m_ImageItemManager.push(sSource);
}

void ImagePool_Internal::insertSource(int index, const String &sSource)
{
	m_ImageItemManager.insert(index, sSource);
}

void ImagePool_Internal::removeSource(int index)
{
	m_ImageItemManager.remove(index);
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, index);
}

void ImagePool_Internal::updateSourceAt(int index, const String &sSource)
{
	m_ImageItemManager.setSourceAt(index, sSource);
}

void ImagePool_Internal::getSourceFileList(ImageSources &ret) const
{
	m_ImageItemManager.getSourceFiles(ret);
}

String ImagePool_Internal::sourceAt(int index) const
{
	return m_ImageItemManager.sourceAt(index);
}

int ImagePool_Internal::sourceFileCount() const
{
	return m_ImageItemManager.count();
}

void ImagePool_Internal::setSentry(int sentry)
{
	m_nSentry = sentry;
}

int ImagePool_Internal::sentry() const
{
	int ret = nb::bound(0, sourceFileCount(), m_nSentry);
	return ret;
}

void ImagePool_Internal::startLoading()
{
	if(isWorking())
		return;

	m_bStopFlag = false;
	Thread::start();
}

void ImagePool_Internal::stopLoading(bool bClear)
{
	if(!isWorking())
		return;

	m_bStopFlag = true;
	if(bClear)
		clear();
}

bool ImagePool_Internal::isWorking() const
{
	return m_bStopFlag;
}

bool ImagePool_Internal::getImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty)
{
	if(m_ImageItemManager.tryLockOne(index))
	{
		ImageItem *item = m_ImageItemManager.itemAt(index);
		itemProperty.m_SourcePath = item->m_Source;
		itemProperty.m_Bitmap = item->m_Bm;
		itemProperty.m_Loaded = item->m_Bm != NULL || item->m_bError == true;
		itemProperty.m_Error = item->m_bError;
		itemProperty.m_OriginalSize = item->m_OriginalSize;
		return true;
	}
	else
	{
		try{
		itemProperty.m_SourcePath = m_ImageItemManager.sourceAt(index);
		}
		catch(Exception &e){(void)e;}
		itemProperty.m_Bitmap = NULL;
		itemProperty.m_Loaded = false;
		itemProperty.m_Error = false;
		itemProperty.m_OriginalSize = SizeI(0, 0);
		return false;
	}
}

void ImagePool_Internal::getImageItemPropertyUnlock(int index)
{
	m_ImageItemManager.unlockOne(index);
}

SizeI ImagePool_Internal::scaleSize() const
{
	SizeI sz = m_ImgReader.scaledSize();
	return sz;
}

void ImagePool_Internal::setListener(ImagePoolEvent *p)
{
	m_pEventInterface = p;
}

ImagePoolEvent *ImagePool_Internal::getListener() const
{
	return m_pEventInterface;
}

void ImagePool_Internal::clear()
{
	m_ImageItemManager.clear();
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, -1);
}

int ImagePool_Internal::calcNextLoadIndex(int &nNewCacheRangeBeg, int &nNewCacheRangeEnd) const
{
	int nRet = -1;
	ImagePool::LoadingDirection direction = loadingDirection();
	if(direction == ImagePool::Direction_Forward)
	{
		//正序找未加载的下标
		nNewCacheRangeEnd = sentry() + m_Cache.m_Size;
		if(nNewCacheRangeEnd >= sourceFileCount())
			nNewCacheRangeEnd = sourceFileCount();
		for(int i = sentry(); i < nNewCacheRangeEnd; ++i)
		{
			if(m_ImageItemManager.hasImageLoaded(i) == false)
			{
				nRet = i;
				break;
			}
		}

		int nReverseStart = sentry() - 1;
		nNewCacheRangeBeg = nNewCacheRangeEnd - cache().m_Size - 1;
		//如果正序未找到，表明到尾部，从哨岗处往回找
		if(nRet == -1 && nReverseStart >= 0)
		{
			for(int i = nReverseStart; i > nNewCacheRangeBeg; --i)
			{
				if(m_ImageItemManager.hasImageLoaded(i) == false)
				{
					nRet = i;
					break;
				}
			}
		}
	}
	else if(direction == ImagePool::Direction_Backward)
	{
	}
	else
	{
		//计算缓存区域
		int nCacheRangeSize = (std::min)(cache().m_Size, sourceFileCount());
		nNewCacheRangeBeg = sentry() - nCacheRangeSize / 2;
		nNewCacheRangeEnd = nNewCacheRangeBeg + nCacheRangeSize - 1;
		if(nNewCacheRangeBeg < 0)
		{
			nNewCacheRangeEnd += std::abs(nNewCacheRangeBeg);
			nNewCacheRangeBeg = 0;
		}
		else if(nNewCacheRangeEnd >= sourceFileCount())
		{
			nNewCacheRangeBeg -= (nNewCacheRangeEnd - sourceFileCount() + 1);
			nNewCacheRangeEnd = sourceFileCount() - 1;
		}

		//取最近的还没被加载的下标
		for(int i = 0; i <= nCacheRangeSize * 2; ++i)
		{
			int offset = (i / 2) * (i % 2 ? 1 : -1);
			int index = sentry() + offset;
			if(index >= nNewCacheRangeBeg && index <= nNewCacheRangeEnd && m_ImageItemManager.hasImageLoaded(index) == false
				/*&& Singleton<SharedPathsManager>::Current()->IsSourcePathLocked(m_ImageItems[index]->m_Source) == false*/)
			{
				nRet = index;
				break;
			}
		}
	}
	return nRet;
}

int ImagePool_Internal::calcFarestLoadedIndex(int nNewCacheRangeBeg, int nNewCacheRangeEnd) const
{
	std::vector<int> loadedIndices;
	m_ImageItemManager.getLoadedItems(loadedIndices);
	if(loadedIndices.empty())	
		return -1;

	int nFarestIndex = loadedIndices[0];
	int distanceMax = nb::distanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, nFarestIndex);
	for(int i = 0; i != loadedIndices.size(); ++i)
	{
		int n = loadedIndices[i];
		int distance = nb::distanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, n);
		if(distance > distanceMax)
		{
			nFarestIndex = n;
			distanceMax = distance;
		}
	}
	if(nb::distanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, nFarestIndex) == 0)
		nFarestIndex = -1;
	return nFarestIndex;
}

int ImagePool_Internal::loadedBytes() const
{
	return m_ImageItemManager.loadedBytes();
}

bool ImagePool_Internal::isCacheFull() const
{
	std::vector<int> loadedIndices;
	m_ImageItemManager.getLoadedItems(loadedIndices);
	bool b = (m_Cache.m_Mode == ImagePool::Cache::CacheMode_Count_Limit && loadedIndices.size() >= (unsigned int)m_Cache.m_Size) || (m_Cache.m_Mode == ImagePool::Cache::CacheMode_Bytes_Limit && loadedBytes() >= m_Cache.m_Size);
	return b;
}

void ImagePool_Internal::run()
{
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnLoading_Start(m_pOwner);

	try{
	while(true)
	{
		//计算下一次加载的下标和缓存区域
		int nNewCacheRangeBeg, nNewCacheRangeEnd;
		int nNextIndex = calcNextLoadIndex(nNewCacheRangeBeg, nNewCacheRangeEnd);
		//如果有可加载的下标
		if(nNextIndex == -1)
		{
			if(m_pEventInterface)
				m_pEventInterface->ImagePool_OnLoading_Idled(m_pOwner);

			msleep(10);
			continue;
		}
		else
		{
			//如果原缓存已满且，需释放一个离区域最远的图片
			if(isCacheFull())
			{
				int nFarestIndex = calcFarestLoadedIndex(nNewCacheRangeBeg, nNewCacheRangeEnd);
				if(nFarestIndex != -1)
				{
					if(m_ImageItemManager.tryLockOne(nFarestIndex))
					{
						m_ImageItemManager.eraseLoaded(nFarestIndex);
						m_ImageItemManager.unlockOne(nFarestIndex);
						if(m_pEventInterface)
							m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, nFarestIndex);
					}
				}
			}

			uint64_t tickBeg = nb::getTickCount();
			if(m_ImageItemManager.tryLockOne(nNextIndex) == false)	continue;		//如果尝试锁失败表面外部正在锁定图片，则不加载

			String path = m_ImageItemManager.sourceAt(nNextIndex);
			if(Singleton<SharedPathsManager>::Current()->tryLockSourcePath(path))	//如果尝试锁失败，则表示该路径已经在读取当中
			{
				if(m_FilterManager.testSuffixAndBytesLimit(path) == false)
				{
					m_ImageItemManager.markLoaded(nNextIndex, NULL, true, SizeI(0, 0));
				}
				else
				{
					Bitmap *pBm = new Bitmap();
					SizeI sz;
					m_ImgReader.readUniform(path, pBm, sz);
					m_ImageItemManager.markLoaded(nNextIndex, pBm, !(pBm->hasPixelData()), sz);
				}
				Singleton<SharedPathsManager>::Current()->unlockSourcePath(path);
				m_ImageItemManager.unlockOne(nNextIndex);	//解锁该图片

				uint64_t tickEnd = nb::getTickCount();
				if(m_pEventInterface)
					m_pEventInterface->ImagePool_OnImage_Loaded(m_pOwner, nNextIndex, (int)(tickEnd - tickBeg));
			}
			else
			{
				m_ImageItemManager.unlockOne(nNextIndex);	//解锁该图片
			}

		}

		msleep(1);
	}
	}
	catch(Exception &e){
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("exception: %s\r\n", e.what().data());
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
	}
	catch(...)
	{
		printf("other exception!!!!\r\n\r\n");
	}
}

////////////////////////////////
ImagePool_Internal::ImageItemManager::~ImageItemManager()
{
	clear();
}

void ImagePool_Internal::ImageItemManager::setSourceFiles(const ImageSources &filePaths)
{
	m_Lock.Lock();
	clear();
	for(int i = 0; i != filePaths.count(); ++i)
	{
		m_ImageItems.push_back(new ImageItem(filePaths[i]));
		Singleton<SharedPathsManager>::Current()->requestSourcePath(filePaths[i]);
	}
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::getSourceFiles(ImageSources &ret) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	for(int i = 0; i != m_ImageItems.size(); ++i)
		ret.pushBack(m_ImageItems[i]->m_Source);
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::setSourceAt(int index, const String &path)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		NB_THROW_EXCEPTION("index over flow");
	}
	m_ImageItems[index]->m_Source = path;
	delete m_ImageItems[index]->m_Bm;
	m_ImageItems[index]->m_Bm = NULL;
	m_ImageItems[index]->m_bError = false;
	m_ImageItems[index]->m_OriginalSize = SizeI(0, 0);
	std::vector<int>::iterator iter = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index);
	if(iter != m_LoadedIndices.end())	m_LoadedIndices.erase(iter);
	m_Lock.Unlock();
}

String ImagePool_Internal::ImageItemManager::sourceAt(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
		NB_THROW_EXCEPTION("index over flow");
	}
	String sRet = m_ImageItems[index]->m_Source;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return sRet;
}

ImagePool_Internal::ImageItem *ImagePool_Internal::ImageItemManager::itemAt(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
		NB_THROW_EXCEPTION("index over flow");
	}
	ImagePool_Internal::ImageItem *item = m_ImageItems[index];
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return item;
}

void ImagePool_Internal::ImageItemManager::push(const String &path)
{
	m_Lock.Lock();
	m_ImageItems.push_back(new ImageItem(path));
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::insert(int index, const String &path)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		NB_THROW_EXCEPTION("index over flow");
	}

	m_ImageItems.insert(m_ImageItems.begin() + index, new ImageItem(path));
	//此处有bug，需要对caches重新index重新排布
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::remove(int index)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		NB_THROW_EXCEPTION("erase out of index");
	}

	delete m_ImageItems[index]->m_Bm;
	delete m_ImageItems[index];
	m_ImageItems.erase(m_ImageItems.begin() + index);
	std::vector<int>::iterator iter = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index);
	if(iter != m_LoadedIndices.end()) m_LoadedIndices.erase(iter);
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::eraseLoaded(int index)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		NB_THROW_EXCEPTION("erase out of index");
	}

	delete m_ImageItems[index]->m_Bm;
	m_ImageItems[index]->m_Bm = NULL;
	m_ImageItems[index]->m_bError = false;
	m_ImageItems[index]->m_OriginalSize = SizeI(0, 0);
	std::vector<int>::iterator iter = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index);
	if(iter != m_LoadedIndices.end()) m_LoadedIndices.erase(iter);
	m_Lock.Unlock();
}

int ImagePool_Internal::ImageItemManager::count() const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	int nRet = (int)m_ImageItems.size();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return nRet;
}

void ImagePool_Internal::ImageItemManager::clear()
{
	m_Lock.Lock();
	for(int i = 0; i != m_ImageItems.size(); ++i)
	{
		Singleton<SharedPathsManager>::Current()->removeRef(m_ImageItems[i]->m_Source);
		delete m_ImageItems[i]->m_Bm;
		delete m_ImageItems[i];
	}
	m_ImageItems.clear();
	m_LoadedIndices.clear();
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::getLoadedItems(std::vector<int> &loadedIndices) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	loadedIndices = m_LoadedIndices;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
}

bool ImagePool_Internal::ImageItemManager::hasImageLoaded(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	bool b = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index) != m_LoadedIndices.end();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return b;
}

int ImagePool_Internal::ImageItemManager::loadedBytes() const
{
	int nRet = 0;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	for(int i = 0; i != m_LoadedIndices.size(); ++i)
			nRet += m_ImageItems[m_LoadedIndices[i]]->m_Bm->bytesCount();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return nRet;
}

void ImagePool_Internal::ImageItemManager::markLoaded(int index, Bitmap *bm, bool bError, const SizeI &originalSize)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		return;
	}
	m_ImageItems[index]->m_Bm = bm;
	m_ImageItems[index]->m_bError = bError;
	m_ImageItems[index]->m_OriginalSize = originalSize;
	m_LoadedIndices.push_back(index);
	m_Lock.Unlock();
}

bool ImagePool_Internal::ImageItemManager::tryLockOne(int index)
{
	m_Lock.Lock();
	if((index < 0 || index >= (int)m_ImageItems.size()) || (m_ImageItems[index]->isLocked()))
	{
		m_Lock.Unlock();
		return false;
	}

	m_ImageItems[index]->lock();
	m_Lock.Unlock();
	return true;
}

void ImagePool_Internal::ImageItemManager::unlockOne(int index)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		return;
	}
	m_ImageItems[index]->unlock();
	m_Lock.Unlock();
}

bool ImagePool_Internal::ImageItemManager::isLocked(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	bool b = m_ImageItems[index]->isLocked();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return b;
}

////////////////////
ImagePool_Internal::FilterItemManager::~FilterItemManager()
{
	clear();
}

void ImagePool_Internal::FilterItemManager::SetFilter(EnumFlags<ImagePool::FileType> flags)
{
	m_Lock.Lock();
	clear();
	if(flags.testFlag(ImagePool::FileType_Bmp))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("bmp");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Bmp, suffixs));
	}
	if(flags.testFlag(ImagePool::FileType_Jpeg))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("jpg");
		suffixs.push_back("jpeg");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Jpeg, suffixs));
	}
	if(flags.testFlag(ImagePool::FileType_Png))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("png");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Jpeg, suffixs));
	}
	m_Lock.Unlock();
}

EnumFlags<ImagePool::FileType> ImagePool_Internal::FilterItemManager::filter() const
{
	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Lock();
	EnumFlags<ImagePool::FileType> filter;
	for(int i = 0; i != m_Filters.size(); ++i)
		filter |= m_Filters[i]->m_FileType;
	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Unlock();
	return filter;
}

void ImagePool_Internal::FilterItemManager::setBytesLimit(ImagePool::FileType type, int bytesLimit)
{
	m_Lock.Lock();
	for(int i = 0; i != m_Filters.size(); ++i)
	{
		if(m_Filters[i]->m_FileType == type)
			m_Filters[i]->m_BytesLimit = bytesLimit;
	}
	m_Lock.Unlock();
}

void ImagePool_Internal::FilterItemManager::setBytesLimitAllType(int bytesLimit)
{
	m_Lock.Lock();
	setBytesLimit(ImagePool::FileType_Bmp, bytesLimit);
	setBytesLimit(ImagePool::FileType_Jpeg, bytesLimit);
	setBytesLimit(ImagePool::FileType_Png, bytesLimit);
	m_Lock.Unlock();
}

bool ImagePool_Internal::FilterItemManager::testSuffixAndBytesLimit(const String &path) const
{
	std::string s = path.ToUtf8().GetData();
	size_t n = s.rfind(".");
	std::string suffix = n == std::string::npos ? "" : s.substr(n + 1);
	if(suffix.empty())
		return false;

	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Lock();
	for(int i = 0; i != m_Filters.size(); ++i)
	{
		for(int j = 0; j != m_Filters[i]->m_Suffixs.size(); ++j)
		{
			String sOne = m_Filters[i]->m_Suffixs[j].data();
			if(String(suffix.data()).ToLower() == sOne.ToLower())
			{
				File file(path);
				file.Open(File::OpenExistsOnly, File::Read);
				if(file.IsOpened() && file.GetLenght() < (uint64_t)(m_Filters[i]->m_BytesLimit))
				{
					const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Unlock();
					return true;
				}
			}
		}
	}
	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Unlock();
	return false;
}

void ImagePool_Internal::FilterItemManager::clear()
{
	m_Lock.Lock();
	for(int i = 0; i != m_Filters.size(); ++i)
		delete m_Filters[i];
	m_Filters.clear();
	m_Lock.Unlock();
}

//////////////////////
void ImagePool_Internal::SharedPathsManager::requestSourcePath(const String &path)
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter == m_SourcePaths.end())
	{
		m_SourcePaths.insert(path);
	}
	else
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		const_cast<ImagePool_Internal::SharedPathItem &>(x).addRef();
	}
	g_Lock.Unlock();
}

void ImagePool_Internal::SharedPathsManager::removeRef(const String &path)
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		const_cast<ImagePool_Internal::SharedPathItem &>(x).subRef();
		if((*iter).ref() <= 0)
			m_SourcePaths.erase(iter);
	}
	g_Lock.Unlock();
}

bool ImagePool_Internal::SharedPathsManager::tryLockSourcePath(const String &path) 
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		if(x.isLocked() == false)
		{
			const_cast<ImagePool_Internal::SharedPathItem &>(x).lock();
			g_Lock.Unlock();
			return true;
		}
	}
	g_Lock.Unlock();
	return false;
}

void ImagePool_Internal::SharedPathsManager::unlockSourcePath(const String &path)
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		const_cast<ImagePool_Internal::SharedPathItem &>(x).unlock();
	}
	g_Lock.Unlock();
}
