#include "newbrush/Node2D.h"

namespace nb
{

class NB_API Panel : public Node2D
{
	RTTR_ENABLE(Node2D)
public:

};

class NB_API Canvas : public Panel
{
	RTTR_ENABLE(Panel)
public:

};

}