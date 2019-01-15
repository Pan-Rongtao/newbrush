#pragma once
#include <vector>
#include "../core/Size.h"
#include "../core/String.h"
#include "../core/EnumFlags.h"
#include "ImageSources.h"

namespace nb{ namespace media {

class ImagePool_Internal;
class ImagePoolEvent;
class Bitmap;
class NB_API ImagePool
{
public:

	//文件过滤器
	enum FileType
	{
		FileType_Unknown	= 0x00000001,	//未知
		FileType_Jpeg		= 0x00000002,	//JPEG
		FileType_Bmp		= 0x00000004,	//BMP
		FileType_Png		= 0x00000008,	//PNG
		FileType_Gif		= 0x00000010,	//GIF
		FileType_Reserve	= 0x80000000,	//预留
	};

	//加载方向
	enum LoadingDirection
	{
		Direction_Forward,					//向前
		Direction_Backward,					//向后
		Direction_Radiant,					//辐射
	};

	struct ImageItemProperty
	{
		nb::core::String	m_SourcePath;	//源路径
		bool				m_Loaded;		//是否已经加载
		bool				m_Error;		//是否是错误图片
		nb::core::SizeI		m_OriginalSize;	//图片的原尺寸
		Bitmap				*m_Bitmap;		//实际Bitmap
	};

	struct Cache
	{
		//缓存模式
		enum CacheMode
		{
			CacheMode_Count_Limit,			//个数限制
			CacheMode_Bytes_Limit,			//字节限制
		};
		Cache(CacheMode mode, int size) : m_Mode(mode), m_Size(size) {}

		CacheMode			m_Mode;
		int					m_Size;
	};

public:
	//构建一个图片池
	//scale尺寸为	160x160
	//采用CacheMode_Count_Limit的缓存模式，缓存大小为不限制
	//文件过滤器为	JPG|BMP|PNG
	//加载方向为	Direction_Radiant
	//它的源是空的
	ImagePool();

	//构建一个图片池
	//scale尺寸为	scaleSize
	//采用CacheMode_Count_Limit的缓存模式，缓存大小为不限制
	//文件过滤器为	JPG|BMP|PNG
	//加载方向为	Direction_Radiant
	//它的源是空的
	ImagePool(const nb::core::SizeI &scaleSize);


	//构建一个图片池
	//scale尺寸为	160x160
	//采用CacheMode_Count_Limit的缓存模式，缓存大小为cacheSize
	//文件过滤器为	JPG|BMP|PNG
	//加载方向为	Direction_Radiant
	//它的源是空的
	ImagePool(const nb::core::SizeI &scaleSize, ImagePool::Cache cache);

	//构建一个图片池
	//scale尺寸为	scaleSize
	//采用mode缓存模式，缓存大小为cacheSize
	//文件过滤器为	flags
	//加载方向为	direction
	//它的源是空的
	ImagePool(const nb::core::SizeI &scaleSize, ImagePool::Cache cache, const nb::core::EnumFlags<ImagePool::FileType> &flags, ImagePool::LoadingDirection direction);

	~ImagePool();

public:
	//设置缓存
	void setCache(ImagePool::Cache cache);

	//获取缓存
	ImagePool::Cache cache() const;

	//设置过滤器，过滤器中的文件类型才被加载
	void setFilter(const nb::core::EnumFlags<ImagePool::FileType> &flags);

	//获取过滤器
	nb::core::EnumFlags<ImagePool::FileType> filter() const;

	//限制某种图片格式的文件大小为bytesLimit，超过将判定为错误图片
	void setImageMemoryLimit(ImagePool::FileType type, int bytesLimit);
	//限制所有图片格式的文件大小bytesLimit，超过将判定为错误图片
	void setImageMemoryLimitAllType(int bytesLimit);

	//设置加载方向
	void setLoadingDirection(ImagePool::LoadingDirection direction);
	
	//获取加载方向
	ImagePool::LoadingDirection loadingDirection() const;

	//设置图片文件列表源，图片池中的原数据将被清空；假设当前的正在加载图片，则继续从哨岗处加载
	//void SetSourceFiles(const std::vector<nb::System::String> &vtFilePaths);
	void setSourceFiles(const ImageSources &filePaths);

	//追加一个源文件
	void appendSource(const nb::core::String &sSource);

	//插入一个源文件
	//异常：index溢出
	void insertSource(int index, const nb::core::String &sSource);

	//移除一个源文件
	void removeSource(int index);

	//更新一个Source
	//异常：index溢出
	void updateSourceAt(int index, const nb::core::String &sSource);

	//获取图片文件列表
	void getSourceFileList(ImageSources &ret) const;

	//获取下标为index的源
	//异常：index溢出
	nb::core::String sourceAt(int index) const;

	//获取源图片文件个数
	int sourceFileCount() const;

	//设置岗哨，岗哨的意义在于下一次加载的图片位置，并按照当前的缓存大小等信息规则释放某些已加载图片缓存
	//sentry会采用就近可用原则，比如当sentry不在控制范围内，选取最近的可用下标作为岗哨
	void setSentry(int sentry);

	//获取岗哨位置
	int sentry() const;

	//开始加载
	void startLoading();

	//停止加载，停止加载将删除图片池中的所有图片
	//bClear：是否清除缓存
	void stopLoading(bool bClear);

	//是否在工作
	bool isWorking() const;

	//获取已加载图片个数（包含错误图片）
	//int GetLoadedCount() const;

	//获取下标为index的图片属性并加锁，此函数必须与GetImageItemPropertyUnlock配套使用，否则可能产生死锁
	//异常：index溢出
	bool getImageItemPropertyAndLock(int index, ImageItemProperty &itemProperty);
	//获取图片属性解锁解锁，注意！！！如果GetImageItemPropertyAndLock返回false，则不应该调用
	void getImageItemPropertyUnlock(int index);

	//获取scale尺寸
	nb::core::SizeI scaleSize() const;

	//设置消息监听
	void setListener(ImagePoolEvent *p);
	ImagePoolEvent *getListener() const;

private:
	ImagePool(const ImagePool &other);
	void operator = (const ImagePool &other);

	ImagePool_Internal		*m_pInternal;
};

//消息由线程发出，请注意！！！！！
class NB_API ImagePoolEvent
{
public:
	//开始加载
	virtual void ImagePool_OnLoading_Start(ImagePool *sender)											{}

	//空闲，当图片池加载完毕所有的缓存后就会处于空闲状态
	virtual void ImagePool_OnLoading_Idled(ImagePool *sender)											{}

	//一张图片加载完成，millisecond：加载时长；bSccess：是否加载成功
	virtual void ImagePool_OnImage_Loaded(ImagePool *sender, int index, int millisecond)	{}

	//一张图片被销毁了
	virtual void ImagePool_OnImage_Released(ImagePool *sender, int index)								{}

};

}}
