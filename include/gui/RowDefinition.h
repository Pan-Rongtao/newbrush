#pragma once

#include "GridLength.h"

#include "core/Object.h"
namespace nb { namespace Gui {

class RowDefinitionCollection;
class Grid;
class GridPrivate;
class NB_EXPORT RowDefinition : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

	friend class RowDefinitionCollection;
	friend class Grid;
	friend class GridPrivate;
public:
	RowDefinition(void);
	~RowDefinition(void);

	NB_OBJECT_VALUE_PROPERTY_DECLARE(Height, GridLength);

	float GetActualHeight() const {return m_actualHeight;}
private:
	void SetActualHeight(float height) {m_actualHeight = height;}

	float m_actualHeight;
};

typedef nbObjectPtrDerive<RowDefinition, nbObjectPtr> RowDefinitionPtr;

}}
