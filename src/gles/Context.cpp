#include "gles/Context.h"
#include <EGL/egl.h>
#include <algorithm>
#include "gles/Egl.h"
#include "gles/RenderObject.h"
#include "EglMaster.h"

using namespace nb;
using namespace nb::gl;

Context::Context(std::shared_ptr<Configure> configure)
{
	if (!gl::getDisplay())
		nbThrowException(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	EGLint contextAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
	m_handle = eglCreateContext(gl::getDisplay()->handle(), configure->handle(), 0, contextAttr);
	EglMaster::contexts().push_back(this);
}

Context::~Context()
{
	eglDestroyContext(gl::getDisplay()->handle(), m_handle);
	auto &contexts = EglMaster::contexts();
	auto iter = std::find(contexts.begin(), contexts.end(), this);
	if (iter != contexts.end())
		contexts.erase(iter);
}

void *Context::handle() const
{
	return m_handle;
}

void Context::queue(std::shared_ptr<RenderObject> renderObject)
{
	if (std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject) == m_renderObjects.end())
		m_renderObjects.push_back(renderObject);
}

void Context::dequeue(std::shared_ptr<RenderObject> renderObject)
{
	auto iter = std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject);
	if (iter != m_renderObjects.end())
		m_renderObjects.erase(iter);
}

uint32_t Context::renderObjectCount() const
{
	return (uint32_t)m_renderObjects.size();
}

std::shared_ptr<RenderObject> Context::renderObject(uint32_t index)
{
	if (index >= m_renderObjects.size())
		nbThrowException(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, (int)m_renderObjects.size());

	return m_renderObjects[index];
}

void Context::draw()
{
	for (int i = 0; i != m_renderObjects.size(); ++i)
		m_renderObjects[i]->draw();
}