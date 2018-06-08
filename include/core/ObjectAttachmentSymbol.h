#pragma once

#include "Object.h"

namespace nb { namespace Core {

class NB_CORE_DECLSPEC_X_INTERFACE ObjectAttachmentSymbol : public nbObject
{
public:
	ObjectAttachmentSymbol(void);
	virtual ~ObjectAttachmentSymbol(void);
};

typedef nbObjectPtrDerive<ObjectAttachmentSymbol, nbObjectPtr> ObjectAttachmentSymbolPtr;

}}
