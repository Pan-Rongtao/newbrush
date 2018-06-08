#pragma once

#include "VisualState.h"
#include "system/Array.h"

namespace nb { namespace Gui {

class VisualStateArrayPrivate;
class NB_EXPORT VisualStateArray : public nb::System::ObjectArray<VisualState>// public nbObject, public nb::System::IArray 
{
	NB_OBJECT_TYPE_DECLARE();

public:
	VisualStateArray(void);
	virtual ~VisualStateArray(void);

//	void Clear();
//	void RemoveAt(int index);

//	void Add(VisualState *state);
//	void Insert(int index, VisualState *state);

//	VisualState * GetAt(int index) const;
//	int GetCount() const;

//	VisualState * operator [] (int index) const;

	VisualStateArrayPrivate * GetPrivate() const {return m_private;}

private:
	VisualStateArrayPrivate * m_private;

//	void Add(nb::Core::RefObject *value);
//	void Insert(int index, nb::Core::RefObject *value);
};

}}
