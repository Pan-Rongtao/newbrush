#include "BatchingsDrawcalls.h"
#include "system/Singleton.h"
#include "Batching.h"
#include "gles/Material.h"
#include "gles/RenderObject.h"

using nb::gl::Gles::BatchingsDrawcalls;
using nb::gl::Gles::Batching;
using nb::gl::Gles::RenderObject;
using nb::gl::Gles::Material;

BatchingsDrawcalls::BatchingsDrawcalls()
{
}

BatchingsDrawcalls::~BatchingsDrawcalls()
{
	for(int i = 0; i != m_Batchings.size(); ++i)
		delete m_Batchings[i];
}

void BatchingsDrawcalls::Charge(RenderObject *renderObject)
{
	//如果已经有相同material的batching，直接使用该batching接管renderObject，否则创建一个新的batching
	for(int i = 0; i != m_Batchings.size(); ++i)
	{
		if(renderObject->CanBatchWith(m_Batchings[i]->GetRenderObejct(0)))
		{
			m_Batchings[i]->Charge(renderObject);
			return;
		}
	}

	Batching *newBatching = new Batching();
	newBatching->Charge(renderObject);
	m_Batchings.push_back(newBatching);
}

void BatchingsDrawcalls::Eject(RenderObject *renderObject)
{

}

void BatchingsDrawcalls::UpdateModel(RenderObject *renderObject)
{
	for(int i = 0; i != m_Batchings.size(); ++i)
	{
		Batching *batching = m_Batchings[i];
		if(batching->Find(renderObject) != -1)
		{
			batching->UpdateModel(renderObject);
			break;
		}
	}
}

void BatchingsDrawcalls::UpdateMaterial(RenderObject *renderObject)
{
	for(int i = 0; i != m_Batchings.size(); ++i)
	{
		Batching *batching = m_Batchings[i];
		if(batching->Find(renderObject) != -1)
		{
			batching->UpdateModel(renderObject);
			break;
		}
	}
/*	bool bCharge = false;
	int nEject = -1;
	//如果
	for(int i = 0; i != m_Batchings.size(); ++i)
	{
		Batching *batching = m_Batchings[i];
		//如果已有batching已经有相同material，则放入这个batching
		if(!bCharge && renderObject->CanBatchWith(batching->GetRenderObejct(0)))
		{
			batching->Charge(renderObject);
			bCharge = true;
		}

		//Eject掉原来的renderObject
		if(nEject == -1 && batching->Find(renderObject) != -1)
		{
			if(renderObject->CanBatchWith(batching->GetRenderObejct(0)) == false)
			{
				batching->Eject(renderObject);
				if(batching->GetObjectsCount() == 0)
					nEject = i;
			}
		}

		//已经重新charge且找到原batching eject掉，则不必再继续循环下去
		if(bCharge && nEject != -1)
			break;
	}
	if(nEject != -1)
		m_Batchings.erase(m_Batchings.begin() + nEject);

	//还未charge则new一个batching
	if(!bCharge)
	{
		Batching *newBatching = new Batching();
		newBatching->Charge(renderObject);
		m_Batchings.push_back(newBatching);
	}
*/
}

int BatchingsDrawcalls::GetBatchingCount() const
{
	return (int)m_Batchings.size();
}

int BatchingsDrawcalls::GetRenderObjectCount() const
{
	int ret = 0;
	for(int i = 0; i != m_Batchings.size(); ++i)
		ret += m_Batchings[i]->GetObjectsCount();
	return ret;
}

void BatchingsDrawcalls::DoBatchingsDrawcalls()
{
	for(int i = 0; i != m_Batchings.size(); ++i)
	{
		m_Batchings[i]->Draw();
	}
}
