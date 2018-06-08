#include "ImagePool_Internal.h"
#include "core/Exception.h"
#include "media/ImageReader.h"
#include "system/Platform.h"
#include "system/System.h"
#include "system/File.h"
#include <algorithm>
#include "system/Singleton.h"

using nb::Media::ImagePool_Internal;
using nb::Media::ImagePool;
using nb::Media::ImagePoolEvent;
using nb::Media::Bitmap;
using nb::Media::ImageSources;
using namespace nb::System;

nb::System::CriticalSection  ImagePool_Internal::SharedPathsManager::g_Lock;

ImagePool_Internal::ImagePool_Internal(ImagePool *pOwner, const nb::System::SizeI &scaleSize)
: m_bStopFlag(false)
, m_ImgReader(scaleSize)
, m_Cache(ImagePool::Cache::CacheMode_Count_Limit, -1)
, m_LoadingDirection(ImagePool::Direction_Radiant)
, m_nSentry(0)
, m_pEventInterface(NULL)
, m_pOwner(pOwner)
{
	SetFilter(ImagePool::FileType_Jpeg | ImagePool::FileType_Bmp | ImagePool::FileType_Png);
}

ImagePool_Internal::~ImagePool_Internal()
{
	Clear();
}

void ImagePool_Internal::SetCache(ImagePool::Cache cache)
{
	m_Cache = cache;
	//此处应该重新计算缓存动作
}

ImagePool::Cache ImagePool_Internal::GetCache() const
{
	ImagePool::Cache cache = m_Cache;
	return cache;
}

void ImagePool_Internal::SetFilter(nb::System::EnumFlags<ImagePool::FileType> flags)
{
	if(flags.TestFlag(ImagePool::FileType_Unknown) || flags.TestFlag(ImagePool::FileType_Reserve))
		NB_THROW_EXCEPTION("module out of bound.");

	m_FilterManager.SetFilter(flags);
	//此处应该重新计算缓存动作
}

nb::System::EnumFlags<ImagePool::FileType> ImagePool_Internal::GetFilter() const
{
	return m_FilterManager.GetFilter();
}

void ImagePool_Internal::SetImageMemoryLimit(nb::Media::ImagePool::FileType type, int bytesLimit)
{
	m_FilterManager.SetBytesLimit(type, bytesLimit);
}

void ImagePool_Internal::SetImageMemoryLimitAllType(int bytesLimit)
{
	m_FilterManager.SetBytesLimitAllType(bytesLimit);
}

void ImagePool_Internal::SetLoadingDirection(ImagePool::LoadingDirection direction)
{
	m_LoadingDirection = direction;
}

ImagePool::LoadingDirection ImagePool_Internal::GetLoadingDirection() const
{
	ImagePool::LoadingDirection direction = m_LoadingDirection;
	return direction;
}

void ImagePool_Internal::SetSourceFiles(const ImageSources &filePaths)
{
	m_ImageItemManager.SetSourceFiles(filePaths);
}

void ImagePool_Internal::AppendSource(const nb::System::String &sSource)
{
	m_ImageItemManager.Push(sSource);
}

void ImagePool_Internal::InsertSource(int index, const nb::System::String &sSource)
{
	m_ImageItemManager.Insert(index, sSource);
}

void ImagePool_Internal::RemoveSource(int index)
{
	m_ImageItemManager.Remove(index);
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, index);
}

void ImagePool_Internal::UpdateSourceAt(int index, const nb::System::String &sSource)
{
	m_ImageItemManager.SetSourceAt(index, sSource);
}

void ImagePool_Internal::GetSourceFileList(ImageSources &ret) const
{
	m_ImageItemManager.GetSourceFiles(ret);
}

nb::System::String ImagePool_Internal::GetSourceAt(int index) const
{
	return m_ImageItemManager.GetSourceAt(index);
}

int ImagePool_Internal::GetSourceFileCount() const
{
	return m_ImageItemManager.GetCount();
}

void ImagePool_Internal::SetSentry(int sentry)
{
	m_nSentry = sentry;
}

int ImagePool_Internal::GetSentry() const
{
	int ret = nb::System::Bound(0, GetSourceFileCount(), m_nSentry);
	return ret;
}

void ImagePool_Internal::StartLoading()
{
	if(IsWorking())
		return;

	m_bStopFlag = false;
	nb::System::Thread::Start();
}

void ImagePool_Internal::StopLoading(bool bClear)
{
	if(!IsWorking())
		return;

	m_bStopFlag = true;
	if(bClear)
		Clear();
}

bool ImagePool_Internal::IsWorking() const
{
	return m_bStopFlag;
}

bool ImagePool_Internal::GetImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty)
{
	if(m_ImageItemManager.TryLockOne(index))
	{
		ImageItem *item = m_ImageItemManager.GetItemAt(index);
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
		itemProperty.m_SourcePath = m_ImageItemManager.GetSourceAt(index);
		}
		catch(nb::Core::ExceptionPtr &e){(void)e;}
		itemProperty.m_Bitmap = NULL;
		itemProperty.m_Loaded = false;
		itemProperty.m_Error = false;
		itemProperty.m_OriginalSize = nb::System::SizeI(0, 0);
		return false;
	}
}

void ImagePool_Internal::GetImageItemPropertyUnlock(int index)
{
	m_ImageItemManager.UnlockOne(index);
}

nb::System::SizeI ImagePool_Internal::GetScaleSize() const
{
	nb::System::SizeI sz = m_ImgReader.GetScaledSize();
	return sz;
}

void ImagePool_Internal::SetListener(ImagePoolEvent *p)
{
	m_pEventInterface = p;
}

ImagePoolEvent *ImagePool_Internal::GetListener() const
{
	return m_pEventInterface;
}

void ImagePool_Internal::Clear()
{
	m_ImageItemManager.Clear();
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, -1);
}

int ImagePool_Internal::CalcNextLoadIndex(int &nNewCacheRangeBeg, int &nNewCacheRangeEnd) const
{
	int nRet = -1;
	ImagePool::LoadingDirection direction = GetLoadingDirection();
	if(direction == ImagePool::Direction_Forward)
	{
		//正序找未加载的下标
		nNewCacheRangeEnd = GetSentry() + m_Cache.m_Size;
		if(nNewCacheRangeEnd >= GetSourceFileCount())
			nNewCacheRangeEnd = GetSourceFileCount();
		for(int i = GetSentry(); i < nNewCacheRangeEnd; ++i)
		{
			if(m_ImageItemManager.HasImageLoaded(i) == false)
			{
				nRet = i;
				break;
			}
		}

		int nReverseStart = GetSentry() - 1;
		nNewCacheRangeBeg = nNewCacheRangeEnd - GetCache().m_Size - 1;
		//如果正序未找到，表明到尾部，从哨岗处往回找
		if(nRet == -1 && nReverseStart >= 0)
		{
			for(int i = nReverseStart; i > nNewCacheRangeBeg; --i)
			{
				if(m_ImageItemManager.HasImageLoaded(i) == false)
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
		int nCacheRangeSize = nb::System::Min(GetCache().m_Size, GetSourceFileCount());
		nNewCacheRangeBeg = GetSentry() - nCacheRangeSize / 2;
		nNewCacheRangeEnd = nNewCacheRangeBeg + nCacheRangeSize - 1;
		if(nNewCacheRangeBeg < 0)
		{
			nNewCacheRangeEnd += nb::System::Abs(nNewCacheRangeBeg);
			nNewCacheRangeBeg = 0;
		}
		else if(nNewCacheRangeEnd >= GetSourceFileCount())
		{
			nNewCacheRangeBeg -= (nNewCacheRangeEnd - GetSourceFileCount() + 1);
			nNewCacheRangeEnd = GetSourceFileCount() - 1;
		}

		//取最近的还没被加载的下标
		for(int i = 0; i <= nCacheRangeSize * 2; ++i)
		{
			int offset = (i / 2) * (i % 2 ? 1 : -1);
			int index = GetSentry() + offset;
			if(index >= nNewCacheRangeBeg && index <= nNewCacheRangeEnd && m_ImageItemManager.HasImageLoaded(index) == false
				/*&& Singleton<SharedPathsManager>::Current()->IsSourcePathLocked(m_ImageItems[index]->m_Source) == false*/)
			{
				nRet = index;
				break;
			}
		}
	}
	return nRet;
}

int ImagePool_Internal::CalcFarestLoadedIndex(int nNewCacheRangeBeg, int nNewCacheRangeEnd) const
{
	std::vector<int> loadedIndices;
	m_ImageItemManager.GetLoadedItems(loadedIndices);
	if(loadedIndices.empty())	
		return -1;

	int nFarestIndex = loadedIndices[0];
	int distanceMax = nb::System::DistanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, nFarestIndex);
	for(int i = 0; i != loadedIndices.size(); ++i)
	{
		int n = loadedIndices[i];
		int distance = nb::System::DistanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, n);
		if(distance > distanceMax)
		{
			nFarestIndex = n;
			distanceMax = distance;
		}
	}
	if(nb::System::DistanceFromArea(nNewCacheRangeBeg + 1, nNewCacheRangeEnd - 1, nFarestIndex) == 0)
		nFarestIndex = -1;
	return nFarestIndex;
}

int ImagePool_Internal::GetLoadedBytes() const
{
	return m_ImageItemManager.GetLoadedBytes();
}

bool ImagePool_Internal::IsCacheFull() const
{
	std::vector<int> loadedIndices;
	m_ImageItemManager.GetLoadedItems(loadedIndices);
	bool b = (m_Cache.m_Mode == ImagePool::Cache::CacheMode_Count_Limit && loadedIndices.size() >= (unsigned int)m_Cache.m_Size) || (m_Cache.m_Mode == ImagePool::Cache::CacheMode_Bytes_Limit && GetLoadedBytes() >= m_Cache.m_Size);
	return b;
}

void ImagePool_Internal::Run()
{
	if(m_pEventInterface)
		m_pEventInterface->ImagePool_OnLoading_Start(m_pOwner);

	try{
	while(true)
	{
		//计算下一次加载的下标和缓存区域
		int nNewCacheRangeBeg, nNewCacheRangeEnd;
		int nNextIndex = CalcNextLoadIndex(nNewCacheRangeBeg, nNewCacheRangeEnd);
		//如果有可加载的下标
		if(nNextIndex == -1)
		{
			if(m_pEventInterface)
				m_pEventInterface->ImagePool_OnLoading_Idled(m_pOwner);

			MSleep(10);
			continue;
		}
		else
		{
			//如果原缓存已满且，需释放一个离区域最远的图片
			if(IsCacheFull())
			{
				int nFarestIndex = CalcFarestLoadedIndex(nNewCacheRangeBeg, nNewCacheRangeEnd);
				if(nFarestIndex != -1)
				{
					if(m_ImageItemManager.TryLockOne(nFarestIndex))
					{
						m_ImageItemManager.EraseLoaded(nFarestIndex);
						m_ImageItemManager.UnlockOne(nFarestIndex);
						if(m_pEventInterface)
							m_pEventInterface->ImagePool_OnImage_Released(m_pOwner, nFarestIndex);
					}
				}
			}

			UInt64 tickBeg = nb::System::Platform::GetTickCount();
			if(m_ImageItemManager.TryLockOne(nNextIndex) == false)	continue;		//如果尝试锁失败表面外部正在锁定图片，则不加载

			nb::System::String path = m_ImageItemManager.GetSourceAt(nNextIndex);
			if(Singleton<SharedPathsManager>::Current()->TryLockSourcePath(path))	//如果尝试锁失败，则表示该路径已经在读取当中
			{
				if(m_FilterManager.TestSuffixAndBytesLimit(path) == false)
				{
					m_ImageItemManager.MarkLoaded(nNextIndex, NULL, true, nb::System::SizeI(0, 0));
				}
				else
				{
					Bitmap *pBm = new Bitmap();
					nb::System::SizeI sz;
					m_ImgReader.ReadUniform(path, pBm, sz);
					m_ImageItemManager.MarkLoaded(nNextIndex, pBm, !(pBm->HasPixelData()), sz);
				}
				Singleton<SharedPathsManager>::Current()->UnlockSourcePath(path);
				m_ImageItemManager.UnlockOne(nNextIndex);	//解锁该图片

				UInt64 tickEnd = nb::System::Platform::GetTickCount();
				if(m_pEventInterface)
					m_pEventInterface->ImagePool_OnImage_Loaded(m_pOwner, nNextIndex, (int)(tickEnd - tickBeg));
			}
			else
			{
				m_ImageItemManager.UnlockOne(nNextIndex);	//解锁该图片
			}

		}

		MSleep(1);
	}
	}
	catch(nb::Core::ExceptionPtr ex){
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n\r\n");
		printf("exception: %s\r\n", ex->GetErrorMessageData());
		printf("file: %s\r\n", ex->GetFileNameData());
		printf("line: %d\r\n\r\n", ex->GetFileLine());
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
	Clear();
}

void ImagePool_Internal::ImageItemManager::SetSourceFiles(const ImageSources &filePaths)
{
	m_Lock.Lock();
	Clear();
	for(int i = 0; i != filePaths.GetCount(); ++i)
	{
		m_ImageItems.push_back(new ImageItem(filePaths[i]));
		Singleton<SharedPathsManager>::Current()->RequestSourcePath(filePaths[i]);
	}
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::GetSourceFiles(ImageSources &ret) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	for(int i = 0; i != m_ImageItems.size(); ++i)
		ret.PushBack(m_ImageItems[i]->m_Source);
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::SetSourceAt(int index, const nb::System::String &path)
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
	m_ImageItems[index]->m_OriginalSize = nb::System::SizeI(0, 0);
	std::vector<int>::iterator iter = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index);
	if(iter != m_LoadedIndices.end())	m_LoadedIndices.erase(iter);
	m_Lock.Unlock();
}

nb::System::String ImagePool_Internal::ImageItemManager::GetSourceAt(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
		NB_THROW_EXCEPTION("index over flow");
	}
	nb::System::String sRet = m_ImageItems[index]->m_Source;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return sRet;
}

ImagePool_Internal::ImageItem *ImagePool_Internal::ImageItemManager::GetItemAt(int index) const
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

void ImagePool_Internal::ImageItemManager::Push(const nb::System::String &path)
{
	m_Lock.Lock();
	m_ImageItems.push_back(new ImageItem(path));
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::Insert(int index, const nb::System::String &path)
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

void ImagePool_Internal::ImageItemManager::Remove(int index)
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

void ImagePool_Internal::ImageItemManager::EraseLoaded(int index)
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
	m_ImageItems[index]->m_OriginalSize = nb::System::SizeI(0, 0);
	std::vector<int>::iterator iter = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index);
	if(iter != m_LoadedIndices.end()) m_LoadedIndices.erase(iter);
	m_Lock.Unlock();
}

int ImagePool_Internal::ImageItemManager::GetCount() const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	int nRet = (int)m_ImageItems.size();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return nRet;
}

void ImagePool_Internal::ImageItemManager::Clear()
{
	m_Lock.Lock();
	for(int i = 0; i != m_ImageItems.size(); ++i)
	{
		Singleton<SharedPathsManager>::Current()->RemoveRef(m_ImageItems[i]->m_Source);
		delete m_ImageItems[i]->m_Bm;
		delete m_ImageItems[i];
	}
	m_ImageItems.clear();
	m_LoadedIndices.clear();
	m_Lock.Unlock();
}

void ImagePool_Internal::ImageItemManager::GetLoadedItems(std::vector<int> &loadedIndices) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	loadedIndices = m_LoadedIndices;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
}

bool ImagePool_Internal::ImageItemManager::HasImageLoaded(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	bool b = std::find(m_LoadedIndices.begin(), m_LoadedIndices.end(), index) != m_LoadedIndices.end();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return b;
}

int ImagePool_Internal::ImageItemManager::GetLoadedBytes() const
{
	int nRet = 0;
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	for(int i = 0; i != m_LoadedIndices.size(); ++i)
			nRet += m_ImageItems[m_LoadedIndices[i]]->m_Bm->GetBytesCount();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return nRet;
}

void ImagePool_Internal::ImageItemManager::MarkLoaded(int index, Bitmap *bm, bool bError, const nb::System::SizeI &originalSize)
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

bool ImagePool_Internal::ImageItemManager::TryLockOne(int index)
{
	m_Lock.Lock();
	if((index < 0 || index >= (int)m_ImageItems.size()) || (m_ImageItems[index]->IsLocked()))
	{
		m_Lock.Unlock();
		return false;
	}

	m_ImageItems[index]->Lock();
	m_Lock.Unlock();
	return true;
}

void ImagePool_Internal::ImageItemManager::UnlockOne(int index)
{
	m_Lock.Lock();
	if(index < 0 || index >= (int)m_ImageItems.size())
	{
		m_Lock.Unlock();
		return;
	}
	m_ImageItems[index]->Unlock();
	m_Lock.Unlock();
}

bool ImagePool_Internal::ImageItemManager::IsLocked(int index) const
{
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Lock();
	bool b = m_ImageItems[index]->IsLocked();
	const_cast<ImagePool_Internal::ImageItemManager *>(this)->m_Lock.Unlock();
	return b;
}

////////////////////
ImagePool_Internal::FilterItemManager::~FilterItemManager()
{
	Clear();
}

void ImagePool_Internal::FilterItemManager::SetFilter(nb::System::EnumFlags<ImagePool::FileType> flags)
{
	m_Lock.Lock();
	Clear();
	if(flags.TestFlag(ImagePool::FileType_Bmp))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("bmp");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Bmp, suffixs));
	}
	if(flags.TestFlag(ImagePool::FileType_Jpeg))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("jpg");
		suffixs.push_back("jpeg");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Jpeg, suffixs));
	}
	if(flags.TestFlag(ImagePool::FileType_Png))
	{
		std::vector<std::string> suffixs;
		suffixs.push_back("png");
		m_Filters.push_back(new ImagePool_Internal::FilterItemProperty(ImagePool::FileType_Jpeg, suffixs));
	}
	m_Lock.Unlock();
}

nb::System::EnumFlags<ImagePool::FileType> ImagePool_Internal::FilterItemManager::GetFilter() const
{
	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Lock();
	nb::System::EnumFlags<ImagePool::FileType> filter;
	for(int i = 0; i != m_Filters.size(); ++i)
		filter |= m_Filters[i]->m_FileType;
	const_cast<ImagePool_Internal::FilterItemManager *>(this)->m_Lock.Unlock();
	return filter;
}

void ImagePool_Internal::FilterItemManager::SetBytesLimit(ImagePool::FileType type, int bytesLimit)
{
	m_Lock.Lock();
	for(int i = 0; i != m_Filters.size(); ++i)
	{
		if(m_Filters[i]->m_FileType == type)
			m_Filters[i]->m_BytesLimit = bytesLimit;
	}
	m_Lock.Unlock();
}

void ImagePool_Internal::FilterItemManager::SetBytesLimitAllType(int bytesLimit)
{
	m_Lock.Lock();
	SetBytesLimit(ImagePool::FileType_Bmp, bytesLimit);
	SetBytesLimit(ImagePool::FileType_Jpeg, bytesLimit);
	SetBytesLimit(ImagePool::FileType_Png, bytesLimit);
	m_Lock.Unlock();
}

bool ImagePool_Internal::FilterItemManager::TestSuffixAndBytesLimit(const nb::System::String &path) const
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
			nb::System::String sOne = m_Filters[i]->m_Suffixs[j].data();
			if(nb::System::String(suffix.data()).ToLower() == sOne.ToLower())
			{
				nb::System::File file(path);
				file.Open(nb::System::File::OpenExistsOnly, nb::System::File::Read);
				if(file.IsOpened() && file.GetLenght() < (UInt64)(m_Filters[i]->m_BytesLimit))
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

void ImagePool_Internal::FilterItemManager::Clear()
{
	m_Lock.Lock();
	for(int i = 0; i != m_Filters.size(); ++i)
		delete m_Filters[i];
	m_Filters.clear();
	m_Lock.Unlock();
}

//////////////////////
void ImagePool_Internal::SharedPathsManager::RequestSourcePath(const nb::System::String &path)
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
		const_cast<ImagePool_Internal::SharedPathItem &>(x).AddRef();
	}
	g_Lock.Unlock();
}

void ImagePool_Internal::SharedPathsManager::RemoveRef(const nb::System::String &path)
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		const_cast<ImagePool_Internal::SharedPathItem &>(x).SubRef();
		if((*iter).GetRef() <= 0)
			m_SourcePaths.erase(iter);
	}
	g_Lock.Unlock();
}

bool ImagePool_Internal::SharedPathsManager::TryLockSourcePath(const nb::System::String &path) 
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		if(x.IsLocked() == false)
		{
			const_cast<ImagePool_Internal::SharedPathItem &>(x).Lock();
			g_Lock.Unlock();
			return true;
		}
	}
	g_Lock.Unlock();
	return false;
}

void ImagePool_Internal::SharedPathsManager::UnlockSourcePath(const nb::System::String &path)
{
	g_Lock.Lock();
	std::set<ImagePool_Internal::SharedPathItem>::iterator iter = m_SourcePaths.find(path);
	if(iter != m_SourcePaths.end())
	{
		const ImagePool_Internal::SharedPathItem &x = *iter;
		const_cast<ImagePool_Internal::SharedPathItem &>(x).Unlock();
	}
	g_Lock.Unlock();
}
