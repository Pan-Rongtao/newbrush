﻿#include "newbrush/Bitmap.h"
#include <regex>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_resize.h"
#include "stb/stb_image_write.h"

using namespace nb;

Bitmap::Bitmap()
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
{}

Bitmap::Bitmap(const std::string &path)
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
{
	load(path);
}

Bitmap::~Bitmap()
{
	stbi_image_free(m_data);
}

Bitmap::Bitmap(const Bitmap &other)
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
{
	*this = other;
}

void Bitmap::operator = (const Bitmap &other)
{
	stbi_image_free(m_data);
	m_data = new unsigned char[other.bytes()];
	memcpy(m_data, other.data(), other.bytes());
	m_width = other.width();
	m_height = other.height();
	m_channels = other.channels();
}

void Bitmap::load(const std::string &path)
{
	stbi_image_free(m_data);
	m_data = stbi_load(path.data(), &m_width, &m_height, &m_channels, 0);
	if (!m_data)
	{
		m_width = 0;
		m_height = 0;
		m_channels = 0;
	}
}

void Bitmap::load(const unsigned char *buffer, uint32_t bytes)
{
	stbi_image_free(m_data);
	m_data = stbi_load_from_memory(buffer, bytes, &m_width, &m_height, &m_channels, 0);
	if (!m_data)
	{
		m_width = 0;
		m_height = 0;
		m_channels = 0;
	}
}

bool Bitmap::isValid() const
{
	return m_data != nullptr;
}

const unsigned char *Bitmap::data() const
{
	return m_data;
}

int Bitmap::width() const
{
	return m_width;
}

int Bitmap::height() const
{
	return m_height;
}

int Bitmap::bytes() const
{
	return m_width * m_height * channels();
}

int Bitmap::channels() const
{
	return m_channels;
}

bool Bitmap::scale(uint32_t width, uint32_t height)
{
	unsigned char *newData = new unsigned char[width * height * channels()];
	int n = stbir_resize_uint8(m_data, m_width, m_height, 0, newData, width, height, 0, channels());
	stbi_image_free(m_data);
	m_data = newData;
	m_width = width;
	m_height = height;
	return n != 0;
}

bool Bitmap::save(const std::string &path, uint32_t quality) const
{
	return save(path, m_data, m_width, m_height, m_channels, quality);
}

bool Bitmap::save(const std::string & path, unsigned char * data, int32_t width, int32_t height, int channels, uint32_t quality)
{
	/*bmp, png, jpeg, tga*/
	int n = 0;
	if (std::regex_match(path, std::regex("(.*)(.png)")))
		n = stbi_write_png(path.data(), width, height, channels, data, 0);
	else if (std::regex_match(path, std::regex("(.*)(.jpg)")) || std::regex_match(path, std::regex("(.*)(.jpeg)")))
		n = stbi_write_jpg(path.data(), width, height, channels, data, quality);
	else if (std::regex_match(path, std::regex("(.*)(.tga)")))
		n = stbi_write_tga(path.data(), width, height, channels, data);
	else
		n = stbi_write_bmp(path.data(), width, height, channels, data);
	return n != 0;
}

