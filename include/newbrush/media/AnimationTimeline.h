#pragma once
#include "newbrush/media/Timeline.h"
#include "newbrush/core/Easing.h"
#include "newbrush/core/DependencyProperty.h"

namespace nb{

class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline() = default;

	void setTarget(std::weak_ptr<DependencyObject> target) &;
	std::weak_ptr<DependencyObject> target() const;

	void setTargetProperty(const DependencyProperty &property) &;
	const DependencyProperty &targetProperty() const;

protected:
	AnimationTimeline();

	virtual void onStateChanged() override;

private:
	std::weak_ptr<DependencyObject>	m_target;
	DependencyProperty				m_property;
};

}