#include <GLES2/gl2.h>
#include "gles/VBO.h"

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

void VBO::cacheDataToGpu(const float *data, uint32_t bytes)
{
	if(!data || bytes == 0)
		return;

	active();
	glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	m_nBytes = bytes;
	deactive();
}

uint32_t VBO::bytes() const
{
	return m_nBytes;
}

void VBO::updateCacheData(const float *data, uint32_t cacheOffset, uint32_t size)
{
	if (!data || size == 0 || cacheOffset >= bytes())
		return;

	if (cacheOffset + size > bytes())
		size = bytes() - cacheOffset;

	active();
	glBufferSubData(GL_ARRAY_BUFFER, cacheOffset, size, data);
	deactive();
}
