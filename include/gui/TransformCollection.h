#pragma once
#include "core/Object.h"
#include "RowDefinition.h"
#include "system/Array.h"
#include "Transform.h"

namespace nb { namespace Media {

	class NB_EXPORT TransformCollection : public nb::System::ObjectArray<Transform>
	{
		NB_OBJECT_TYPE_DECLARE();

	public:
		TransformCollection(void);
		~TransformCollection(void);


	};

}}
