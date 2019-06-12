#include "core/Random.h"
#include <algorithm>
#include <time.h>
#include <float.h>

using namespace nb::core;
static std::default_random_engine g_randomEngine((unsigned int)time(nullptr));

Random::Random()
	: Random(0, 100)
{
}

Random::Random(int min, int max)
{
	setRange(min, max);
}

void Random::range(int &min, int &max) const
{
	min = m_dis.min();
	max = m_dis.max();
}

void Random::setRange(int min, int max)
{
	m_dis.param(decltype(m_dis)::param_type(std::min(min, max), std::max(min, max)));
}

int Random::get() const
{
	return const_cast<Random *>(this)->m_dis(g_randomEngine);
}

std::vector<int> Random::group(int count) const
{
	std::vector<int> ret;
	for(int i = 0;i != count; ++i)
		ret.push_back(get());
	return ret;
}

//洗牌算法
void shuffle(int a[], int n)  
{  
	int index, tmp, i;
	for(i = n - 1; i > 0; i--)  
	{  
		index = Random::get(0, i);// rand() % (n - i) + i;
		if(index != i)  
		{  
			tmp = a[i];  
			a[i] = a[index];  
			a[index] = tmp;  
		}  
	}  
}

std::vector<int> Random::groupNonRepeat(int count) const
{
	std::vector<int> ret;

	int min, max;
	range(min, max);
	int nMin = std::min(min, max);
	int nMax = std::max(min, max);
	unsigned int n = (unsigned int)nMax - (unsigned int)nMin + 1;

	//十万级内的range使用洗牌算法效率高，任何nCount消耗在0ms以内；
	if(n <= 1e5 + 1)
	{
		int *pArr = new int[n];
		for(int i = 0; i != n; ++i)
			pArr[i] = nMin + i;

		shuffle(pArr, n);
		ret.insert(ret.begin(), pArr, pArr + (std::min(n, (unsigned int)count)));
		delete []pArr;

		if((unsigned int)count > n)
		{
			std::vector<int> g = group(count - n);
			ret.insert(ret.end(), g.begin(), g.end());
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
		if(count <= 2000)	//任何range，2000个随机数获取组个加入，1s以内
		{
			while(ret.size() < (unsigned int)count)
			{
				int nOne = get();
				if(ret.size() >= n || std::find(ret.begin(), ret.end(), nOne) == ret.end())
					ret.push_back(nOne);
			}
		}
		else			
		{
			if(n <= 1e7 + 1)	//range千万级别内，且count大于2000的效率，任何nCount消耗在1s以内
			{
				int *pArr = new int[n];
				for(int i = 0; i != n; ++i)
					pArr[i] = nMin + i;

				shuffle(pArr, n);
				ret.insert(ret.begin(), pArr, pArr + (std::min(n, (unsigned int)count)));
				delete []pArr;

				if((unsigned int)count > n)
				{
					std::vector<int> g = group(count - n);
					ret.insert(ret.begin(), g.begin(), g.end());
				}
			}
			else					//千万级以上range
			{
				if(count <= 10000)
				{
					while(ret.size() < (unsigned int)count)
					{
						int nOne = get();
						if(ret.size() >= n || std::find(ret.begin(), ret.end(), nOne) == ret.end())
							ret.push_back(nOne);
					}
				}
				else			//此分支，千万级以上，不能使用洗牌算法（内存太高），不能遍历插入（效率太低），所有直接抛异常
				{
					nbThrowException(std::invalid_argument, "random range size[%d], count[%d] are refused", n, count);
				}
			}
		}
	}

	return ret;
}

int Random::get(int min, int max)
{
	return Random(min, max).get();
}

//////////////////////////////////////////////////////////////////////////
//RandomF
RandomF::RandomF()
	: RandomF(0.0, 100.0)
{
}

RandomF::RandomF(double min, double max)
{
	setRange(min, max);
}

void RandomF::setRange(double min, double max)
{
	min = std::min(min, std::nextafter(max, DBL_MAX));
	max = std::max(min, std::nextafter(max, DBL_MAX));
	m_dis.param(decltype(m_dis)::param_type(min, max));
}

void RandomF::range(double &min, double &max) const
{
	min = m_dis.min();
	max = m_dis.max();
}

double RandomF::get() const
{
	return const_cast<RandomF *>(this)->m_dis(g_randomEngine);
}

std::vector<double> RandomF::group(int count) const
{
	std::vector<double> ret;
	for(int i = 0; i != count; ++i)
		ret.push_back(get());
	return ret;
}

std::vector<double> RandomF::groupNonRepeat(int count) const
{
	double min, max;
	range(min, max);
	int nMin = (int)std::min(min, max);
	int nMax = (int)std::max(min, max);
	unsigned int n = (unsigned int)nMax - (unsigned int)nMin + 1;
	std::vector<double> ret;
	while(ret.size() < (unsigned int)count)
	{
		double fOne = get();
		if(ret.size() >= n || std::find(ret.begin(), ret.end(), fOne) == ret.end())
			ret.push_back(fOne);
	}
	return ret;
}

double RandomF::get(double min, double max)
{
	return RandomF(min, max).get();
}
