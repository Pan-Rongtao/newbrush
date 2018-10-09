#include <GLES2/gl2.h>
#include "gles/VBO.h"
#include "core/Exception.h"

using namespace nb::gl;

VBO::VBO()
{
	glGenBuffers(1, &m_glHandle);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &m_glHandle);
}

void VBO::active()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_glHandle);
}

void VBO::deactive()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::cacheDataToGpu(const float *data, int bytes)
{
	if(bytes < 0)
		NB_THROW_EXCEPTION("param invalid");
	if(data == NULL || bytes == 0)
		return;
	active();
	glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	m_nBytes = bytes;
	deactive();
}

int VBO::bytes() const
{
	return m_nBytes;
}

void VBO::updateCacheData(const float *data, int cacheOffset, int size)
{
	if(cacheOffset < 0 || size < 0 || cacheOffset + size > bytes())
		NB_THROW_EXCEPTION("param invalid");
	if(data == NULL || size == 0)
		return;
	active();
	glBufferSubData(GL_ARRAY_BUFFER, cacheOffset, size, data);
	deactive();
}
