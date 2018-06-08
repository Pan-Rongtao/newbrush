#include "gui/VisualStateManager.h"
#include "VisualStateManagerPrivate.h"
#include "core/ObjectAttachmentSymbol.h"

using namespace nb::Gui;

using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(nb::Gui::VisualStateManager, nbObject, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT(VisualStateManager, VisualStateGroups, VisualStateGroupCollection, &VisualStateManager::OnVisualStateGroupsChanged);

static ObjectAttachmentSymbolPtr s_symbol = new ObjectAttachmentSymbol();

VisualStateManager::VisualStateManager(void)
{
	m_private = new VisualStateManagerPrivate();
}

VisualStateManager::~VisualStateManager(void)
{
	delete m_private;
}

VisualStateManagerPrivate * VisualStateManager::GetPrivate() const
{
	return m_private;
}

void VisualStateManager::AddGroup(VisualStateGroup *group)
{
	GetPrivate()->AddGroup(group);
}

VisualStateGroup * VisualStateManager::GetGroup(const char *name) const
{
	return GetPrivate()->GetGroup(name);
}

void VisualStateManager::AddStoryboard(VisualStateStoryboard *storyboard)
{
	GetPrivate()->AddStoryboard(storyboard);
}

void VisualStateManager::TestGotoState(VisualStateGroup *group, VisualState *state)
{
	GetPrivate()->TestGotoState(group, state);
}

void VisualStateManager::OnVisualStateGroupsChanged(PropertyValueChangedEventArgs &args)
{
	VisualStateGroupCollection *coll = dynamic_cast<VisualStateGroupCollection *>(args.m_oldObject);
	if(coll != NULL) coll->SetAttachment(s_symbol, NULL);

	coll = dynamic_cast<VisualStateGroupCollection *>(args.m_newObject);
	if(coll != NULL) coll->SetAttachment(s_symbol, this);
}

VisualStateManager * VisualStateManager::FindVisualStateManager(VisualStateGroupCollection *groupArray)
{
	return (VisualStateManager *)groupArray->GetAttachment(s_symbol);
}
