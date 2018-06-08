#pragma once
#include <map>
#include "system/Size.h"
using namespace std;

namespace nb
{
	namespace Gui
	{
		class WrapPanel;
		class UIElement;
		class WrapPanelPrivate
		{
		public:
			WrapPanelPrivate(WrapPanel *owner);
			virtual ~WrapPanelPrivate(void);

			nb::System::Size ArrangeWork(const nb::System::Size &finalSize);
			nb::System::Size MeasureWork(const nb::System::Size &availableSize);
		private:			
			void SaveIndex(int nIndex, int nItemIndex);
			std::map<int, int> *m_mapIndex;//int:行号或列号索引,int:该行（列）的起始子控件索引
			WrapPanel *m_owner;
		};
	}
}
