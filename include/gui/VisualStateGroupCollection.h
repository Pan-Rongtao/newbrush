#pragma once

#include "VisualStateGroup.h"
#include "system/Array.h"

namespace nb { namespace Gui {

class VisualStateGroupCollectionPrivate;

class NB_EXPORT VisualStateGroupCollection : public nb::System::ObjectArray<VisualStateGroup>
{
	NB_OBJECT_TYPE_DECLARE();

public:
	VisualStateGroupCollection(void);
	virtual ~VisualStateGroupCollection(void);

//	void Clear();
//	void RemoveAt(int index);

//	void Add(VisualStateGroup *group);
//	void Insert(int index, VisualStateGroup *group);

//	VisualStateGroup * GetAt(int index) const;
//	int GetCount() const;

//	VisualStateGroup * operator [] (int index) const;

	VisualStateGroupCollectionPrivate * GetPrivate() const {return m_private;}
private:
	VisualStateGroupCollectionPrivate * m_private;

//	void Add(nb::Core::RefObject *value);
//	void Insert(int index, nb::Core::RefObject *value);
};

}}
