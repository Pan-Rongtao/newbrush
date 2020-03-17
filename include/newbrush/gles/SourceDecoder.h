#pragma once
#include <map>
#include <unordered_map>
#include <string>
#include "newbrush/core/Def.h"

namespace nb{

class NB_API SourceDecoder
{
public:
	enum class VarTypeE
	{
		unknown,
		boolean,
		integer,
		real,
		vec2,
		vec3,
		vec4,
		ivec2,
		ivec3,
		ivec4,
		bvec2,
		bvec3,
		bvec4,
		mat2x2,
		mat2x3,
		mat2x4,
		mat3x2,
		mat3x3,
		mat3x4,
		mat4x2,
		mat4x3,
		mat4x4,
		structure,
	};

public:
	std::unordered_map<std::string, VarTypeE> decode(const std::string &verSource, const std::string &fragSource);
	
private:
	void decodeOne(const std::string &s, std::unordered_map<std::string, VarTypeE> &uniforms);
	std::string cutMain(const std::string &s);
	void extractStruct(const std::string &sStructDefineStr, std::string &structName, std::map<std::string, VarTypeE> &structMembers);
	void extractVar(const std::string &sVarDefineStr, std::string &varTypeName, std::string &varName, VarTypeE &varType);
	bool isBlank(char c) const;
	std::string toLower(const std::string &s) const;

	std::map<std::string, std::map<std::string, VarTypeE>>	m_structDefines;
};

}