#pragma once


#include "core/Object.h"
#include "ColDefinition.h"
#include "system/Array.h"

#include <vector>

namespace nb { namespace Gui {

class NB_EXPORT ColDefinitionCollection : public nb::System::ObjectArray<ColDefinition>
{
	NB_OBJECT_TYPE_DECLARE();

public:
	ColDefinitionCollection(void);
	~ColDefinitionCollection(void);

	//void Clear();
	//void RemoveAt(int index);

	//void Add(ColDefinition *col);
	//void Insert(int index, ColDefinition *row);

	//ColDefinition * GetAt(int index) const;
	//int GetCount() const;

	//ColDefinition * operator [] (int index) const {return m_cols[index];}

private:
	//std::vector<ColDefinitionPtr> m_cols;
	float m_measureWidth;

	//void Add(nb::Core::RefObject *value);
	//void Insert(int index, nb::Core::RefObject *value);

};

}}
