#pragma once
#include <vector>
#include <set>
#include "system/EnumFlags.h"
#include "system/String.h"
#include "system/Thread.h"
#include "system/CriticalSection.h"
#include "media/Bitmap.h"
#include "media/ImagePool.h"
#include "media/ImageReader.h"
#include "core/Exception.h"

namespace nb { namespace Media {

class ImagePool_Internal : public nb::System::Thread
{
public:
	ImagePool_Internal(ImagePool *pOwner, const nb::System::SizeI &scaleSize);
	~ImagePool_Internal();

	void SetCache(ImagePool::Cache cache);

	ImagePool::Cache GetCache() const;

	void SetFilter(nb::System::EnumFlags<nb::Media::ImagePool::FileType> flags);

	nb::System::EnumFlags<nb::Media::ImagePool::FileType> GetFilter() const;

	void SetImageMemoryLimit(nb::Media::ImagePool::FileType type, int bytesLimit);

	void SetImageMemoryLimitAllType(int bytesLimit);

	void SetLoadingDirection(ImagePool::LoadingDirection direction);

	ImagePool::LoadingDirection GetLoadingDirection() const;

	void SetSourceFiles(const ImageSources &filePaths);

	void AppendSource(const nb::System::String &sSource);

	void InsertSource(int index, const nb::System::String &sSource);

	void RemoveSource(int index);

	void UpdateSourceAt(int index, const nb::System::String &sSource);

	void GetSourceFileList(ImageSources &ret) const;

	nb::System::String GetSourceAt(int index) const;

	int GetSourceFileCount() const;

	void SetSentry(int sentry);

	int GetSentry() const;

	void StartLoading();

	void StopLoading(bool bClear);

	bool IsWorking() const;

	bool HasImageLoaded(int index) const;

	bool GetImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty);

	void GetImageItemPropertyUnlock(int index);

	nb::System::SizeI GetScaleSize() const;

	void SetListener(ImagePoolEvent *p);
	ImagePoolEvent *GetListener() const;

protected:
	virtual void Run();

private:
	struct FilterItemProperty
	{
		FilterItemProperty(ImagePool::FileType type, const std::vector<std::string> &suffixs) : m_FileType(type), m_Suffixs(suffixs), m_BytesLimit(-1) {}
		ImagePool::FileType			m_FileType;
		std::vector<std::string>	m_Suffixs;
		int							m_BytesLimit;
	};
	class FilterItemManager
	{
	public:
		void SetFilter(nb::System::EnumFlags<ImagePool::FileType> flags);
		nb::System::EnumFlags<ImagePool::FileType> GetFilter() const;
		void SetBytesLimit(ImagePool::FileType type, int bytesLimit);
		void SetBytesLimitAllType(int bytesLimit);
		bool TestSuffixAndBytesLimit(const nb::System::String &path) const;
		~FilterItemManager();

	private:
		void Clear();
		std::string GetSuffix(const std::string &s) const;

		std::vector<FilterItemProperty *>		m_Filters;
		nb::System::CriticalSection				m_Lock;
	};
	/////////////////////////////
	class ImageItem
	{
	public:
		ImageItem(const nb::System::String &source) : m_Source(source), m_Bm(NULL), m_bError(false), m_bLock(false) {}

		void Lock()		{m_bLock = true; m_Lock.Lock();}
		void Unlock()	{m_bLock = false; m_Lock.Unlock();}
		bool IsLocked() {return m_bLock;}

		nb::System::String			m_Source;
		Bitmap						*m_Bm;
		bool						m_bError;
		nb::System::SizeI			m_OriginalSize;
		bool						m_bLock;
		nb::System::CriticalSection m_Lock;
	};
	class ImageItemManager
	{
	public:
		bool CheckIndex(int index) const;
		void SetSourceFiles(const ImageSources &filePaths);
		void GetSourceFiles(ImageSources &ret) const;
		void SetSourceAt(int index, const nb::System::String &path);
		nb::System::String GetSourceAt(int index) const;
		ImageItem *GetItemAt(int index) const;
		void Push(const nb::System::String &path);
		void Insert(int index, const nb::System::String &path);
		void Remove(int index);
		void EraseLoaded(int index);
		int GetCount() const;
		void Clear();
		void GetLoadedItems(std::vector<int> &loadedIndices) const;
		bool HasImageLoaded(int index) const;
		int GetLoadedBytes() const;
		void MarkLoaded(int index, Bitmap *bm, bool bError, const nb::System::SizeI &originalSize);
		bool TryLockOne(int index);
		void UnlockOne(int index);
		bool IsLocked(int index) const;

		~ImageItemManager();

	private:
		std::vector<ImageItem *>		m_ImageItems;
		std::vector<int>				m_LoadedIndices;
		nb::System::CriticalSection		m_Lock;
	};

	class SharedPathItem
	{
	public:
		SharedPathItem(const nb::System::String &path) : m_Path(path), m_bLocked(false), m_nRefCount(1) {}

		void Lock()				{m_bLocked = true;}
		void Unlock()			{m_bLocked = false;}
		bool IsLocked() const	{return m_bLocked;}
		void AddRef()			{m_nRefCount++;}
		void SubRef()			{m_nRefCount--;}
		int GetRef() const		{return m_nRefCount;}

		bool operator < (const SharedPathItem &other) const {return m_Path < other.m_Path;}
	private:
		nb::System::String	m_Path;
		bool				m_bLocked;
		int					m_nRefCount;
	};
	class SharedPathsManager
	{
	public:
		void RequestSourcePath(const nb::System::String &path);
		void RemoveRef(const nb::System::String &path);
		bool TryLockSourcePath(const nb::System::String &path);
		void UnlockSourcePath(const nb::System::String &path);

	private:
		std::set<SharedPathItem>			m_SourcePaths;
		static nb::System::CriticalSection	g_Lock;
	};

	ImagePool_Internal(const ImagePool_Internal &other) : m_Cache(ImagePool::Cache::CacheMode_Count_Limit, -1) {}
	void operator = (const ImagePool_Internal &other)	{}

	void Clear();
	int CalcNextLoadIndex(int &nNewCacheRangeBeg, int &nNewCacheRangeEnd) const;
	int CalcFarestLoadedIndex(int nNewCacheRangeBeg, int nNewCacheRangeEnd) const;
	int GetLoadedBytes() const;
	bool IsCacheFull() const;

	bool										m_bStopFlag;
	ImagePool::Cache							m_Cache;
	ImagePool::LoadingDirection					m_LoadingDirection;
	int											m_nSentry;

	FilterItemManager							m_FilterManager;
	ImageItemManager							m_ImageItemManager;

	ImageReader									m_ImgReader;
	ImagePoolEvent								*m_pEventInterface;
	ImagePool									*m_pOwner;
	nb::System::CriticalSection					m_Lock;
};

}}
