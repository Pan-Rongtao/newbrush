#include "FloatView.h"

extern MessageQueue g_msgQueue;
void FloatView::init()
{
	Application::get()->mainWindow()->setWidth(800.0f);
	Application::get()->mainWindow()->setHeight(600.0f);
	Application::get()->mainWindow()->setTitle("lanjing5 Power By NewBrush");
	m_root = createRef<Node2D>(/*0.0f, 0.0f, 200.0f, 200.0f*/);
	m_root->setAlignmentCenter();
	m_root->setScene(createRef<Scene>());
#ifdef WIN32
	m_root->setBackground(SolidColorBrush::white());
#endif

	auto resDir = m_resDir.empty() ? RES_DIR : m_resDir;
	auto model = loadModel(resDir + "lanjing5/1.fbx", glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, glm::radians(180.0f), 0.0f), glm::vec3(0.004f));
	auto light = createRef<PointLight>();
#ifdef WIN32
	light->ambient = {50, 50, 50};
	light->diffuse = { 255, 255, 255 };
#else
	light->ambient = { 75, 75, 75 };
	light->diffuse = { 1, 1, 1 };
#endif
	m_root->getScene()->addLight(light);
	m_root->getScene()->addChild(model);
	m_root->Touch += nbBindEventFunction(FloatView::onTouch);
	m_root->Key += nbBindEventFunction(FloatView::onKey);

	auto data = nb::makeDataObject("m_root");
	data->add(makeDataInt("AnimationType", -1));
	m_data = data;
	m_data->ValueChanged += [&](const DataContext::ValueChangedArgs & args) { onDataChanged(args.path, args.value); };

	model->AnimationStateChanged += [=](const TimelineState &state)
	{
		float beg, end;
		model->getFrameSection(beg, end);
		auto aniIndex = -1;
		if (end == 110.0f)		aniIndex = 0;
		else if (end == 210.0f)	aniIndex = 1;
		else if (end == 375.0f)	aniIndex = 2;
		else if (end == 545.0f)	aniIndex = 3;
		else if (end == 650.0f)	aniIndex = 4;
		else if (end == 730.0f)	aniIndex = 5;
		auto st = (int)state;
		auto args = std::to_string(aniIndex) + "," + std::to_string(st);
#if NB_OS == NB_OS_ANDROID
		nofityAndroid("AnimationStateChangedEvent", args);
#endif
	};
	//	setData("AnimationType", 0);
#if NB_OS == NB_OS_ANDROID
	nofityAndroid("InitDoneEvent", "");
#endif
}

void FloatView::onDataChanged(const std::string & path, const var & value)
{
	if (path == "AnimationType")
	{
		//一定不要传引用/指针进去
		auto task = [=]()
		{
			auto model = nb::as<Model>(m_root->getScene()->getChildAt(0));
			if (!model)
				return;

			int x = value.get_value<int>();
			bool onceAni = (x & 0xf0000000) == 0x10000000;
			int type = x & 0x0fffffff;
			switch (type)
			{
			case 0:	model->setFrameSection(0.0, 110);	model->play(!onceAni); break;
			case 1:	model->setFrameSection(120.0, 210.0f);	model->play(!onceAni); break;
			case 2:	model->setFrameSection(220.0, 375.0f);	model->play(!onceAni); break;
			case 3:	model->setFrameSection(385.0, 545.0f);	model->play(!onceAni); break;
			case 4:	model->setFrameSection(545.0, 650.0f);	model->play(!onceAni); break;
			case 5:	model->setFrameSection(660.0, 730.0f);	model->play(!onceAni); break;
			case 9:	model->setFrameSection(0.0, -1.0f);		model->play(!onceAni); break;
			default:	break;
			}
		};
#if NB_OS == NB_OS_ANDROID
		g_msgQueue.post(task);
#else
		task();
#endif
	}

}

void FloatView::onTouch(const TouchEventArgs & e)
{
	Point p = { e.x, e.y };
	if (e.action == TouchAction::Down)
	{
		m_pressed = true;
		m_pressedPoint = p;
	}
	else if (e.action == TouchAction::Move)
	{
		if (!m_pressed) return;

		Point ptOffset = { p.x - m_pressedPoint.x, m_pressedPoint.y - p.y };
		m_pressedPoint = p;

		auto model = m_root->getScene()->getChildAt(0);
		if (!model)
			return;

		auto rotate = model->getTransform()->getRotate();
		auto newAngle = glm::degrees(rotate.y) + ptOffset.x;
		rotate.y = glm::radians(newAngle);
		model->getTransform()->setRotate(rotate);
	}
	else if (e.action == TouchAction::Up)
	{
		m_pressed = false;
	}
}

void FloatView::onKey(const KeyEventArgs &e)
{
	if (e.action != KeyAction::Down)
		return;

	switch (e.key)
	{
	case KeyCode::_1:	setData("AnimationType", 0); break;
	case KeyCode::_2:	setData("AnimationType", 1); break;
	case KeyCode::_3:	setData("AnimationType", 2); break;
	case KeyCode::_4:	setData("AnimationType", 3); break;
	case KeyCode::_5:	setData("AnimationType", 4); break;
	case KeyCode::_6:	setData("AnimationType", 5); break;
	case KeyCode::_9:	setData("AnimationType", 9); break;
	case KeyCode::KP_1:	setData("AnimationType", 0x10000000 | 2);	break;
	default:														break;
	}
}
//一定不要少了这句
ref<ViewBase> g_view = createRef<FloatView>();