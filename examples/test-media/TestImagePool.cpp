#include "TestImagePool.h"
#include "media/Bitmap.h"
#include "core/Random.h"

using namespace nb::core;
using namespace nb::media;

void TestImagePool::PrintAll(ImagePool *p, bool bRelease)
{
	printf("##########################################\r\n");
	std::string sInfo;
	char arr[80] = {0};
	sprintf(arr, "[%p]", p);
	std::string s1 = arr + std::string(" ########################################## 1111\r\n");
	std::string s2 = arr + std::string(" ########################################## 2222\r\n");
//	OutputDebugStringA(s1.data());
	int count = p->sourceFileCount();
	for(int i = 0; i != count; ++i)
	{
	//	sprintf(arr, "[%p]--%d/%d:", p, i, count);
	//	std::string s1 = arr + std::string(" GetImageItemPropertyAndLock 1111\r\n");
	//	std::string s2 = arr + std::string(" GetImageItemPropertyUnlock 2222\r\n");
	//	OutputDebugStringA(s1.data());
		ImagePool::ImageItemProperty item;
		bool bLock = p->getImageItemPropertyAndLock(i, item);
		if(item.m_Loaded)
		{
			if(!item.m_Error)
				sInfo = sInfo + std::string("1") + ' ';
			else
				sInfo = sInfo+ std::string("2") + ' ';
		}
		else
		{
			sInfo = sInfo + std::string("0") + ' ';
		}
		if(bLock)
			p->getImageItemPropertyUnlock(i);
//		OutputDebugStringA(s2.data());
	}
	printf("[%p]%s\r\n", p, sInfo.data());

//	OutputDebugStringA(s2.data());
	printf("##########################################\r\n");
//	Random rd(0, 100);
//	m_imgPool1.SetSentry(rd.GetOne());
//	m_imgPool2.SetSentry(rd.GetOne());

}

TestImagePool::TestImagePool()
: m_imgPool1(SizeI(200, 200))
, m_imgPool2(SizeI(1280, 720))
{
}


void TestImagePool::Reset(ImagePool *p, int beg, int end)
{
	char arr1[80] = {0};
	char arr2[80] = {0};
	sprintf(arr1, "[%p]", &m_imgPool1);
	sprintf(arr2, "[%p]", &m_imgPool2);
	ImageSources vtImgs;
	for(int i = beg; i != end; ++i)
	{
		char arr[10] = {0};
		sprintf(arr, "%d", i);
		std::string s;
#ifdef WIN32
		s = std::string("e:/Pics/") + arr + ".jpg";
		//s = std::string("f:/xxx/") + arr + ".jpg";
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)
		s = std::string("Pics/NoThumbJPG/") + arr + ".jpg";
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)
		s = std::string("/home/ubuntu/NoThumbJPG/") + arr + ".jpg";
#endif
		vtImgs.pushBack(s.data());
	}
	//	vtImgs.PushBack("f:/pics/0.jpg1");
	int count = end - beg;
	p->setSourceFiles(vtImgs);
	p->setSentry(count / 2);
//	p->SetCache(ImagePool::Cache(ImagePool::Cache::CacheMode_Count_Limit, 2));
	p->setCache(ImagePool::Cache(ImagePool::Cache::CacheMode_Count_Limit, count+ 1));
}

#define IMAGE_COUNT		10
void TestImagePool::Test()
{
	Reset(&m_imgPool1, 0, 13);
	Reset(&m_imgPool2, 0, 5);
	m_imgPool1.startLoading();
//	m_imgPool1.SetLoadingDirection(ImagePool::Direction_Forward);
	m_imgPool1.setListener(this);
//	m_imgPool1.SetSentry(5);
//	m_imgPool1.SetImageMemoryLimit(ImagePool::FileType_Jpeg, 2 * 1024 * 1024);

	m_imgPool2.startLoading();
	m_imgPool2.setListener(this);
//	m_imgPool2.SetImageMemoryLimit(ImagePool::FileType_Jpeg, 2 * 1024 * 1024);

	m_imgPool1.setSourceFiles(ImageSources());
	m_imgPool2.setSourceFiles(ImageSources());
	Reset(&m_imgPool1, 0, 13);
	Reset(&m_imgPool2, 0, 5);
}
void TestImagePool::ImagePool_OnLoading_Start(ImagePool *sender)
{
	printf("TestImagePool::ImagePool_OnLoading_Start()\r\n");
}

void TestImagePool::ImagePool_OnLoading_Idled(ImagePool *sender)
{
	printf("TestImagePool::ImagePool_OnLoading_Idled()\r\n");
}

void TestImagePool::ImagePool_OnImage_Loaded(ImagePool *sender, int index, int millisecond)
{
//	char arr[80] = {0};
//	sprintf(arr, "[%p]", sender);
//	printf("[%p]new loaded---index[%d], millisecond[%d]\r\n", sender, index, millisecond);
//	Bitmap *bm = m_imgPool1.GetImage(index);
//	printf("width[%d], height[%d]\r\n", bm ? bm->GetWidth() : 0, bm ? bm->GetHeight() : 0);
//	std::vector<String>	vtImgs;
//	if(index == 5)
//	m_imgPool1.SetSourceFiles(vtImgs);
// 	if(index == 0)
// 	{
// 		ImagePool::ImageItemProperty item;
// 		bool bLock = sender->GetImageItemPropertyAndLock(0, item);
// 		item.m_Bitmap->saveAsFile("f:/xxx/000.jpg");
// 		if(bLock)
// 			sender->GetImageItemPropertyUnlock(0);
// 	}
// 
// 	if(index == 3)
// 	{
// 		sender->SetSentry(0);
// 	}
// 	else if(index == 1)
// 	{
// 		sender->SetSentry(4);
// 	}
// 	return;
	PrintAll(sender, false);
	if(index == 0)
	{
		Random rd(1, 100);
		int beg = rd.one();
		int end = rd.one();
		if(beg > end)
		{
			std::swap(beg, end);
		}
		else if(beg == end)
		{
			end++;
		}
//		OutputDebugStringA((std::string(arr) + "reset 111\r\n").data());
		Reset(sender, beg, end);
//		OutputDebugStringA((std::string(arr) + "reset 222\r\n").data());
	}
	return;
/*	static bool bxx = true;
	if(index == 2 && bxx)
	{
		nb::Media::ImageSources vtImgs;
		for(int i = 0; i != 20; ++i)
		{
			char arr[10] = {0};
			sprintf(arr, "%d", i);
			std::string s;
#ifdef WIN32
			s = std::string("f:/Pics/") + arr + ".jpg";
#else
			s = std::string("Pics/") + arr + ".jpg";
#endif
			vtImgs.PushBack(s.data());
		}
		m_imgPool1.SetSourceFiles(vtImgs);
		bxx = false;
	}
	return;*/
// 	if(index == 5)
// 		m_imgPool1.SetSentry(20);
// 	if(index == 21)
// 		m_imgPool1.SetSentry(3);
// 	if(index == 8)
// 		m_imgPool1.SetSentry(1);
// 	if(index == 4)
// 		m_imgPool1.SetSentry(15);
// 	if(index == 20)
// 		m_imgPool1.SetSentry(22);
}

void TestImagePool::ImagePool_OnImage_Released(ImagePool *sender, int index)
{
	printf("[%p]release---index[%d]\r\n", sender, index);
	PrintAll(sender, true);
}
