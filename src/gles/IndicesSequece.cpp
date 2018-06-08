#include <string.h>
#include "gles/IndicesSequece.h"
#include "core/Exception.h"

using nb::gl::Gles::IndicesSequece;

IndicesSequece::IndicesSequece(unsigned short *data, unsigned short size)
: m_Size(size)
{
	m_Head = new unsigned short[size];
	memcpy(m_Head, data, size * sizeof(unsigned short));
}

IndicesSequece::~IndicesSequece()
{
	delete []m_Head;
}

void IndicesSequece::operator = (const IndicesSequece &other)
{
	delete m_Head;
	m_Head = new unsigned short[other.m_Size];
	memcpy(m_Head, other.m_Head, other.m_Size * sizeof(unsigned short));
	m_Size = other.m_Size;
}

IndicesSequece::IndicesSequece(const IndicesSequece &other)
{
	m_Head = new unsigned short[other.m_Size];
	memcpy(m_Head, other.m_Head, other.m_Size * sizeof(unsigned short));
	m_Size = other.m_Size;
}

unsigned short *IndicesSequece::Data() const
{
	return m_Head;
}

unsigned short IndicesSequece::GetSize() const
{
	return m_Size;
}

unsigned short IndicesSequece::operator[] (int index)
{
	if(index < 0 || index >= m_Size)
		NB_THROW_EXCEPTION("out of index");

	return m_Head[index];
}
