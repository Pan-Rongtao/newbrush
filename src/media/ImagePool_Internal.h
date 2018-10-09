#pragma once
#include <vector>
#include <set>
#include "core/EnumFlags.h"
#include "core/String.h"
#include "system/Thread.h"
#include "system/CriticalSection.h"
#include "media/Bitmap.h"
#include "media/ImagePool.h"
#include "media/ImageReader.h"
#include "core/Exception.h"

namespace nb { namespace media {

class ImagePool_Internal : public nb::System::Thread
{
public:
	ImagePool_Internal(ImagePool *pOwner, const nb::core::SizeI &scaleSize);
	~ImagePool_Internal();

	void setCache(ImagePool::Cache cache);

	ImagePool::Cache cache() const;

	void setFilter(nb::core::EnumFlags<ImagePool::FileType> flags);

	nb::core::EnumFlags<ImagePool::FileType> filter() const;

	void setImageMemoryLimit(ImagePool::FileType type, int bytesLimit);

	void setImageMemoryLimitAllType(int bytesLimit);

	void setLoadingDirection(ImagePool::LoadingDirection direction);

	ImagePool::LoadingDirection loadingDirection() const;

	void setSourceFiles(const ImageSources &filePaths);

	void appendSource(const nb::core::String &sSource);

	void insertSource(int index, const nb::core::String &sSource);

	void removeSource(int index);

	void updateSourceAt(int index, const nb::core::String &sSource);

	void getSourceFileList(ImageSources &ret) const;

	nb::core::String sourceAt(int index) const;

	int sourceFileCount() const;

	void setSentry(int sentry);

	int sentry() const;

	void startLoading();

	void stopLoading(bool bClear);

	bool isWorking() const;

	bool getImageItemPropertyAndLock(int index, ImagePool::ImageItemProperty &itemProperty);

	void getImageItemPropertyUnlock(int index);

	nb::core::SizeI scaleSize() const;

	void setListener(ImagePoolEvent *p);
	ImagePoolEvent *getListener() const;

protected:
	virtual void run() override;

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
		void SetFilter(nb::core::EnumFlags<ImagePool::FileType> flags);
		nb::core::EnumFlags<ImagePool::FileType> filter() const;
		void setBytesLimit(ImagePool::FileType type, int bytesLimit);
		void setBytesLimitAllType(int bytesLimit);
		bool testSuffixAndBytesLimit(const nb::core::String &path) const;
		~FilterItemManager();

	private:
		void clear();
		std::string getSuffix(const std::string &s) const;

		std::vector<FilterItemProperty *>		m_Filters;
		nb::System::CriticalSection				m_Lock;
	};
	/////////////////////////////
	class ImageItem
	{
	public:
		ImageItem(const nb::core::String &source) : m_Source(source), m_Bm(NULL), m_bError(false), m_bLock(false) {}

		void lock()		{m_bLock = true; m_Lock.Lock();}
		void unlock()	{m_bLock = false; m_Lock.Unlock();}
		bool isLocked() {return m_bLock;}

		nb::core::String			m_Source;
		Bitmap						*m_Bm;
		bool						m_bError;
		nb::core::SizeI				m_OriginalSize;
		bool						m_bLock;
		nb::System::CriticalSection m_Lock;
	};
	class ImageItemManager
	{
	public:
		void setSourceFiles(const ImageSources &filePaths);
		void getSourceFiles(ImageSources &ret) const;
		void setSourceAt(int index, const nb::core::String &path);
		nb::core::String sourceAt(int index) const;
		ImageItem *itemAt(int index) const;
		void push(const nb::core::String &path);
		void insert(int index, const nb::core::String &path);
		void remove(int index);
		void eraseLoaded(int index);
		int count() const;
		void clear();
		void getLoadedItems(std::vector<int> &loadedIndices) const;
		bool hasImageLoaded(int index) const;
		int loadedBytes() const;
		void markLoaded(int index, Bitmap *bm, bool bError, const nb::core::SizeI &originalSize);
		bool tryLockOne(int index);
		void unlockOne(int index);
		bool isLocked(int index) const;

		~ImageItemManager();

	private:
		std::vector<ImageItem *>		m_ImageItems;
		std::vector<int>				m_LoadedIndices;
		nb::System::CriticalSection		m_Lock;
	};

	class SharedPathItem
	{
	public:
		SharedPathItem(const nb::core::String &path) : m_Path(path), m_bLocked(false), m_nRefCount(1) {}

		void lock()				{m_bLocked = true;}
		void unlock()			{m_bLocked = false;}
		bool isLocked() const	{return m_bLocked;}
		void addRef()			{m_nRefCount++;}
		void subRef()			{m_nRefCount--;}
		int ref() const		{return m_nRefCount;}

		bool operator < (const SharedPathItem &other) const {return m_Path < other.m_Path;}
	private:
		nb::core::String	m_Path;
		bool				m_bLocked;
		int					m_nRefCount;
	};
	class SharedPathsManager
	{
	public:
		void requestSourcePath(const nb::core::String &path);
		void removeRef(const nb::core::String &path);
		bool tryLockSourcePath(const nb::core::String &path);
		void unlockSourcePath(const nb::core::String &path);

	private:
		std::set<SharedPathItem>			m_SourcePaths;
		static nb::System::CriticalSection	g_Lock;
	};

	ImagePool_Internal(const ImagePool_Internal &other) : m_Cache(ImagePool::Cache::CacheMode_Count_Limit, -1) {}
	void operator = (const ImagePool_Internal &other)	{}

	void clear();
	int calcNextLoadIndex(int &nNewCacheRangeBeg, int &nNewCacheRangeEnd) const;
	int calcFarestLoadedIndex(int nNewCacheRangeBeg, int nNewCacheRangeEnd) const;
	int loadedBytes() const;
	bool isCacheFull() const;

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
