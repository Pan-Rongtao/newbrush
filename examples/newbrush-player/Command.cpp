#include "Command.h"
#include "BuildProgramCommand.h"

std::shared_ptr<Command> CommandFactory::createCommand(CommandID id)
{
	switch (id)
	{
	case Command_Shader_Build:			return std::make_shared<BuildProgramCommand>();
	case Command_Shader_Uniform_Var:	return std::make_shared<BuildProgramCommand>();
	default:							return nullptr;
	}
}
