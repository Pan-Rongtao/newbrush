#pragma once

#include "GridLength.h"

#include "core/Object.h"
namespace nb { namespace Gui {

class Grid;
class GridPrivate;

class NB_EXPORT ColDefinition : public nbObject
{
	NB_OBJECT_TYPE_DECLARE();

	friend class Grid;
	friend class GridPrivate;
public:
	ColDefinition(void);
	~ColDefinition(void);

	NB_OBJECT_VALUE_PROPERTY_DECLARE(Width, GridLength);

	float GetActualWidth() const {return m_actualWidth;}
private:
	void SetActualWidth(float width) {m_actualWidth = width;}

	float m_actualWidth;
};

typedef nbObjectPtrDerive<ColDefinition, nbObjectPtr> ColDefinitionPtr;

}}
