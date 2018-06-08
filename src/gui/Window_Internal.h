#pragma once
#include "system/String.h"
#include "system/WindowEvent.h"
#include "gles/Window.h"
#include "gles/Surface.h"
#include "gles/Context.h"
#include "gui/Panel.h"
#include "gui/Page.h"
#include "gui/BaseTrack.h"

namespace nb{ namespace Gui{

class Window_Internal : public nb::System::WindowEvent
{
public:
	Window_Internal(Window *owner);
	virtual ~Window_Internal();

	void SetPage(Page *page);

	void Render();

private:
	//Gles底层的窗口消息
	virtual void OnPrimaryAction(PrimaryAction action);
	virtual void OnResize(int width, int height);
	virtual void OnPointerAction(PointerAction action, int x, int y); 
	virtual void OnKeyAction(KeyAction action, KeyCode key, int mask);

	void PointerDownAction(int x, int y);
	void PointerMoveAction(int x, int y);
	void PointerUpAction(int x, int y);

	bool PointerPressOrDoubleClick(int absx, int absy);
	UIElement * FindParentElementOfHasTack(UIElement *element) const;

private:
	bool m_bPointerPressed;
	UIElementPtr m_currentPressElement;

	std::multimap<UIElementPtr, BaseTrack*> m_mapTracks;
	std::list<BaseTrackPtr> m_lstPrepTracks;
	BaseTrackPtr m_pActiveTrack;

	nb::Gui::Window				*m_owner;
	nb::gl::egl::Window			*m_GLWindow;
	nb::gl::egl::WindowSurface	*m_WindowSurface;
	nb::gl::egl::Context		*m_Context;
	PagePtr						m_page;
};

}}
