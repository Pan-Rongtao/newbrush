#pragma once

#include "Object.h"
#include "ObjectPtr.h"




class NB_CORE_DECLSPEC_X_INTERFACE nbCoreApplication : public nbObject
{
public:
	nbCoreApplication(void);
	void Run();
	static nbCoreApplication *GetInstance();

	static void InitGlobal();

protected:
	virtual ~nbCoreApplication(void);
};
