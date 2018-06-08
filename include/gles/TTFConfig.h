#pragma once

namespace nb{ namespace gl{ namespace Gles{

struct TTFConfig
{
	std::string m_fontFilePath;
	float	m_fontSize;
	TTFConfig(const std::string & filePath = "",float size = 12.0f)
		:m_fontFilePath(filePath)
		,m_fontSize(size)
	{}
};

}}}