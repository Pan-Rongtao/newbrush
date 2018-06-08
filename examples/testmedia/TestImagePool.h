#pragma once
#include "TestBase.h"
#include "media/ImagePool.h"
#include "system/Timer.h"

class TestImagePool : public nbObject, public TestBase, public nb::Media::ImagePoolEvent
{
public:
	TestImagePool();
	virtual void Test();

private:
	void Reset(nb::Media::ImagePool *p, int beg, int end);
	void PrintAll(nb::Media::ImagePool *p, bool bRelease);


	virtual void ImagePool_OnLoading_Start(nb::Media::ImagePool *sender);

	virtual void ImagePool_OnLoading_Idled(nb::Media::ImagePool *sender);

	virtual void ImagePool_OnImage_Loaded(nb::Media::ImagePool *sender, int index, int millisecond);

	virtual void ImagePool_OnImage_Released(nb::Media::ImagePool *sender, int index);

	void OnTick(nb::System::Timer::TimeoutParam &param);

	nb::Media::ImagePool	m_imgPool1;
	nb::Media::ImagePool	m_imgPool2;
	nb::System::Timer		m_Timer;
};