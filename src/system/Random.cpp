#include "system/Random.h"
#include "system/System.h"
#include "system/Global.h"
#include <algorithm>
#include <time.h>
#include <assert.h>

//是否初始化了随机种子，全局变量，只需要初始化一次即可
bool g_bInitRandomSeed = false;
#define RANDOM_MAX_RANGE	32767
using namespace nb::System;
Random::Random()
{
	SetRange(0, 100);
	if(g_bInitRandomSeed == false)
	{
		srand((unsigned int)time(NULL));
		g_bInitRandomSeed = true;
	}
}

Random::Random(int nMin, int nMax)
{
	SetRange(nMin, nMax);
	if(g_bInitRandomSeed == false)
	{
		srand((unsigned int)time(NULL));
		g_bInitRandomSeed = true;
	}
}

void Random::GetRange(int &nMin, int &nMax) const
{
	nMin = m_nMin;
	nMax = m_nMax;
}

void Random::SetRange(int nMin, int nMax)
{
	//rewrite when define
	assert(nb::System::Abs(nMax - nMin) <= MaxRange());
	m_nMin = nMin;
	m_nMax = nMax;
}

int Random::GetOne() const
{
	int nMin = nb::System::Min(m_nMin, m_nMax);
	int nMax = nb::System::Max(m_nMin, m_nMax);
	unsigned int n = (unsigned int)nMax - (unsigned int)nMin + 1;

	return rand() % n + nMin;
}

std::vector<int> Random::GetGroup(int nCount) const
{
	//rewrite when define assert
	assert(nCount >= 0 && nCount <= 1e6);

	std::vector<int> vtRandom;
	for(int i = 0;i != nCount; ++i)
		vtRandom.push_back(GetOne());
	return vtRandom;
}

//洗牌算法
void Shuffle(int a[], int n)  
{  
	int index, tmp, i;
	for(i = 0; i < n; i++)  
	{  
		index = rand() % (n - i) + i;  
		if(index != i)  
		{  
			tmp = a[i];  
			a[i] = a[index];  
			a[index] = tmp;  
		}  
	}  
}

std::vector<int> Random::GetGroupNonRepeat(int nCount) const
{
	//rewrite when define assert
	assert(nCount >= 0 && nCount <= 1e6);

	std::vector<int> vtRandom;

	int nMin = nb::System::Min(m_nMin, m_nMax);
	int nMax = nb::System::Max(m_nMin, m_nMax);
	unsigned int n = (unsigned int)nMax - (unsigned int)nMin + 1;

	//十万级内的range使用洗牌算法效率高，任何nCount消耗在0ms以内；
	if(n <= 1e5 + 1)
	{
		int *pArr = new int[n];
		for(int i = 0; i != n; ++i)
			pArr[i] = nMin + i;

		Shuffle(pArr, n);
		vtRandom.insert(vtRandom.begin(), pArr, pArr + (nb::System::Min(n, (unsigned int)nCount)));
		delete []pArr;

		if((unsigned int)nCount > n)
		{
			std::vector<int> group = GetGroup(nCount - n);
			vtRandom.insert(vtRandom.begin(), group.begin(), group.end());
		}
	}
	////////////////////////////////////////////////////
	//	由于目前MaxRange()限定在内的方式，所以n必定小于1e5 + 1，
	//	因此不会走到else分支保留else代码，假若之后MaxRange()变大，
	//	有超过1e5+1的可能，则要走到else 分支
	////////////////////////////////////////////////////
	//
	//千万级内的range且nCount大于2000的效率，任何nCount消耗在1s以内
	//
	else
	{
		if(nCount <= 2000)	//任何range，2000个随机数获取组个加入，1s以内
		{
			while(vtRandom.size() < (unsigned int)nCount)
			{
				int nOne = GetOne();
				if(vtRandom.size() >= n || std::find(vtRandom.begin(), vtRandom.end(), nOne) == vtRandom.end())
					vtRandom.push_back(nOne);
			}
		}
		else			
		{
			if(n <= 1e7 + 1)	//range千万级别内，且count大于2000的效率，任何nCount消耗在1s以内
			{
				int *pArr = new int[n];
				for(int i = 0; i != n; ++i)
					pArr[i] = nMin + i;

				Shuffle(pArr, n);
				vtRandom.insert(vtRandom.begin(), pArr, pArr + (nb::System::Min(n, (unsigned int)nCount)));
				delete []pArr;

				if((unsigned int)nCount > n)
				{
					std::vector<int> group = GetGroup(nCount - n);
					vtRandom.insert(vtRandom.begin(), group.begin(), group.end());
				}
			}
			else					//千万级以上range
			{
				if(nCount <= 10000)
				{
					while(vtRandom.size() < (unsigned int)nCount)
					{
						int nOne = GetOne();
						if(vtRandom.size() >= n || std::find(vtRandom.begin(), vtRandom.end(), nOne) == vtRandom.end())
							vtRandom.push_back(nOne);
					}
				}
				else			//此分支，千万级以上，不能使用洗牌算法（内存太高），不能遍历插入（效率太低），所有直接抛异常
				{
					assert(0);
				}
			}
		}
	}

	return vtRandom;
}

int Random::GenerateOne(int nMin, int nMax)
{
	return Random(nMin, nMax).GetOne();
}

//由于不同编译器的RAND_MAX不同，所以固定RangeMax=RANDOM_MAX_RANGE
int Random::MaxRange()
{
	return RANDOM_MAX_RANGE;
}

////////////
//////////////////////////////////////////////////////////////////////////
//RandomF
RandomF::RandomF()
{
	SetRange(0.0f, 1.0f);
	if(g_bInitRandomSeed == false)
	{
		srand((unsigned int)time(NULL));
		g_bInitRandomSeed = true;
	}
}

RandomF::RandomF(float fMin, float fMax)
{
	SetRange(fMin, fMax);
	if(g_bInitRandomSeed == false)
	{
		srand((unsigned int)time(NULL));
		g_bInitRandomSeed = true;
	}
}

void RandomF::SetRange(float fMin, float fMax)
{
	//rewrite when define
	assert(nb::System::Abs(fMax - fMin) <= MaxRange());
	m_fMin = fMin;
	m_fMax = fMax;
}

void RandomF::GetRange(float &fMin, float &fMax) const
{
	fMin = m_fMin;
	fMax = m_fMax;
}

float RandomF::GetOne() const
{
	float fMin = nb::System::Min(m_fMin, m_fMax);
	float fMax = nb::System::Max(m_fMin, m_fMax);

	int nMin = (int)nb::System::Floor(fMin);
	int nMax = (int)nb::System::Floor(fMax);
	if(nb::System::ApproximatelyEqual((float)nMax, fMax))
		nMax -= 1;

	Random rnd(nMin, nMax);
	int nIntV = rnd.GetOne();
	int nMantissa = 0;
	if(nIntV == nMin && fMin < nMin)
	{
		float f = fMin - (int)fMin;
		Random rm(0, (int)(f * 10000));
		nMantissa = rm.GetOne();
		
	}
	else if(nIntV == (int)fMax && fMax > nMax)
	{
		Random rm(0, (int)((fMax - (int)fMax) * 10000));
		nMantissa = rm.GetOne();
	}
	else
	{
		Random rm(0, 10000);
		nMantissa = rm.GetOne();
	}
	if(nIntV < 0)
		nMantissa = -nMantissa;
	if(nIntV < 0)
		nIntV += 1;

	float fRet = (float)nIntV + (float)nMantissa / 10000;

	if(fRet < fMin)
		fRet = fMin;
	else if(fRet > fMax)
		fRet = fMax;
	
	return fRet;
}

std::vector<float> RandomF::GetGroup(int nCount) const
{
	//rewrite when define assert
	assert(nCount >= 0 && nCount <= 1e6);

	std::vector<float> vtRandom;
	for(int i = 0; i != nCount; ++i)
		vtRandom.push_back(GetOne());
	return vtRandom;
}

std::vector<float> RandomF::GetGroupNonRepeat(int nCount) const
{
	//rewrite when define assert
	assert(nCount >= 0 && nCount <= 1e6);

	int nMin = (int)nb::System::Min(m_fMin, m_fMax);
	int nMax = (int)nb::System::Max(m_fMin, m_fMax);
	unsigned int n = (unsigned int)nMax - (unsigned int)nMin + 1;
	std::vector<float> vtRandom;
	while(vtRandom.size() < (unsigned int)nCount)
	{
		float fOne = GetOne();
		if(vtRandom.size() >= n || std::find(vtRandom.begin(), vtRandom.end(), fOne) == vtRandom.end())
			vtRandom.push_back(fOne);
	}
	return vtRandom;
}

float RandomF::GenerateOne(float fMin, float fMax)
{
	return RandomF(fMin, fMax).GetOne();
}

float RandomF::MaxRange()
{
	return (float)RANDOM_MAX_RANGE;
}
