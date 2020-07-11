#pragma once
#include "newbrush/media/Timeline.h"

namespace nb{

class DependencyObject;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline() = default;

	static DependencyPropertyPtr TargetProperty();			//目标对象依赖属性（std::weak_ptr<DependencyObject>，默认值为空）
	static DependencyPropertyPtr TargetPropertyProperty();	//目标对象属性依赖属性（DependencyPropertyPtr，默认值为空）

protected:
	AnimationTimeline() = default;

	virtual void onStateChanged() override;

};

}