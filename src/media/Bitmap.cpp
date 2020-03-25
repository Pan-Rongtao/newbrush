#include "newbrush/media/Bitmap.h"
#include <regex>
#include "SOIL.h"
#include "newbrush/core/Def.h"

using namespace nb;

Bitmap::Bitmap()
	: m_data(nullptr)
	, m_width(0)
	, m_height(0)
	, m_channels(0)
{
}

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
	SOIL_free_image_data(m_data);
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
	SOIL_free_image_data(m_data);
	m_data = new unsigned char[other.bytes()];
	memcpy(m_data, other.data(), other.bytes());
	m_width = other.width();
	m_height = other.height();
	m_channels = other.channels();
}

void Bitmap::load(const std::string &path)
{
	SOIL_free_image_data(m_data);
	m_data = SOIL_load_image(path.data(), &m_width, &m_height, &m_channels, SOIL_LOAD_RGB);
	if (!m_data)
	{
		m_width = 0;
		m_height = 0;
		m_channels = 0;
	}
}

void Bitmap::load(const unsigned char *buffer, uint32_t bytes)
{
	SOIL_free_image_data(m_data);
	m_data = SOIL_load_image_from_memory(buffer, bytes, &m_width, &m_height, &m_channels, SOIL_LOAD_RGB);
	if (!m_data)
	{
		m_width = 0;
		m_height = 0;
		m_channels = 0;
	}
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
	nbThrowException(std::logic_error, "Unimplemented method");
	//unsigned char *newData = new unsigned char[width * height * channels()];
	//int n /*= stbir_resize_uint8(m_data, m_width, m_height, 0, newData, width, height, 0, channels())*/;
	//SOIL_free_image_data(m_data);
	//m_data = newData;
	//m_width = width;
	//m_height = height;
	//return n != 0;
}

bool Bitmap::save(const std::string &path, uint32_t quality) const
{
	nbThrowException(std::logic_error, "Unimplemented method");
	/*bmp, png, jpeg, tga*/
	int n = 0;
	//if (std::regex_match(path, std::regex("(.*)(.dds)")))
	//	n = stbi_write_png(path.data(), m_width, m_height, m_channels, m_data, 0);
	//else if (std::regex_match(path, std::regex("(.*)(.jpg)")) || std::regex_match(path, std::regex("(.*)(.jpeg)")))
	//	n = stbi_write_jpg(path.data(), m_width, m_height, m_channels, m_data, quality);
	//else if (std::regex_match(path, std::regex("(.*)(.tga)")))
	//	n = stbi_write_tga(path.data(), m_width, m_height, m_channels, m_data);
	//else
	//	n = stbi_write_bmp(path.data(), m_width, m_height, m_channels, m_data);
	return n != 0;
}
