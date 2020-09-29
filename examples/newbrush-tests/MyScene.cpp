#include "MyScene.h"
#include "newbrush/model/Timer.h"
#include "newbrush/model/Log.h"

MyScene::MyScene(int width, int height)
{
	m_window = std::make_shared<Window>(width, height);
	m_window->KeyEvent += std::bind(&MyScene::onKey, this, std::placeholders::_1);
	m_window->ResizeEvent += std::bind(&MyScene::onResize, this, std::placeholders::_1);
	m_window->CursorPosEvent += std::bind(&MyScene::onCursorPos, this, std::placeholders::_1);
	m_window->ScrollEvent += std::bind(&MyScene::onScroll, this, std::placeholders::_1);
	m_sc = std::make_shared<Scene3D>(width, height);
}

void MyScene::load(const std::string & path, float scale)
{
	auto k = nb::getTickCount();
	m_sc->load(path);
	auto cost = nb::getTickCount() - k;
	if (m_sc->model())
	{
		int32_t meshCount = 0, triangleCount = 0, vertexCount = 0;
		m_sc->model()->getInfo(meshCount, triangleCount, vertexCount);
		Log::info("load [{}] success cost [{}] ms. MeshCount:[{}], TriangleCount:[{}], VertexCount=[{}]", path, cost, meshCount, triangleCount, vertexCount);
	}
	else
	{
		Log::error("load [{}] fail cost [{}] ms.", path, cost);
		return;
	}

	m_translate = -0.3f;
	m_angle = 0.0f;
	m_scale = scale;

	updateTransform();
}

Scene3DPtr MyScene::getScene() const
{
	return m_sc;
}

void MyScene::loopDraw()
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
		m_sc->draw();
		m_window->swapBuffers();
	}

}

void MyScene::onKey(const int & key)
{
	switch (key)
	{
	case 87: m_sc->camera()->moveForward();		break;
	case 83: m_sc->camera()->moveBackward();	break;
	case 65: m_sc->camera()->moveLeft();		break;
	case 68: m_sc->camera()->moveRight();		break;
	case 49: 
	{
		auto cubeMaterial = std::make_shared<CubemapMaterial>();
		m_sc->model()->setMaterial(cubeMaterial);
		break;
	}
	case 50:
	{
		m_sc->playAnimation();
	}
	default: break;
	}
}

void MyScene::onResize(const Size & sz)
{
	m_sc->setWidth(sz.width);
	m_sc->setHeight(sz.height);
}

void MyScene::onCursorPos(const Point & pt)
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

//	m_sc->camera()->pitchYaw(xoffset, yoffset);
		
	m_angle += xoffset;
	updateTransform();
}

void MyScene::onScroll(const Point & pt)
{
	static float Zoom = 45.0f;
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= pt.y;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
	m_sc->camera()->setFOV(Zoom);
}

void MyScene::updateTransform()
{
	TransformPtr transform = std::make_shared<Transform>();
	transform->setPosition({ 0.0f, m_translate, 0.0f });
	transform->setRotate({ 0.0f, glm::radians(m_angle), 0.0f });
	transform->setScale({ m_scale, m_scale, m_scale });

	auto x = transform->value();

	m_sc->model()->setTransform(transform);
}
