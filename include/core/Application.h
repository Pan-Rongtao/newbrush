#pragma once

#include "ObjectPtr.h"
#include "ApplicationRealize.h"
class nbApplication;

class NB_CORE_DECLSPEC_X_INTERFACE nbCoreApplicationPtr : public nbObjectPtr
{
public:
	nbCoreApplicationPtr(void);
	virtual ~nbCoreApplicationPtr(void);

	void Run();

	nbCoreApplication * GetRealize();
//	void CreateInstance();

	nbCoreApplication * operator ->() {return GetRealize();}
	int x;

private:
	class Realize_x
	{
	};
};
