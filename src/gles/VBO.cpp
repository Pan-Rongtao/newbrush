#include <GLES2/gl2.h>
#include "gles/VBO.h"
#include "core/Exception.h"

using namespace nb::gl::Gles;
VBO::VBO()
{
	glGenBuffers(1, &m_glHandle);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &m_glHandle);
}

void VBO::Active()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_glHandle);
}

void VBO::Deactive()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::CacheDataToGpu(const float *data, int bytes)
{
	if(bytes < 0)
		NB_THROW_EXCEPTION("param invalid");
	if(data == NULL || bytes == 0)
		return;
	Active();
	glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	m_nBytes = bytes;
	Deactive();
}

int VBO::GetBytes() const
{
	return m_nBytes;
}

void VBO::UpdateCacheData(const float *data, int cacheOffset, int bytes)
{
	if(cacheOffset < 0 || bytes < 0 || cacheOffset + bytes > GetBytes())
		NB_THROW_EXCEPTION("param invalid");
	if(data == NULL || bytes == 0)
		return;
	Active();
	glBufferSubData(GL_ARRAY_BUFFER, cacheOffset, bytes, data);
	Deactive();
}
