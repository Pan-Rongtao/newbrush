#pragma once

#include "core/Object.h"
#include "system/Array.h"
#include "UIElement.h"

namespace nb { namespace Gui {

class UIElementArrayPrivate;
class NB_EXPORT UIElementArray : public nbObject, public nb::System::IArray
{
public:
	UIElementArray(void);
	virtual ~UIElementArray(void);

	void Add(UIElement *value);
	void Insert(int index, UIElement *value);

	void Add(UIElementPtr &value);
	void Insert(int index, UIElementPtr &value);

	void Clear();
	void RemoveAt(int index);
	virtual UIElement * GetAt(int index) const;
	UIElement * operator [](int index) const;
	int GetCount() const;

	inline UIElementArrayPrivate * GetPrivate() const {return m_private;}

private:
	UIElementArrayPrivate *m_private;

	void Add(nb::Core::RefObject *value);
	void Insert(int index, nb::Core::RefObject *value);
};

}}
