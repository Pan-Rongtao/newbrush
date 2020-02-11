#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/RenderObject.h"
#include <GLES2/gl2.h>

using namespace nb;

void Viewport2D::viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}

void Viewport2D::queue(std::shared_ptr<RenderObject> renderObject)
{
	if (std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject) == m_renderObjects.end())
		m_renderObjects.push_back(renderObject);
}

void Viewport2D::draw()
{
	for (auto ro : m_renderObjects)
		ro->draw(camera, projection);
}
