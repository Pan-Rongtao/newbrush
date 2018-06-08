#pragma once

#include "core/Object.h"
#include "VisualStateGroupCollection.h"


namespace nb {

namespace Core{
class DependencyProperty;
}

namespace Gui {

class UIElement;
class VisualState;
class VisualStateGroup;
class VisualStateStoryboard;
class VisualStateManagerPrivate;
class NB_EXPORT VisualStateManager : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

public:
	VisualStateManager(void);
	virtual ~VisualStateManager(void);

	void AddGroup(VisualStateGroup *group);

	VisualStateGroup * GetGroup(const char *name) const;

	void AddStoryboard(VisualStateStoryboard *storyboard);

	VisualStateManagerPrivate * GetPrivate() const;

	void TestGotoState(VisualStateGroup *group, VisualState *state);

	NB_X_OBJECT_PROPERTY_DECLARE(VisualStateGroups, VisualStateGroupCollection);

	static VisualStateManager * FindVisualStateManager(VisualStateGroupCollection *groupArray);

private:
	void OnVisualStateGroupsChanged(Core::PropertyValueChangedEventArgs &args);

	VisualStateManagerPrivate * m_private;
};

typedef nbObjectPtrDerive<VisualStateManager, nbObjectPtr> VisualStateManagerPtr;

}}

