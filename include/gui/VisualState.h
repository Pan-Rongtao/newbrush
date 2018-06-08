#pragma once

#include "core/Object.h"
#include "gui/Storyboard.h"
#include "system/Array.h"

#include<set>

namespace nb { namespace Gui {


template<class T, class PtrT>
class RefObjectSet
{
public:
	RefObjectSet(){}
	RefObjectSet(T *t){m_objects.insert(t);}
	void operator |= (T *t){m_objects.insert(t);}

/*	void operator != (const RefObjectSet<T, PtrT> &set) const
	{
		if(m_objects.size() != set.m_objects.size()) return true;
		std::set<PtrT>::const_iterator itorLeft = m_objects.begin();
		std::set<PtrT>::const_iterator itorRight = set.m_objects.begin();
		for(; itorLeft != m_objects.end(); itorLeft++)
		{
			if(*itorLeft != *itorRight) return true;
		}
		return false;
	}

	void operator == (const RefObjectSet<T, PtrT> &set) const
	{
		return ! operator !=(set);
	}*/

	bool HasObject(T *object) const
	{
		return m_objects.find(object) != m_objects.end();
	}

	bool Include(RefObjectSet<T, PtrT> *set) const
	{
		NB_LINUX_STD std::set<PtrT>::const_iterator itor = set->m_objects.begin();
		for(; itor != set->m_objects.end(); itor++)
		{
			if(m_objects.find(*itor) == m_objects.end()) return false;
		}
		return true;
	}

	int GetCount() const {return m_objects.size();}

	std::set<PtrT> m_objects;
};


class VisualStateGroup;
class NB_EXPORT VisualState : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	VisualState(const char *name="");
	virtual ~VisualState(void);

	std::string GetName() const {return m_name;}

	NB_OBJECT_PROPERTY_DECLARE(Target, nbObject);
	NB_OBJECT_PROPERTY_DECLARE(TargetProperty, nb::Core::DependencyProperty);
	NB_OBJECT_PROPERTY_DECLARE(TargetValue, nb::Core::RefObject);

	NB_OBJECT_PROPERTY_DECLARE(Storyboard, nb::Media::Storyboard);

private:
	std::string m_name;
};

typedef nbObjectPtrDerive<VisualState, nbObjectPtr> VisualStatePtr;

}}
