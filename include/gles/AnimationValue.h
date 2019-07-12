#pragma once
#include <vector>
#include "../core/Def.h"


template<class T>
class KeyFrame
{
public:
	bool operator < (const KeyFrame &other) const
	{
		return time < other.time;
	}

	float	time;
	T		v;
};

template<class T>
class AnimationValue
{
public:
	void add(float time, T v)
	{
		m_keyFrames.push_back({ time, v });
		std::sort(m_keyFrames.begin(), m_keyFrames.end());
	}

	//获取时间的上下关键帧
	void getPrevNextFramesByTime(float time, uint32_t &prevFrame, uint32_t &nextFrame)
	{
		uint32_t begin = 0;
		uint32_t end = m_keyFrames.size() - 1;

		while (begin != end)
		{
			int middle = (begin + end) / 2;
			if (m_keyFrames[middle].time < time)
			{
				begin = middle + 1;
			}
			else
			{
				end = middle;
			}
		}

		prevFrame = begin > 0 ? begin - 1 : 0;
		nextFrame = begin;
	}

	//获取时间点的插值：找到上下关键帧后的线性插值
	T getValueByTime(float time)
	{
		uint32_t numKeys = m_keyFrames.size();

		if (numKeys < 2)
		{
			return T(); // we need to have at least 2 keys
		}

		if (time <= m_keyFrames[0].time)
		{
			return m_keyFrames[0].v;
		}

		if (time >= m_keyFrames[numKeys - 1].time)
		{
			return m_keyFrames[numKeys - 1].v;
		}

		uint32_t prevFrame = 0;
		uint32_t nextFrame = 0;
		getPrevNextFramesByTime(time, prevFrame, nextFrame);

		float timeBetweenFrames = m_keyFrames[nextFrame].time - m_keyFrames[prevFrame].time;
		float percentageThroughFrame = (time - m_keyFrames[prevFrame].time) / timeBetweenFrames;

		T keyValue = m_keyFrames[nextFrame].v * percentageThroughFrame + m_keyFrames[prevFrame].v * (1.0f - percentageThroughFrame);

		return keyValue;
	}

	T getValueByDelta(float deltaTime)
	{
		uint32_t numKeys = m_keyFrames.size();

		if (numKeys < 2)
		{
			return T(); // we need to have at least 2 keys
		}

		float firstFrameTime = m_keyFrames[0].time;
		float lastFrameTime = m_keyFrames[numKeys - 1].time;

		if (m_currentTime >= lastFrameTime)
		{
			if (m_loop)
			{
				m_currentTime = firstFrameTime;
			}
			else
			{
				return m_keyFrames[numKeys - 1].v;
			}
		}

		if (m_currentTime <= firstFrameTime)
		{
			m_currentTime = firstFrameTime + deltaTime;
			return m_keyFrames[0].v;
		}

		uint32_t prevFrame = 0;
		uint32_t nextFrame = 0;
		getPrevNextFramesByTime(m_currentTime, prevFrame, nextFrame);

		float timeBetweenFrames = m_keyFrames[nextFrame].time - m_keyFrames[prevFrame].time;
		float percentageThroughFrame = timeBetweenFrames <= 0 ? 0 : (m_currentTime - m_keyFrames[prevFrame].time) / timeBetweenFrames;

		T keyValue = m_keyFrames[nextFrame].v * percentageThroughFrame + m_keyFrames[prevFrame].v * (1.0f - percentageThroughFrame);

		m_currentTime += deltaTime;

		return keyValue;
	}

	bool m_loop;
	float m_currentTime;	//0.0-1.0
	std::vector<KeyFrame<T>>	m_keyFrames;
};

