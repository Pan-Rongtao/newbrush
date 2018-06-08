#pragma once

#include "UIElement.h"
#include "UIElementArray.h"
//#include "System/Array.h"

namespace nb
{
	namespace Gui
	{
		class PanelPrivate;

		class NB_EXPORT Panel : public UIElement, public nb::System::IHasChildrenArray
		{
			NB_OBJECT_TYPE_DECLARE();

		public:

			Panel(void);
			virtual ~Panel(void);

		//	void AddChild(UIElement *element);
		//	int GetChildCount() const;
		//	UIElement * GetChild(int index) const;

			PanelPrivate * GetPrivate() const {return m_pPrivate;}

			virtual IElementRender * GetElementRender() const;


			UIElementArray * Children();

		protected:
			virtual nb::Core::InterfaceBase * GetInterfaceOverride(const std::type_info &type);

		//	virtual void InvalidateMeasureOverride();
		//	virtual void InvalidateArrangeOverride();

		private:
			nb::System::IArray * GetChildrenArray();
			PanelPrivate *m_pPrivate;
		};

		typedef nbObjectPtrDerive<Panel, UIElementPtr> PanelPtr;
	}
}
