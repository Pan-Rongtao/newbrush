#pragma once
#include "../gui/Shape.h"

namespace nb{
namespace gui{

class NB_API Rectangle : public Shape
{
public:
	Rectangle();
	virtual ~Rectangle() = default;

	Property_rw<float>					RadiusX;			//X弧度
	Property_rw<float>					RadiusY;			//Y弧度
	static const DependencyProperty		RadiusXProperty();	//X弧度的依赖属性
	static const DependencyProperty		RadiusYProperty();	//Y弧度的依赖属性

	virtual void onRender(std::shared_ptr<gl::Context> drawContext);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

	Size	m_availableSize;
};

}}
