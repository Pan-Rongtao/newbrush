#include "gles/Context.h"
#include <EGL/egl.h>
#include <algorithm>
#include "gles/Egl.h"
#include "core/Exception.h"
#include "gles/RenderObject.h"
#include "EglMaster.h"

using namespace nb::core;
using namespace nb::gl;

Context::Context(const Configure &configure)
{
	if(nb::gl::getCurrentDisplay().isNull())	throw SystemException();

	EGLint contextAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
	m_handle = eglCreateContext(nb::gl::getCurrentDisplay().handle(), configure.handle(), 0, contextAttr);
	nb::gl::ContextMaster::push(this);
}

Context::~Context()
{
	eglDestroyContext(nb::gl::getCurrentDisplay().handle(), m_handle);
	nb::gl::ContextMaster::erease(this);
}

void *Context::handle() const
{
	return m_handle;
}

void Context::queue(std::shared_ptr<nb::gl::RenderObject> renderObject)
{
	if (std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject) == m_renderObjects.end())
		m_renderObjects.push_back(renderObject);
}

void Context::dequeue(std::shared_ptr<nb::gl::RenderObject> renderObject)
{
	auto iter = std::find(m_renderObjects.begin(), m_renderObjects.end(), renderObject);
	if (iter != m_renderObjects.end())
		m_renderObjects.erase(iter);
}

int Context::renderObjectCount() const
{
	return m_renderObjects.size();
}

std::shared_ptr<nb::gl::RenderObject> Context::renderObject(uint32_t index)
{
	if (index >= m_renderObjects.size())	throw ArrayIndexOutOfRangeException(m_renderObjects.size(), index);
	return m_renderObjects[index];
}

void Context::draw()
{
	for (int i = 0; i != m_renderObjects.size(); ++i)
		m_renderObjects[i]->draw();
}