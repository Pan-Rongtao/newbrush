#include "newbrush/core/base/Random.h"
#include <algorithm>
#include <numeric>
#include <time.h>
#include <float.h>
#include <functional>

using namespace nb;
static std::default_random_engine g_seed((unsigned int)time(nullptr));

Random::Random()
	: Random(0, 100)
{
}

Random::Random(int min, int max)
{
	setRange(min, max);
}

std::pair<int, int> Random::getRange() const
{
	return{ m_dis.min(), m_dis.max() };
}

void Random::setRange(int min, int max) &
{
	m_dis.param(decltype(m_dis)::param_type(std::min(min, max), std::max(min, max)));
}

int Random::get() const
{
	return const_cast<Random *>(this)->m_dis(g_seed);
}

int Random::get(int min, int max)
{
	setRange(min, max);
	return get();
}

std::vector<int> Random::group(uint32_t count) const
{
	std::vector<int> ret;
	try {
		ret.resize(count);
		std::generate_n(ret.begin(), count, std::bind(m_dis, g_seed));
	}
	catch (...) {
		nbThrowException(std::length_error, "count[%d] is too long for vector.", count);
	}
	return ret;
}

std::vector<int> Random::groupNonRepeat(uint32_t count, bool overflowRepeater) const
{
	auto r = getRange();
	auto range = (uint32_t)(r.second - r.first) + 1;
	std::vector<int> ret;
	try {
		ret.resize(count);
	}
	catch (...) { 
		nbThrowException(std::length_error, "count[%d] is too long for vector.", count);
	}
	if (overflowRepeater)
	{
		auto iter = ret.begin();
		while (count >= range)
		{
			std::iota(iter, iter + range, r.first);
			std::shuffle(iter, iter + range, g_seed);
			count -= range;
			iter += range;
		}
		std::iota(iter, ret.end(), r.first);
		std::shuffle(iter, ret.end(), g_seed);
	}
	else
	{
		if (count >= range)
		{
			std::iota(ret.begin(), ret.begin() + range, r.first);
			std::shuffle(ret.begin(), ret.begin() + range, g_seed);
			std::generate_n(ret.begin() + range, count - range, std::bind(m_dis, g_seed));
		}
		else
		{
			std::generate_n(ret.begin(), count, std::bind(m_dis, g_seed));
		}
	}
	return ret;
}

int Random::generate(int min, int max)
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

void RandomF::setRange(double min, double max) &
{
	min = std::min(min, std::nextafter(max, DBL_MAX));
	max = std::max(min, std::nextafter(max, DBL_MAX));
	m_dis.param(decltype(m_dis)::param_type(min, max));
}

std::pair<double, double> RandomF::getRange() const
{
	return{ m_dis.min(), m_dis.max() };
}

double RandomF::get() const
{
	return const_cast<RandomF *>(this)->m_dis(g_seed);
}

double RandomF::get(double min, double max)
{
	setRange(min, max);
	return get();
}

std::vector<double> RandomF::group(uint32_t count) const
{
	std::vector<double> ret;
	try {
		ret.resize(count);
		std::generate_n(ret.begin(), count, std::bind(m_dis, g_seed));
	}
	catch (...) {
		nbThrowException(std::length_error, "count[%d] is too long for vector.", count);
	}
	return ret;
}

double RandomF::generate(double min, double max)
{
	return RandomF(min, max).get();
}

/////////////////////////////
RandomS::RandomS()
	: RandomS(L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
{
}

RandomS::RandomS(const std::wstring & range)
	: m_range(range)
{
}

void RandomS::setRange(const std::wstring & range)
{
	m_range = range;
}

const std::wstring & RandomS::getRange() const
{
	return m_range;
}

std::wstring RandomS::get(uint32_t size) const
{
	if (m_range.empty() || size == 0)
	{
		return L"";
	}
	else
	{
		std::wstring ret(size, 0);
		std::uniform_int_distribution<int>	dis;
		dis.param(decltype(dis)::param_type(0, (int)m_range.size() - 1));
		std::generate_n(ret.begin(), size, [&]() {return m_range[dis(g_seed)]; });
		return ret;
	}
}

std::wstring RandomS::get(const std::wstring & range, uint32_t size)
{
	setRange(range);
	return get(size);
}

std::wstring RandomS::generate(const std::wstring & range, uint32_t size)
{
	return RandomS(range).get(size);
}
