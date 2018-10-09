#pragma once
#include <map>
#include <string>
#include "../core/Def.h"

namespace nb{ namespace gl{

class NB_API SourceDecoder
{
public:
	SourceDecoder();

	void decode(const std::string &verSource, const std::string &fragSource);
	
	void getUniforms(std::map<std::string, size_t> &uniforms);

private:
	void decodeOne(const std::string &s);
	void extractLine(const std::string &sLine, size_t &hash, std::string &name);
	bool isBlank(char c);
	std::string toLower(const std::string &s) const;

	std::map<std::string, size_t>	m_Uniforms;
};

} }