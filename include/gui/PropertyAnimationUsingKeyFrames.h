/*******************************************************
**	KeyFrame|PropertyAnimationUsingKeyFrames
**
**	关键帧与关键帧动画
**
**	关键帧表示在动画中处于关键状态的数据结构，它使用了时间点、
**	值和Easing这几个属性来描述一个关键帧。
**
**	而关键帧动画则包含一系列关键帧作为它动画执行的依据。它的
**	本质是关键帧组成的串行动画。
**
**
**		潘荣涛
**
********************************************************/

#pragma once
#include <set>
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "AnimationTimeline.h"
#include "../core/Easing.h"

namespace nb{ namespace gui{

template<class T>
class NB_API KeyFrame
{
public:
	KeyFrame() : KeyFrame(T(), TimeSpan(), std::make_shared<LinearEase>()) {}
	KeyFrame(const Property_rw<T> &value, const TimeSpan &keyTime) : KeyFrame(value, keyTime, std::make_shared<LinearEase>()) {}
	KeyFrame(const Property_rw<T> &value, const TimeSpan &keyTime, std::shared_ptr<EasingBase> easing) : Value(value), KeyTime(keyTime), Easing(easing) {}
	bool operator < (const KeyFrame<T> &other) const{	return KeyTime() < other.KeyTime(); }

	Property_rw<T>									Value;
	Property_rw<TimeSpan>						KeyTime;
	Property_rw<std::shared_ptr<EasingBase>>	Easing;
};

template<class T>
class NB_API PropertyAnimationUsingKeyFrames : public AnimationTimeline<T>
{
public:
	PropertyAnimationUsingKeyFrames() : KeyFrames(nullptr, nullptr) {}

	Property_rw<std::set<KeyFrame<T>>>		KeyFrames;

protected:
	virtual void progressing(float progress) override
	{
//		if (!TargetProperty || KeyFrames().empty())	return;
		//根据ticks获取当前frame，找不到表示超出了范围
		auto getCurrentFrame = [&](int64_t ticks) ->std::set<KeyFrame<T>>::iterator
		{
			for (auto iter = KeyFrames().begin(); iter != KeyFrames().end(); ++iter)
				if (ticks <= (*iter).KeyTime().totalMilliseconds())
					return iter;
			return KeyFrames().end();
		};

		int64_t ticks = (int64_t)(Duration().totalMilliseconds() * progress);
		auto curFrameIter = getCurrentFrame(ticks);
		if (curFrameIter != KeyFrames().end())
		{
/*			const KeyFrame<T> &curFrame = *curFrameIter;
			auto prevFrameIter = (curFrameIter == KeyFrames().begin()) ? KeyFrames().end() : --curFrameIter;
			T fromValue = (prevFrameIter == KeyFrames().end()) ? curFrame.Value : (*prevFrameIter).Value();
			T toValue = curFrame.Value();
			int64_t frmeBegTick = (prevFrameIter == KeyFrames().end() ? 0 : (int64_t)(*prevFrameIter).KeyTime().totalMilliseconds());
			int64_t frameEndTick = (int64_t)curFrame.KeyTime().totalMilliseconds();
			auto t = (double)(ticks - frmeBegTick) / (frameEndTick - frmeBegTick);
			auto ft = curFrame.Easing()->easeInCore(t);
			*TargetProperty = fromValue + (toValue - fromValue) * ft;*/
		}
	}
};

}}