/*******************************************************
**	Storyboard
**
**	故事板
**
**	故事板与它的children都是Timeline，因此它们的时间线运作基本都是独立的。
**
**	对于duration，当Storyboard的duration影响children的duration。
**	比如，当storyboard的duration为2s，它的一个子属性动画大于2s，那这个动画将在2s时也停止，duration小于2s的则正常执行完成
**
**		潘荣涛
**
********************************************************/
#pragma once
#include "newbrush/core/media/animation/Timeline.h"

namespace nb{

class NB_API Storyboard : public Timeline
{
public:
	Storyboard();
	virtual ~Storyboard() = default;

	std::vector<TimelinePtr> &children();

	void begin();

protected:
	virtual TimeSpan getActualDurationTimespan() const override;

private:
	std::vector<TimelinePtr>	m_children;
};

using StoryboardPtr = std::shared_ptr<Storyboard>;
}
 