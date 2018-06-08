#pragma once
#include "core/Object.h"
#include "core/Event.h"
#include "system/String.h"
#include "system/WindowEvent.h"
#include "gui/Panel.h"
#include "gui/Page.h"

namespace nb{ namespace Gui{

class Panel;
class Page;
class Window_Internal;

class NB_EXPORT Window : public nbObject
{
public:
	Window();
	virtual ~Window();

	void SetPage(Page *page);

	void Render();

public:
	//初始事件
	struct PrimaryEventParam : public nbEventParamT<Window> { nb::System::WindowEvent::PrimaryAction action; };
	nbEvent<PrimaryEventParam>	PrimaryEvent;

	//大小重置事件
	struct ResizeEventParam : public nbEventParamT<Window> { int width; int height; };
	nbEvent<ResizeEventParam>	ResizeEvent;

	//Pointer事件
	struct PointerEventParam : public nbEventParamT<Window> { nb::System::WindowEvent::PointerAction action; int x; int y; };
	nbEvent<PointerEventParam>	PointerEvent;

	//键盘事件
	struct KeyEventParam : public nbEventParamT<Window> { nb::System::WindowEvent::KeyAction action; nb::System::WindowEvent::KeyCode keyCode; int mask; };
	nbEvent<KeyEventParam>		KeyEvent;

private:
	Window_Internal		*m_internal;
};

typedef nbObjectPtrDerive<Window, nbObjectPtr>	WindowPtr;

}}
