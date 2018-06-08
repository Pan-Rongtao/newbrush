#include <assert.h>
#include "media/Bitmap.h"
#include "Bitmap_Internal.h"

using namespace nb::Media;
using namespace nb::System;

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
	m_internal = new Bitmap_Internal(size.GetWidth(), size.GetHeight(), Bitmap::Format_Bpp32_Rgba8888);
}

Bitmap::Bitmap(int width, int height, PixelFormat format)
{
	//rewrite when define assert
	assert(width >= 0 && height >= 0);
	m_internal = new Bitmap_Internal(width, height, format);
}

Bitmap::Bitmap(const SizeI &size, PixelFormat format)
{
	m_internal = new Bitmap_Internal(size.GetWidth(), size.GetHeight(), format);
}

Bitmap::Bitmap(const unsigned char *buffer, int width, int height, PixelFormat format)
{
	m_internal = new Bitmap_Internal(buffer, width, height, format);
}

Bitmap::Bitmap(const unsigned char *buffer, const SizeI &size, PixelFormat format)
{
	m_internal = new Bitmap_Internal(buffer, size.GetWidth(), size.GetHeight(), format);
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

void Bitmap::LoadFile(const char *pFilePath)
{
	m_internal->LoadFile(pFilePath);
}

void Bitmap::LoadFile(const String &filePath)
{
	LoadFile(filePath.ToUtf8().GetData());
}

void Bitmap::LoadFileNarrowed(const nb::System::String &filePath, int jpegNarrow)
{
	m_internal->LoadFileNarrowed(filePath, jpegNarrow);
}

void Bitmap::LoadData(const unsigned char *data, int nLengthBytes)
{
	return m_internal->LoadData(data, nLengthBytes);
}

const unsigned char *Bitmap::GetData() const
{
	return m_internal->GetData();
}

void Bitmap::Fill(const Color &c)
{
	m_internal->Fill(c.ToInteger32());
}

int Bitmap::GetWidth() const
{
	return m_internal->GetPixelWidth();
}

int Bitmap::GetHeight() const
{
	return m_internal->GetPixelHeight();
}

SizeI Bitmap::GetSize() const
{
	return SizeI(GetWidth(), GetHeight());
}

int Bitmap::GetBytesCount() const
{
	return m_internal->GetBytesCount();
}

unsigned char *Bitmap::GetScanLine(int lineIndex)
{
	return m_internal->GetScanLine(lineIndex);
}

bool Bitmap::HasPixelData() const
{
	return m_internal->HasPixelData();
}

bool Bitmap::IsNull() const
{
	return m_internal->IsNull();
}

Bitmap::PixelFormat Bitmap::GetPixelFormat() const
{
	return m_internal->GetPixelFormat();
}

int Bitmap::GetBpp() const
{
	return m_internal->GetBpp();
}

Color Bitmap::GetPixel(int x, int y) const
{
	return Color::FromInteger32(m_internal->GetPixel(x, y));
}

Color Bitmap::GetPixel(const PointI &p) const
{
	return GetPixel(p.GetX(), p.GetY());
}

void Bitmap::SetPixel(int x, int y, const Color &c)
{
	m_internal->SetPixel(x, y, c.ToInteger32());
}

void Bitmap::SetPixel(const PointI &p, const Color &c)
{
	SetPixel(p.GetX(), p.GetY(), c);
}

Bitmap Bitmap::Scale(int width, int height) const
{
	Bitmap_Internal pri = m_internal->Scale(width, height);
	return Bitmap(pri.GetData(), pri.GetPixelWidth(), pri.GetPixelHeight(), pri.GetPixelFormat());
}

Bitmap Bitmap::Scale(const SizeI &size) const
{
	return Scale(size.GetWidth(), size.GetHeight());
}

Bitmap Bitmap::ScaleWidth(int width) const
{
	return Scale(width, GetHeight());
}

Bitmap Bitmap::ScaleHeight(int height) const
{
	return Scale(GetWidth(), height);
}

Bitmap Bitmap::Copy() const
{
	return Copy(0, 0, GetWidth(), GetHeight());
}

Bitmap Bitmap::Copy(int x, int y, int width, int height) const
{
	Bitmap_Internal pri = m_internal->Copy(x, y, width, height);
	return Bitmap(pri.GetData(), pri.GetPixelWidth(), pri.GetPixelHeight(), pri.GetPixelFormat());
}

Bitmap Bitmap::Copy(const RectI &rc) const
{
	return Copy(rc.GetLeft(), rc.GetTop(), rc.GetWidth(), rc.GetHeight());
}

Bitmap Bitmap::ToGray() const
{
	Bitmap_Internal pri = m_internal->ToGray();
	return Bitmap(pri.GetData(), pri.GetPixelWidth(), pri.GetPixelHeight(), pri.GetPixelFormat());
}

Bitmap Bitmap::ConverToFormat(PixelFormat format)
{
	Bitmap_Internal pri = m_internal->ConverToFormat(format);
	return Bitmap(pri.GetData(), pri.GetPixelWidth(), pri.GetPixelHeight(), pri.GetPixelFormat());
}

void Bitmap::SaveAsFile(const String &filePath) const
{
	SaveAsFile(filePath.ToUtf8().GetData());
}

void Bitmap::SaveAsFile(const char *pfilePath) const
{
	m_internal->SaveAsFile(pfilePath);
}
/*
Bitmap Bitmap::BgrToRgb() const
{
	Bitmap_Internal pri = m_internal->BgrToRgb();
	return Bitmap(pri.GetData(), pri.GetPixelWidth(), pri.GetPixelHeight(), pri.GetPixelFormat());
}*/
