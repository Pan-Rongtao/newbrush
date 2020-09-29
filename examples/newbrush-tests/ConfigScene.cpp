#include "ConfigScene.h"
#include "newbrush/model/Timer.h"
#include "newbrush/model/Log.h"
#include "newbrush/model/NBBParser.h"

using namespace nb;

void ConfigScene::parse(const std::string & path)
{
	m_window = std::make_shared<Window>();

	m_window->KeyEvent += std::bind(&ConfigScene::onKey, this, std::placeholders::_1);
	m_window->ResizeEvent += std::bind(&ConfigScene::onResize, this, std::placeholders::_1);
	m_window->CursorPosEvent += std::bind(&ConfigScene::onCursorPos, this, std::placeholders::_1);
	m_window->ScrollEvent += std::bind(&ConfigScene::onScroll, this, std::placeholders::_1);

	NBBParser parser;
	parser.parse(path, m_scene);

	m_window->resize(m_scene->width(), m_scene->height());
}

Scene3DPtr ConfigScene::getScene() const
{
	return m_scene;
}

void ConfigScene::loopDraw()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	Color c(255, 255, 255, 255);
	glClearColor(/*c.alphaF(), c.redF(), c.greenF(), c.blueF()*/0.3f, 0.3f, 0.3f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (1)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Timer::driveInLoop();
		m_scene->draw();
		m_window->swapBuffers();
	}
}

void ConfigScene::onKey(const int & key)
{
	switch (key)
	{
	case 87: m_scene->camera()->moveForward();		break;
	case 83: m_scene->camera()->moveBackward();	break;
	case 65: m_scene->camera()->moveLeft();		break;
	case 68: m_scene->camera()->moveRight();		break;
	case 49:
	{
		auto cubeMaterial = std::make_shared<CubemapMaterial>();
		m_scene->model()->setMaterial(cubeMaterial);
		break;
	}
	case 50:
	{
		m_scene->playAnimation();
	}
	default: break;
	}
}

void ConfigScene::onResize(const Size & sz)
{
	m_scene->setWidth(sz.width);
	m_scene->setHeight(sz.height);
}

void ConfigScene::onCursorPos(const Point & pt)
{
	static bool firstMouse = true;
	static float lastX = m_window->width() / 2.0f;
	static float lastY = m_window->height() / 2.0f;
	if (firstMouse)
	{
		lastX = pt.x;
		lastY = pt.y;
		firstMouse = false;
	}

	float xoffset = (float)(pt.x - lastX);
	float yoffset = (float)(lastY - pt.y);

	lastX = pt.x;
	lastY = pt.y;

	//	m_scene->camera()->pitchYaw(xoffset, yoffset);

	auto rotateY = m_scene->model()->transform()->rotateY();
	auto angle = glm::degrees(rotateY);
	angle += xoffset;
	m_scene->model()->transform()->setRotateY(glm::radians(angle));
}

void ConfigScene::onScroll(const Point & pt)
{
	static float Zoom = 45.0f;
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= pt.y;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	m_scene->camera()->setFOV(Zoom);
}
