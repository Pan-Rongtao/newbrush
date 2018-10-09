#pragma once
#include "Object.h"

namespace nb { namespace core {

class NB_API ObjectAttachmentSymbol : public nbObject
{
public:
	ObjectAttachmentSymbol(void);
	virtual ~ObjectAttachmentSymbol(void);
};

typedef nbObjectPtrDerive<ObjectAttachmentSymbol, nbObjectPtr> ObjectAttachmentSymbolPtr;

}}
