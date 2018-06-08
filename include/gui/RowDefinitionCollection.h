#pragma once


#include "core/Object.h"
#include "RowDefinition.h"
#include "system/Array.h"

//#include <vector>

namespace nb { namespace Gui {

class NB_EXPORT RowDefinitionCollection : public nb::System::ObjectArray<RowDefinition>
{
	NB_OBJECT_TYPE_DECLARE();

public:
	RowDefinitionCollection(void);
	~RowDefinitionCollection(void);

	//void Clear();
	//void RemoveAt(int index);

	//void Add(RowDefinition *row);
	//void Insert(int index, RowDefinition *row);

	//RowDefinition * GetAt(int index) const;
	//int GetCount() const;

	//RowDefinition * operator [] (int index) const {return m_rows[index];}

	NB_X_OBJECT_PROPERTY_DECLARE(Test, nbObject);


private:
//	std::vector<RowDefinitionPtr> m_rows;
	float m_measureHeight;

	//void Add(nb::Core::RefObject *value);
	//void Insert(int index, nb::Core::RefObject *value);
};

}}
