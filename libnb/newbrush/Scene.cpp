#include "newbrush/Scene.h"
#include "newbrush/GLUnit.h"
#include "newbrush/Log.h"

using namespace nb;

Scene::Scene() 
	: m_camera(createRef<PerspectiveCamera>())
{}

void Scene::setCamera(ref<PerspectiveCamera> camera)
{
	m_camera = camera;
}

ref<PerspectiveCamera> Scene::getCamera() const
{
	return m_camera;
}

void Scene::onResize(float width, float height)
{
	m_camera->setAspect(width / height);
	glViewport(0, 0, (int)width, (int)height);
}

void Scene::onRender()
{
	static int frames = 0;
	static uint64_t t0 = getMilliseconds();

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//在android下耗时非常高，达到10ms...
	glClearColor(0.96f, 0.96f, 0.96f, 1.0f);
	for (auto child : children())
	{
		loopDraw(child);
	}

	++frames;
	uint64_t t1 = getMilliseconds();
	if (t1 - t0 >= 5000)
	{
		float fps = frames * 1000.0f / (t1 - t0);
		frames = 0;
		t0 = t1;
		Log::info("fps:{}", fps);
	}
}

void Scene::loopDraw(ref<Node> node)
{
	if (!node) return;

	if (node->mesh())
	{
		auto const &matrix = node->getRenderTransform();
		node->mesh()->draw(matrix, m_camera, lights);
	}
	else
	{
		for (auto &child : node->children())
		{
			loopDraw(child);
		}
	}
}
