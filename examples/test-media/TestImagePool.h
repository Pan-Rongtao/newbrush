#pragma once
#include "TestBase.h"
#include "media/ImagePool.h"

class TestImagePool : public TestBase, public nb::media::ImagePoolEvent
{
public:
	TestImagePool();
	virtual void Test();

private:
	void Reset(nb::media::ImagePool *p, int beg, int end);
	void PrintAll(nb::media::ImagePool *p, bool bRelease);


	virtual void ImagePool_OnLoading_Start(nb::media::ImagePool *sender);

	virtual void ImagePool_OnLoading_Idled(nb::media::ImagePool *sender);

	virtual void ImagePool_OnImage_Loaded(nb::media::ImagePool *sender, int index, int millisecond);

	virtual void ImagePool_OnImage_Released(nb::media::ImagePool *sender, int index);

	nb::media::ImagePool	m_imgPool1;
	nb::media::ImagePool	m_imgPool2;
};