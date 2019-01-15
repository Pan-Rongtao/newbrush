#pragma once
#include "Program.h"

namespace nb { namespace gl{

class NB_API PrimitiveProgram : public Program
{
public:
	static std::shared_ptr<PrimitiveProgram> instance();

	PrimitiveProgram();
};

class NB_API TextureProgram : public Program
{

};

class NB_API PhongProgram : public Program
{
public:
	static std::shared_ptr<PhongProgram> instance();

	PhongProgram();
};

class NB_API CubeProgram : public Program
{
public:
	static std::shared_ptr<CubeProgram> instance();

	CubeProgram();
};

}}