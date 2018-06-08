#pragma once

#include "UIElement.h"
#include "ControlTemplate.h"

namespace nb
{
	namespace Gui
	{
		class NameRealm;
		class ControlPrivate;

		class NB_EXPORT Control : public UIElement
		{
			NB_OBJECT_TYPE_DECLARE();

		public:
			Control(void);
			virtual ~Control(void);

			NB_X_OBJECT_PROPERTY_DECLARE(Template, ControlTemplate);

			virtual IElementRender * GetElementRender() const;
			IElementRender * GetElementRenderNoOveride() const;


			ControlPrivate * GetPrivate() const {return m_private;}

			void GotoVisualState(const char *groupName, const char *stateName);

		protected:
			virtual System::Size MeasureOverride(const System::Size &availableSize);
			virtual System::Size ArrangeOverride(const System::Size &finalSize);

			NameRealm * GetTemplateInstanceNameRealm() const;

		private:

			void OnTemplateChanged(Core::PropertyValueChangedEventArgs &args);

			ControlPrivate *m_private;
		};

		typedef nbObjectPtrDerive<Control, UIElementPtr> ControlPtr;
	}
}
