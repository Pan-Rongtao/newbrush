#include "system/GenericVariant.h"

GenericVariant::GenericVariant(void)
  : m_content(NULL)
{
}

GenericVariant::~GenericVariant(void)
{
	delete m_content;
}
