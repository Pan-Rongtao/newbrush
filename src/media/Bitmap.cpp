#include <assert.h>
#include "media/Bitmap.h"
#include "Bitmap_Internal.h"

using namespace nb::core;
using namespace nb::media;

Bitmap::Bitmap()
{
	m_internal = new Bitmap_Internal();
}

Bitmap::Bitmap(const std::string &path)
{
	m_internal = new Bitmap_Internal(path);
}

Bitmap::Bitmap(int width, int height)
{
	m_internal = new Bitmap_Internal(width, height, Bitmap::Format_Bpp32_Rgba8888);
}

Bitmap::Bitmap(int width, int height, PixelFormat format)
{
	m_internal = new Bitmap_Internal(width, height, format);
}

Bitmap::Bitmap(const char *buffer, int width, int height, PixelFormat format)
{
	m_internal = new Bitmap_Internal(buffer, width, height, format);
}

Bitmap::~Bitmap()
{
	delete m_internal;
}

Bitmap::Bitmap(const Bitmap &other)
{
	m_internal = new Bitmap_Internal(*other.m_internal);
}

void Bitmap::operator = (const Bitmap &other)
{
	delete m_internal;
	m_internal = new Bitmap_Internal(*other.m_internal);
}

void Bitmap::load(const std::string &path, int jpegNarrow)
{
	m_internal->load(path, jpegNarrow);
}

void Bitmap::load(const char *data, int nLengthBytes)
{
	return m_internal->load(data, nLengthBytes);
}

const char *Bitmap::data() const
{
	return m_internal->data();
}

void Bitmap::fill(const Color &c)
{
	m_internal->fill(c.toIntegerArgb());
}

int Bitmap::width() const
{
	return m_internal->pixelWidth();
}

int Bitmap::height() const
{
	return m_internal->pixelHeight();
}

int Bitmap::bytes() const
{
	return m_internal->bytes();
}

char *Bitmap::scanLine(int lineIndex)
{
	return m_internal->scanLine(lineIndex);
}

bool Bitmap::hasPixelData() const
{
	return m_internal->hasPixelData();
}

Bitmap::PixelFormat Bitmap::pixelFormat() const
{
	return m_internal->pixelFormat();
}

int Bitmap::bpp() const
{
	return m_internal->bpp();
}

Color Bitmap::pixel(int x, int y) const
{
	return Color::fromIntegerArgb(m_internal->pixel(x, y));
}

void Bitmap::setPixel(int x, int y, const Color &c)
{
	m_internal->setPixel(x, y, c.toIntegerArgb());
}

Bitmap Bitmap::scale(int width, int height) const
{
	Bitmap_Internal pri = m_internal->scale(width, height);
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

Bitmap Bitmap::copy() const
{
	return copy(0, 0, width(), height());
}

Bitmap Bitmap::copy(int x, int y, int width, int height) const
{
	Bitmap_Internal pri = m_internal->copy(x, y, width, height);
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

Bitmap Bitmap::gray() const
{
	Bitmap_Internal pri = m_internal->gray();
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

Bitmap Bitmap::convert(PixelFormat toFormat)
{
	Bitmap_Internal pri = m_internal->convert(toFormat);
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

void Bitmap::save(const std::string &path) const
{
	m_internal->save(path);
}
