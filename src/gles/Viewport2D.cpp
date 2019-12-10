#include "gles/Viewport2D.h"
#include "gles/RenderObject.h"

using namespace nb;

void Viewport2D::queue(std::shared_ptr<RenderObject> renderObject)
{
	if (std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject) == m_renderObjects.end())
		m_renderObjects.push_back(renderObject);
}

void Viewport2D::draw()
{
	for (auto ro : m_renderObjects)
		ro->draw();
}
