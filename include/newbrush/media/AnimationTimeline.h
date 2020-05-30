#pragma once
#include "newbrush/media/Timeline.h"
#include "newbrush/media/Easing.h"

namespace nb{

class DependencyObject;
class DependencyProperty;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;
using DependencyPropertyPtr = std::shared_ptr<DependencyProperty>;

class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline() = default;

	void setTarget(std::weak_ptr<DependencyObject> target) &;
	std::weak_ptr<DependencyObject> target() const;

	void setTargetProperty(DependencyPropertyPtr property) &;
	DependencyPropertyPtr targetProperty() const;

protected:
	AnimationTimeline();

	virtual void onStateChanged() override;

	void _unmatchThrow(std::type_index animationType);

private:
	std::weak_ptr<DependencyObject>	m_target;
	DependencyPropertyPtr			m_property;
};

}