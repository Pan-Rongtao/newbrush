#pragma once

#include "core/DependencyProperty.h"


		class NB_EXPORT zzOriginObjectPtr
		{
		public:
			zzOriginObjectPtr(void){}
			zzOriginObjectPtr(const zzOriginObjectPtr &right){}
			zzOriginObjectPtr(zzOriginObjectPtr *pObject){}

			virtual ~zzOriginObjectPtr(void){}

		};


template<class T, class ParentPtrT>
class NB_EXPORT zznbObjectPtrDerive : public ParentPtrT
{

};


class NB_EXPORT nbDependencyPropertyzzPtr : public zznbObjectPtrDerive<nb::Core::DependencyProperty, zzOriginObjectPtr>
{
public:
};


namespace xxxxaa
{ 
class NB_EXPORT Testxxxx
{ 
public:
	Testxxxx(void);
	virtual ~Testxxxx(void);
	void aa();

	static nbDependencyPropertyzzPtr m_TestProperty;

	static int a;
	void zz()
	{
	//	int t = nbApplication::kx;
	}
};
}
