#include "newbrush/Scene.h"
#include "newbrush/Log.h"
#include "newbrush/Mesh.h"

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

void Scene::addLight(ref<Light> light)
{
	nbThrowExceptionIf(!light, std::invalid_argument, "light is nullptr");
	m_lights.push_back(light);
}

void Scene::removeLight(unsigned index)
{
	nbThrowExceptionIf(index >= lightCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)lightCount());
	m_lights.erase(m_lights.begin() + index);
}

unsigned Scene::lightCount() const
{
	return m_lights.size();
}

bool Scene::hasLight() const
{
	return lightCount() != 0;
}

ref<Light> Scene::getLightAt(unsigned index)
{
	nbThrowExceptionIf(index >= lightCount(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)lightCount());
	return m_lights[index];
}

void Scene::clearLights()
{
	m_lights.clear();
}

const std::vector<ref<Light>> Scene::lights() const
{
	return m_lights;
}

void Scene::onRender()
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(/*GL_COLOR_BUFFER_BIT | */GL_DEPTH_BUFFER_BIT);	//在android下耗时非常高，达到10ms...，不要GL_COLOR_BUFFER_BIT，否则遮挡下面的node

	for (auto child : children())
	{
		child->onRender(m_camera, m_lights);
	}
}
