#include "newbrush/model/Scene3D.h"
#include "newbrush/model/ModelImporter.h"
#include <GLES2/gl2.h>

using namespace nb;

Scene3D::Scene3D(int width, int height)
	: m_camera(std::make_shared<Camera>())
{
	resize(width, height);
	//默认添加一个点光源，否则渲染很黑
	PointLightPtr pointLight = std::make_shared<PointLight>();
	pointLight->setPosition(glm::vec3(0.0f, 5.0f, 5.0f));
	pointLight->setAmbient(Color::fromRgbF(0.5f, 0.5f, 0.5f));
	pointLight->setDiffuse(Color::fromRgbF(1.0, 1.0, 1.0));
	pointLight->setSpecular(Color::fromRgbF(0.5f, 0.5f, 0.5f));
	addLight(pointLight);
}

void Scene3D::resize(int width, int height)
{
	m_camera->setAspect((float)width / (float)height);
	glViewport(0, 0, width, height);
}

void Scene3D::setCamera(CameraPtr camera)
{
	m_camera = camera;
}

CameraPtr Scene3D::camera()
{
	return m_camera;
}

void Scene3D::addLight(LightPtr light)
{
	m_lights.push_back(light);
}

void Scene3D::removeLight(LightPtr light)
{
	auto iter = std::find(m_lights.begin(), m_lights.end(), light);
	if (iter != m_lights.end())
	{
		m_lights.erase(iter);
	}
}

void Scene3D::removeLightAt(uint32_t index)
{
	if (index >= m_lights.size())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_lights.size());
	}
	m_lights.erase(m_lights.begin() + index);
}

LightPtr Scene3D::lightAt(uint32_t index)
{
	if (index >= m_lights.size())
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, %zu)", index, m_lights.size());
	}
	return m_lights[index];
}

uint32_t Scene3D::lightCount() const
{
	return m_lights.size();
}

void Scene3D::setModel(NodePtr model)
{
	m_model = model;
}

NodePtr Scene3D::model()
{
	return m_model;
}

void Scene3D::load(const std::string & path, const std::string & textureDir)
{
	ModelImporter importer;
	importer.load(path, textureDir);
	auto model = importer.getRootNode();
	setModel(model);
	auto lights = importer.getLights();
	for (auto l : lights)
	{
		addLight(l);
	}
	m_animations = importer.getAnimations();
}

void Scene3D::draw()
{
	loopDraw(m_model);
}

void Scene3D::playAnimation()
{
	for (auto animation : m_animations)
	{
		animation->begin();
	}
}

void Scene3D::loopDraw(NodePtr node)
{
	if (!node) return;

	if (is<MeshNode>(node))
	{
		auto mesh = (as<MeshNode>(node))->mesh();
		mesh->matrix = node->getRenderTransform();
		mesh->draw(m_camera, m_lights);
	}
	else
	{
		for (auto i = 0u; i != node->childCount(); ++i)
		{
			auto child = node->childAt(i);
			loopDraw(child);
		}
	}
}
