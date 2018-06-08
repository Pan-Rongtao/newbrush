#include "Window_Internal.h"
#include "gles/Egl.h"
#include "gles/Painter.h"
#include "system/Point.h"
#include "gui/Window.h"
#include "core/Type.h"
#include "PanelPrivate.h"
#include "UIElementPrivate.h"
#include "gles/Gl.h"

using nb::Core::Boolx;
using nb::Gui::Window_Internal;
using nb::Gui::Panel;
using nb::Gui::Page;
using nb::Gui::UIElement;
using nb::Gui::BaseTrack;

Window_Internal::Window_Internal(nb::Gui::Window *owner)
: m_owner(owner)
{
	m_GLWindow = new nb::gl::egl::Window();
	try{
		m_WindowSurface = new nb::gl::egl::WindowSurface(m_GLWindow->GetWidth(), m_GLWindow->GetHeight(), m_GLWindow->GetWindowHandle());
		m_Context = new nb::gl::egl::Context(nb::gl::egl::GetCurrentConfigure());
		MakeCurrent(m_WindowSurface, m_WindowSurface, m_Context);
	}
	catch(nb::Core::ExceptionPtr &e)
	{
		NB_THROW_EXCEPTION("you should create Application before you create a nb::Gui::Window");
	}
	m_GLWindow->SetListener(this);
}

Window_Internal::~Window_Internal()
{
	delete m_GLWindow;
}

void Window_Internal::OnPrimaryAction(PrimaryAction action)
{
	nb::Gui::Window::PrimaryEventParam param;
	param.action = action;
	m_owner->PrimaryEvent.Dispatch(param);
}

void Window_Internal::OnResize(int width, int height)
{
	nb::Gui::Window::ResizeEventParam param;
	param.width = width;
	param.height = height;
	m_owner->ResizeEvent.Dispatch(param);
	nb::gl::Viewport(0, 0, width, height);
}

void Window_Internal::OnPointerAction(PointerAction action, int x, int y)
{
	printf("Window_Internal::OnPointerAction---action[%d], x[%d]-y[%d]\r\n", action, x, y);
	nb::Gui::Window::PointerEventParam param;
	param.action = action;
	param.x = x;
	param.y = y;
	m_owner->PointerEvent.Dispatch(param);
}

void Window_Internal::OnKeyAction(KeyAction action, KeyCode key, int mask)
{
	nb::Gui::Window::KeyEventParam param;
	param.action = action;
	param.keyCode = key;
	param.mask = mask;
	m_owner->PointerEvent.Dispatch(param);
}

bool Window_Internal::PointerPressOrDoubleClick(int absx, int absy)
{
	m_lstPrepTracks.clear();

	if(m_pActiveTrack != NULL)
	{
//		m_pActiveTrack->OnPointerPress(nb::System::Point(absx, absy));
		return true;
	}
	else
	{

		UIElementPtr pUIElement = m_currentPressElement;

		if(pUIElement != NULL)
		{
			if(/*pUIElement->Enable()暂时使用True*/true)
			{
				std::pair<std::multimap<UIElementPtr, BaseTrack*>::iterator, std::multimap<UIElementPtr, BaseTrack*>::iterator> pai;
				pai = m_mapTracks.equal_range(pUIElement);
				for(std::multimap<UIElementPtr, BaseTrack*>::iterator itor = pai.first; itor != pai.second; itor++)
				{
					BaseTrack* pTrack = itor->second;
					Boolx x = pTrack->Enable();
					bool bEnable = x;
					if(bEnable)
					{
						m_lstPrepTracks.push_back(pTrack);
//						pTrack->OnPointerPress(nb::System::Point(absx, absy));
					}
				}
			}
		}
	}

	return false;
}

UIElement * Window_Internal::FindParentElementOfHasTack(UIElement *element) const
{
	BaseTrack *tack = element->GetTrack();
	if(tack != NULL) return element;

	while(true)
	{
		element = element->GetPrivate()->GetParent();
		if(element == NULL) return NULL;

		tack = element->GetTrack();
		if(tack != NULL) return element;
	}

	return NULL;
}

void Window_Internal::PointerDownAction(int x, int y)
{
	m_bPointerPressed = true;
	if(m_currentPressElement == NULL) return;

	PointerPressOrDoubleClick(x, y);
	m_currentPressElement = m_currentPressElement->GetPrivate()->PointerPress();
}

void Window_Internal::PointerMoveAction(int x, int y)
{
	if(m_bPointerPressed)
	{
		if(m_pActiveTrack != NULL )
		{
			m_pActiveTrack->OnPointerMove(nb::System::Point(x, y));

			//m_MouseEventDelayMgr.Clear();
		}
		else
		{
			std::list<BaseTrackPtr>::iterator itor = m_lstPrepTracks.begin();
			for(; itor != m_lstPrepTracks.end(); itor++)
			{
				BaseTrackPtr pTrack = *itor;
				pTrack->OnPointerMove(nb::System::Point(x, y));
				if(pTrack->IsPointerActive())
				{
					m_pActiveTrack = pTrack;
					m_lstPrepTracks.clear();

					if(pTrack->MonopolizePointer())
					{
						if(m_currentPressElement != NULL)
						{
							int a = 0;
							//m_currentPressElement->CancelPointerPress();
						}

						//m_bMouseGrabber = false;
					}

					//m_MouseEventDelayMgr.Clear();
					break;
				}
			}
		}
	}
	else
	{
	}
}

void Window_Internal::PointerUpAction(int x, int y)
{
	if(m_bPointerPressed)
	{	
		if(m_pActiveTrack != NULL)
		{
			m_pActiveTrack->OnPointerRelease(nb::System::Point(x, y));
			m_pActiveTrack = NULL;
		}
		m_lstPrepTracks.clear();
		m_bPointerPressed = false;
	}
	if(m_currentPressElement != NULL)
	{
		m_currentPressElement->GetPrivate()->PointerRelease();
	}
}

void Window_Internal::SetPage(Page *page)
{
	if(page == NULL) NB_THROW_EXCEPTION("[Window_Internal::SetPage] 参数page不能为空。");

	m_page = page;
}

void Window_Internal::Render()
{
	if(m_page == NULL) return;

	int width = 800;//WindowMaster::At(0)->GetWidth();
	int height = 480;//WindowMaster::At(0)->GetHeight();

	m_page->Measure(width, height);
	m_page->Arrange(nb::System::Rect(0, 0, width, height));

	Panel *panel = m_page->GetRootPanel();
	if(panel == NULL) return;

	UIElement *pBase = panel;
	pBase->GetPrivate()->RenderWork(0, 0);
}
