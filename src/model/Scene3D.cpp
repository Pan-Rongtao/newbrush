#include "newbrush/model/Scene3D.h"
#include "newbrush/model/ModelImporter.h"
#include <GLES2/gl2.h>

using namespace nb;

Scene3D::Scene3D()
	: Scene3D(800, 480)
{

}

Scene3D::Scene3D(float width, float height)
	: m_camera(std::make_shared<Camera>())
	, m_width(width)
	, m_height(height)
{
	resize();
	//默认添加一个点光源，否则渲染很黑
	PointLightPtr pointLight = std::make_shared<PointLight>();
	pointLight->setPosition(glm::vec3(0.0f, 5.0f, 5.0f));
	pointLight->setAmbient(Color::fromRgbF(0.5f, 0.5f, 0.5f));
	pointLight->setDiffuse(Color::fromRgbF(1.0, 1.0, 1.0));
	pointLight->setSpecular(Color::fromRgbF(0.5f, 0.5f, 0.5f));
	m_lights.push_back(pointLight);
}

void Scene3D::setWidth(float width)
{
	m_width = width;
	resize();
}

float Scene3D::width() const
{
	return m_width;
}

void Scene3D::setHeight(float height)
{
	m_height = height;
	resize();
}

float Scene3D::height() const
{
	return m_height;
}

void Scene3D::resize()
{
	m_camera->setAspect(m_width / m_height);
	glViewport(0, 0, (int)m_width, (int)m_height);
}

void Scene3D::setCamera(CameraPtr camera)
{
	m_camera = camera;
}

CameraPtr Scene3D::camera()
{
	return m_camera;
}

void Scene3D::setLights(const std::vector<LightPtr> &lights)
{
	m_lights = lights;
}

std::vector<LightPtr> &Scene3D::lights()
{
	return m_lights;
}

const std::vector<LightPtr> &Scene3D::lights() const
{
	return m_lights;
}

void Scene3D::setModel(NodePtr model)
{
	m_model = model;
}

NodePtr Scene3D::model()
{
	return m_model;
}

void Scene3D::load(const std::string & path)
{
	ModelImporter importer;
	importer.setPath(path);
	m_model = importer.getRootNode();
	auto lights = importer.getLights();
	m_lights.insert(m_lights.end(), lights.begin(), lights.end());
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
		for (auto child : node->children())
		{
			loopDraw(child);
		}
	}
}
