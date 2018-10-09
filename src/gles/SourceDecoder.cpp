#include "gles/SourceDecoder.h"
#include "core/Vec4.h"
#include "core/Matrix2x2.h"
#include "core/Matrix3x3.h"
#include "core/Matrix4x4.h"

using namespace nb::gl;

#define KEYWORD_MAIN			"main"
#define KEYWORD_UNIFORM			"uniform"
SourceDecoder::SourceDecoder()
{
	typeid(int).hash_code();
}

void SourceDecoder::decode(const std::string & verSource, const std::string & fragSource)
{
	m_Uniforms.clear();
	decodeOne(verSource);
	decodeOne(fragSource);
}

void SourceDecoder::getUniforms(std::map<std::string, size_t> &uniforms)
{
	uniforms = m_Uniforms;
}

void SourceDecoder::decodeOne(const std::string &s)
{
	size_t mainP = s.find(KEYWORD_MAIN);
	if (mainP != std::string::npos)
	{
		std::string sCutMain = s.substr(0, mainP);
		for (int i = 0; i <= sCutMain.size() - sizeof(KEYWORD_UNIFORM);)
		{
			std::string s = sCutMain.substr(i, sizeof(KEYWORD_UNIFORM));
			if (toLower(s) == KEYWORD_UNIFORM)
			{
				//+6表示后6个字符肯定不是';'，被空白符和类型、变量名占位。
				int nLineBeg = i + sizeof(KEYWORD_UNIFORM) + 6;
				int nLineEnd = s.find(nLineBeg, ';');

				size_t hash;
				std::string name;
				extractLine(s.substr(nLineBeg, nLineEnd - nLineBeg), hash, name);
				if (hash != typeid(nullptr).hash_code())
					m_Uniforms.insert(std::make_pair(name, hash));
				i = nLineEnd + 1;
			}
			else
			{
				++i;
			}
		}
	}
}

void SourceDecoder::extractLine(const std::string &sLine, size_t &hash, std::string &name)
{
	int nNameBeg = std::string::npos;
	int nTypeBeg = std::string::npos;
	int nTypeEnd = std::string::npos;
	for (int i = sLine.size() - 1; i >= 0; --i)
	{
		if (nNameBeg == std::string::npos)
		{
			if (isBlank(sLine[i]))
			{
				name = sLine.substr(i);
				nNameBeg = i;
			}
		}
		else
		{
			if (nTypeEnd == std::string::npos)
			{
				if (!isBlank(sLine[i]))
				{
					nTypeEnd = i;
				}
			}
			else
			{
				if (isBlank(sLine[i]))
				{
					nTypeBeg = i;
				}
			}
		}
		if (nTypeBeg != std::string::npos)
			break;
	}
	name = sLine.substr(nNameBeg);
	std::string sType = toLower(sLine.substr(nTypeBeg, nTypeEnd - nTypeBeg));
	if (sType == "bool")
	{
		hash = typeid(bool).hash_code();
	}
	else if (sType == "int")
	{
		hash = typeid(int).hash_code();
	}
	else if (sType == "float")
	{
		hash = typeid(float).hash_code();
	}
	else if (sType == "vec2")
	{
		hash = typeid(nb::core::Vec2).hash_code();
	}
	else if (sType == "vec3")
	{
		hash = typeid(nb::core::Vec3).hash_code();
	}
	else if (sType == "vec4")
	{
		hash = typeid(nb::core::Vec4).hash_code();
	}
	else if (sType == "mat2")
	{
		hash = typeid(nb::core::Matrix2x2).hash_code();
	}
	else if (sType == "mat3")
	{
		hash = typeid(nb::core::Matrix3x3).hash_code();
	}
	else if (sType == "mat4")
	{
		hash = typeid(nb::core::Matrix4x4).hash_code();
	}
	else
	{
		hash = typeid(nullptr).hash_code();
	}
}

bool SourceDecoder::isBlank(char c)
{
	return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v';
}

std::string SourceDecoder::toLower(const std::string &s) const
{
	std::string ret = s;
	for (int i = 0; i != ret.size(); ++i)
		if (ret[i] >= 'A' && ret[i] <= 'Z')
			ret[i] += 32;
	return ret;
}
