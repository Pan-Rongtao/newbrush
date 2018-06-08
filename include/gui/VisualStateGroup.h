#pragma once

#include "core/Object.h"
#include "VisualStateArray.h"

namespace nb { namespace Gui {

class VisualState;
class VisualStateGroupPrivate;
class NB_EXPORT VisualStateGroup : public nbObject, public nb::System::IHasChildrenArray
{
	NB_OBJECT_TYPE_DECLARE();

public:
	VisualStateGroup(const char *name="");
	virtual ~VisualStateGroup(void);

	void AddChild(VisualState *state);
	VisualState * GetChild(const char *name) const;

	void GotoState(VisualState *state);
	VisualState * GetCurrentState() const;

	int GetStateCount() const;
	std::string GetName() const {return m_name;}

	VisualStateArray * Children();

	VisualStateGroupPrivate * GetPrivate() const;

	static VisualStateGroup * FindGroup(VisualStateArray *arr);

protected:
	virtual nb::Core::InterfaceBase * GetInterfaceOverride(const std::type_info &type);

private:
	nb::System::IArray * GetChildrenArray();

	std::string m_name;

	VisualStateGroupPrivate * m_private;

	VisualStateArray m_children;
};

typedef nbObjectPtrDerive<VisualStateGroup, nbObjectPtr> VisualStateGroupPtr;

}}
