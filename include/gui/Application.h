#pragma once
#include "core/Object.h"
#include "core/Event.h"

namespace nb{ namespace Gui{

class Window;
class Application_Internal;
class NB_EXPORT Application : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	Application();
	virtual ~Application();

	int Run();

private:
	nb::Gui::Application_Internal	*m_internal;
};
typedef nbObjectPtrDerive<Application, nbObjectPtr> ApplicationPtr;

}}
