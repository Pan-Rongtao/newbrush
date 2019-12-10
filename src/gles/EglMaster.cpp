#include "EglMaster.h"
#include "gles/Context.h"

using namespace nb;

std::vector<Context *>& EglMaster::contexts()
{
	static std::vector<Context *> g_contexs;
	return g_contexs;
}
