#pragma once
#include "../gui/UIElement.h"
#include "../gui/ControlTemplate.h"
#include "../gui/Brush.h"
#include "../gui/Thickness.h"

namespace nb{ namespace gui {

using std::shared_ptr;

class NB_API Control : public UIElement
{
public:
	Control();
	virtual ~Control() = default;

	Property_rw<shared_ptr<Brush>>				Background;
	Property_rw<shared_ptr<Brush>>				BorderBrush;
	Property_rw<Thickness>						BorderThickness;
	Property_rw<Thickness>						Padding;
	Property_rw<HorizontalAlignmentE>			HorizontalContentAlignment;
	Property_rw<VerticalAlignmentE>				VerticalContentAlignment;
	Property_rw<int>							TabIndex;
	Property_rw<shared_ptr<ControlTemplate>>	Template;

	static const DependencyProperty				BackgroundProperty();
	static const DependencyProperty				BorderBrushProperty();
	static const DependencyProperty				BorderThicknessProperty();
	static const DependencyProperty				PaddingProperty();
	static const DependencyProperty				HorizontalContentAlignmentProperty();
	static const DependencyProperty				VerticalContentAlignmentProperty();
	static const DependencyProperty				TabIndexProperty();
	static const DependencyProperty				TemplateProperty();

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:

};

}}
