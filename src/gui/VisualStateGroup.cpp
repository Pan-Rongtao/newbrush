#include "gui/VisualStateGroup.h"
#include "VisualStateGroupPrivate.h"
#include "core/ObjectAttachmentSymbol.h"

using namespace nb::Gui;
using namespace nb::Core;
using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(VisualStateGroup, nbObject, NULL, NULL);


static ObjectAttachmentSymbolPtr s_symbol = new ObjectAttachmentSymbol();

VisualStateGroup::VisualStateGroup(const char *name)
	: m_name(name)
{
	m_private = new VisualStateGroupPrivate();
	m_children.SetAttachment(s_symbol, this);
}

VisualStateGroup::~VisualStateGroup(void)
{
	delete m_private;
}

void VisualStateGroup::AddChild(VisualState *state)
{
	GetPrivate()->AddChild(state);
}

VisualState * VisualStateGroup::GetChild(const char *name) const
{
	return GetPrivate()->GetChild(name);
}

VisualStateGroupPrivate * VisualStateGroup::GetPrivate() const
{
	return m_private;
}

void VisualStateGroup::GotoState(VisualState *state)
{
	GetPrivate()->GotoState(state);

#ifdef WIN32
	StoryboardPtr s = state->Storyboard();
#else
	Storyboard *s = state->Storyboard();
#endif
	if(s != NULL) s->Begin();
}

VisualState * VisualStateGroup::GetCurrentState() const
{
	return GetPrivate()->GetCurrentState();
}

int VisualStateGroup::GetStateCount() const
{
	return GetPrivate()->GetStateCount();
}

nb::System::IArray * VisualStateGroup::GetChildrenArray()
{
	return &m_children;
}

VisualStateArray * VisualStateGroup::Children()
{
	return &m_children;
}

nb::Core::InterfaceBase * VisualStateGroup::GetInterfaceOverride(const std::type_info &type)
{
	std::string typeName = type.name();

	if(typeName == typeid(nb::System::IHasChildrenArray).name())
	{
		return dynamic_cast<nb::System::IHasChildrenArray *>(this);
	}
	else
	{
		return NULL;
	}
}

VisualStateGroup * VisualStateGroup::FindGroup(VisualStateArray *arr)
{
	return (VisualStateGroup *)arr->GetAttachment(s_symbol);
}
