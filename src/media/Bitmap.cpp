#include <assert.h>
#include "media/Bitmap.h"
#include "Bitmap_Internal.h"

using namespace nb::core;
using namespace nb::media;

Bitmap::Bitmap()
{
	m_internal = new Bitmap_Internal();
}

Bitmap::Bitmap(const String &filePath)
{
	m_internal = new Bitmap_Internal(filePath.ToUtf8().GetData());
}

Bitmap::Bitmap(int width, int height)
{
	m_internal = new Bitmap_Internal(width, height, Bitmap::Format_Bpp32_Rgba8888);
}

Bitmap::Bitmap(const SizeI &size)
{
	m_internal = new Bitmap_Internal(size.width(), size.height(), Bitmap::Format_Bpp32_Rgba8888);
}

Bitmap::Bitmap(int width, int height, PixelFormat format)
{
	//rewrite when define assert
	assert(width >= 0 && height >= 0);
	m_internal = new Bitmap_Internal(width, height, format);
}

Bitmap::Bitmap(const SizeI &size, PixelFormat format)
{
	m_internal = new Bitmap_Internal(size.width(), size.height(), format);
}

Bitmap::Bitmap(const unsigned char *buffer, int width, int height, PixelFormat format)
{
	m_internal = new Bitmap_Internal(buffer, width, height, format);
}

Bitmap::Bitmap(const unsigned char *buffer, const SizeI &size, PixelFormat format)
{
	m_internal = new Bitmap_Internal(buffer, size.width(), size.height(), format);
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

void Bitmap::loadFile(const char *pFilePath)
{
	m_internal->loadFile(pFilePath);
}

void Bitmap::loadFile(const String &filePath)
{
	loadFile(filePath.ToUtf8().GetData());
}

void Bitmap::loadFileNarrowed(const String &filePath, int jpegNarrow)
{
	m_internal->loadFileNarrowed(filePath, jpegNarrow);
}

void Bitmap::loadData(const unsigned char *data, int nLengthBytes)
{
	return m_internal->loadData(data, nLengthBytes);
}

const unsigned char *Bitmap::data() const
{
	return m_internal->data();
}

void Bitmap::fill(const Color &c)
{
	m_internal->fill(c.toInteger32());
}

int Bitmap::width() const
{
	return m_internal->pixelWidth();
}

int Bitmap::height() const
{
	return m_internal->pixelHeight();
}

SizeI Bitmap::size() const
{
	return SizeI(width(), height());
}

int Bitmap::bytesCount() const
{
	return m_internal->bytesCount();
}

unsigned char *Bitmap::scanLine(int lineIndex)
{
	return m_internal->scanLine(lineIndex);
}

bool Bitmap::hasPixelData() const
{
	return m_internal->hasPixelData();
}

bool Bitmap::isNull() const
{
	return m_internal->isNull();
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
	return Color::fromInteger32(m_internal->pixel(x, y));
}

Color Bitmap::pixel(const PointI &p) const
{
	return pixel(p.x(), p.y());
}

void Bitmap::setPixel(int x, int y, const Color &c)
{
	m_internal->setPixel(x, y, c.toInteger32());
}

void Bitmap::setPixel(const PointI &p, const Color &c)
{
	setPixel(p.x(), p.y(), c);
}

Bitmap Bitmap::scale(int width, int height) const
{
	Bitmap_Internal pri = m_internal->scale(width, height);
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

Bitmap Bitmap::scale(const SizeI &size) const
{
	return scale(size.width(), size.height());
}

Bitmap Bitmap::scaleWidth(int width) const
{
	return scale(width, height());
}

Bitmap Bitmap::scaleHeight(int height) const
{
	return scale(width(), height);
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

Bitmap Bitmap::copy(const RectI &rc) const
{
	return copy(rc.left(), rc.top(), rc.width(), rc.height());
}

Bitmap Bitmap::toGray() const
{
	Bitmap_Internal pri = m_internal->toGray();
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

Bitmap Bitmap::converToFormat(PixelFormat format)
{
	Bitmap_Internal pri = m_internal->converToFormat(format);
	return Bitmap(pri.data(), pri.pixelWidth(), pri.pixelHeight(), pri.pixelFormat());
}

void Bitmap::saveAsFile(const String &filePath) const
{
	saveAsFile(filePath.ToUtf8().GetData());
}

void Bitmap::saveAsFile(const char *pfilePath) const
{
	m_internal->saveAsFile(pfilePath);
}