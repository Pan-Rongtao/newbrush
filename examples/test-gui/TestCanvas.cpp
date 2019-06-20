#include "TestCanvas.h"

void TestCanvas::test()
{
	auto cv = std::make_shared<Canvas>();

	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 100;
	rc0->Height = 100;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->Fill = std::make_shared<SolidColorBrush>(Colors::green());
	rc1->Width = 100;
	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->Fill = std::make_shared<SolidColorBrush>(Colors::blue());
	rc2->Width = 100;
	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->Fill = std::make_shared<SolidColorBrush>(Colors::firebrick());
	rc3->Width = 100;
	rc3->Height = 100;

	doubleAni.From = 800;
	doubleAni.To = 1000;
	doubleAni.Easing = std::make_shared<SineEase>();
	doubleAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.Duration = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.StateChangedEvent += std::bind(&TestCanvas::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestCanvas::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestCanvas::onCompleted, this, std::placeholders::_1);
	doubleAni.TargetProperty = &m_window.Width;
	doubleAni.begin();

	cv->Children().push_back(rc0);
	cv->Children().push_back(rc1);
	cv->Children().push_back(rc2);
	cv->Children().push_back(rc3);
	cv->setLeft(rc0, 100);
	cv->setTop(rc0, 100);
	cv->setLeft(rc1, 200);
	cv->setTop(rc1, 200);
	cv->setLeft(rc2, 300);
	cv->setTop(rc2, 300);
	cv->setLeft(rc3, 400);
	cv->setTop(rc3, 400);

	m_window.Content = cv;
	
}

void TestCanvas::onStateChanged(const Timeline::StateChangedArgs & args)
{
	printf("onStateChanged:%d\n", args.state);
}

void TestCanvas::onProgress(const Timeline::ProgressArgs & args)
{
	//	printf("onProgress:%f, width=%f\n", args.progress, m_window.Width());
	//printf("onProgress:%f, point=(%f, %f)\n", args.progress, Position().x(), Position().y());
	//	printf("onProgress:%f, color=(%d, %d, %d)\n", args.progress, Background().red(), Background().green(), Background().blue());
}

void TestCanvas::onCompleted(const Timeline::CompleteArgs & args)
{
	printf("onCompleted.\n");
}
