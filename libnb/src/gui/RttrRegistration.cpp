#include "newbrush/gui/RttrRegistration.h"
#include "newbrush/core/Log.h"
#include "newbrush/core/data/Binding.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/panels/Panel.h"
#include "newbrush/gui/panels/Canvas.h"
#include "newbrush/gui/panels/DockPanel.h"
#include "newbrush/gui/panels/WrapPanel.h"
#include "newbrush/gui/panels/StackPanel.h"
#include "newbrush/gui/panels/Grid.h"
#include "newbrush/gui/panels/UniformGrid.h"
#include "newbrush/gui/controls/Button.h"
#include "newbrush/gui/controls/RepeatButton.h"
#include "newbrush/gui/controls/Image.h"
#include "newbrush/gui/controls/TextBlock.h"
#include "newbrush/gui/shapes/Line.h"
#include "newbrush/gui/shapes/Polyline.h"
#include "newbrush/gui/shapes/Polygon.h"
#include "newbrush/gui/shapes/Path.h"
#include "newbrush/gui/shapes/Rectangle.h"
#include "newbrush/gui/shapes/Ellipse.h"
#include "newbrush/core/media/Color.h"
#include "newbrush/core/media/ImageBrush.h"
#include "newbrush/core/base/DateTime.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/media/ImageSource.h"
#include "newbrush/core/base/Thickness.h"

using namespace nb;
using namespace rttr;

std::map<std::string, PropertyCategory> PropertyCategory::s_propertyCategorys;

ClassDescriptor::ClassDescriptor(const std::string & category, const std::string & dispayName, const std::string & description)
	: m_category(category)
	, m_displayName(dispayName)
	, m_description(description)
{
}

const std::string & ClassDescriptor::category() const
{
	return m_category;
}

const std::string & ClassDescriptor::displayName() const
{
	return m_displayName;
}

const std::string & ClassDescriptor::description() const
{
	return m_description;
}

Range::Range(var lowerBound, var upperBound, var step)
	: m_lowerBound(lowerBound)
	, m_upperBound(upperBound)
	, m_step(step)
{
}

var Range::lowerBound() const
{
	return m_lowerBound;
}

var Range::upperBound() const
{
	return m_upperBound;
}

var Range::step() const
{
	return m_step;
}

const std::string & PropertyCategory::name() const
{
	return m_name;
}

int PropertyCategory::order() const
{
	return m_order;
}

const std::map<std::string, PropertyCategory>& PropertyCategory::getAll()
{
	return s_propertyCategorys;
}

const PropertyCategory &PropertyCategory::get(const std::string & name, int order)
{
	PropertyCategory newPC;
	newPC.m_name = name;
	newPC.m_order = order;
	auto ret = s_propertyCategorys.insert({ name, newPC });
	return ret.first->second;
}

const PropertyCategory &PropertyCategory::brush()
{
	return PropertyCategory::get("画笔", 0);
}

const PropertyCategory &PropertyCategory::appearance()
{
	return PropertyCategory::get("外观", 1);
}

const PropertyCategory &PropertyCategory::common()
{
	return PropertyCategory::get("公共", 2);
}

const PropertyCategory &PropertyCategory::automation()
{
	return PropertyCategory::get("自动化", 3);
}

const PropertyCategory &PropertyCategory::layout()
{
	return PropertyCategory::get("布局", 4);
}

const PropertyCategory &PropertyCategory::text()
{
	return PropertyCategory::get("文本", 5);
}

const PropertyCategory &PropertyCategory::transform()
{
	return PropertyCategory::get("转换", 6);
}

const PropertyCategory &PropertyCategory::misc()
{
	return PropertyCategory::get("杂项", 7);
}

const PropertyCategory &PropertyCategory::custom()
{
	return PropertyCategory::get("自定义", 8);
}

//enum类型需要主动注册，因为需要把枚举值注册
//控件类型需主动注册，因为需要注册构造函数和metadata
//作为Property的属性值类型不要主动注册，让RTTR自动生成（用到什么就会自动生成什么）

RTTR_REGISTRATION
{
//	RttrRegistration::doRegister();
}

PropertyDescriptor::PropertyDescriptor(DependencyPropertyPtr dp, const PropertyCategory &category, const std::string & description, int order, RangePtr range)
	: m_property(dp)
	, m_category(category)
	, m_description(description)
	, m_order(order)
	, m_range(range)
{
}

const DependencyPropertyPtr &PropertyDescriptor::property() const
{
	return m_property;
}

const PropertyCategory &PropertyDescriptor::category() const
{
	return m_category;
}

const std::string &PropertyDescriptor::description() const
{
	return m_description;
}

int PropertyDescriptor::order() const
{
	return m_order;
}

const RangePtr &PropertyDescriptor::range() const
{
	return m_range;
}

std::vector<PropertyDescriptorPtr> RttrRegistration::getTypeSelfPropertys(rttr::type t)
{
	std::vector<PropertyDescriptorPtr> ret;
	for (auto i = (int)RttrMetadataIndex::Property0; i <= (int)RttrMetadataIndex::PropertyMax; ++i)
	{
		var vPropertyDescriptor = t.get_metadata((RttrMetadataIndex)i);
		type ttt = vPropertyDescriptor.get_type();
		if (vPropertyDescriptor.is_type<PropertyDescriptorPtr>())
		{
			const auto &one = vPropertyDescriptor.get_value<PropertyDescriptorPtr>();
			ret.push_back(one);
		}
		else
		{
			if (vPropertyDescriptor.is_valid())
			{
				Log::error("[%s]'s metadata[%d] must be set as [DependencyPropertyPtr] type", t.get_name().data(), i);
			}
		}
	}
	return ret;
}

std::vector<PropertyDescriptorPtr> RttrRegistration::getTypeAllPropertys(rttr::type t)
{
	std::vector<PropertyDescriptorPtr> ret;
	auto selfPropertyDescriptors = getTypeSelfPropertys(t);
	ret.insert(ret.end(), selfPropertyDescriptors.begin(), selfPropertyDescriptors.end());

	auto baseClassesRange = t.get_base_classes();
	for (auto base : baseClassesRange)
	{
		auto pros = getTypeSelfPropertys(base);
		ret.insert(ret.end(), pros.begin(), pros.end());
	}
	return ret;
}

void RttrRegistration::doRegister()
{
	static bool registered = false;
	if (registered)	return;

	auto t0 = nb::getTickCount();
	registerEnums();
	auto t1 = nb::getTickCount();
	Log::info("register enum cost [%d] ms.", (int)(t1 - t0));
	registerUIElementTypes();
	auto t2 = nb::getTickCount();
	Log::info("register UIElement types cost [%d] ms.", (int)(t2 - t1));
	registerConverters();
	auto t3 = nb::getTickCount();
	Log::info("register Converters cost [%d] ms.", (int)(t3 - t2));
	registered = true;
	Log::info("Rttr doRegister cost [%d] ms.", (int)(t3 - t0));
}

void RttrRegistration::registerEnums()
{
	registration::enumeration<StretchE>("nb::StretchE")
	(
		value("Origion", StretchE::Origion),
		value("Fill", StretchE::Fill),
		value("Uniform", StretchE::Uniform),
		value("UniformToFill", StretchE::UniformToFill)
	);

	registration::enumeration<VisibilityE>("nb::VisibilityE")
	(
		value("Hidden", VisibilityE::Hidden),
		value("Visible", VisibilityE::Visible),
		value("Collapsed", VisibilityE::Collapsed)
	);

	registration::enumeration<HorizontalAlignmentE>("nb::HorizontalAlignmentE")
	(
		value("Left", HorizontalAlignmentE::Left),
		value("Center", HorizontalAlignmentE::Center),
		value("Right", HorizontalAlignmentE::Right),
		value("Stretch", HorizontalAlignmentE::Stretch)
	);

	registration::enumeration<VerticalAlignmentE>("nb::VerticalAlignmentE")
	(
		value("Top", VerticalAlignmentE::Top),
		value("Center", VerticalAlignmentE::Center),
		value("Bottom", VerticalAlignmentE::Bottom),
		value("Stretch", VerticalAlignmentE::Stretch)
	);

	registration::enumeration<FlowDirectionE>("nb::FlowDirectionE")
	(
		value("LeftToRight", FlowDirectionE::LeftToRight),
		value("RightToLeft", FlowDirectionE::RightToLeft)
	);

	registration::enumeration<FontStyleE>("nb::FontStyleE")
	(
		value("Normal", FontStyleE::Normal),
		value("Italic", FontStyleE::Italic),
		value("Oblique", FontStyleE::Oblique)
	);

	registration::enumeration<FontStretchE>("nb::FontStretchE")
	(
		value("Condensed", FontStretchE::Condensed),
		value("Expanded", FontStretchE::Expanded),
		value("ExtraCondensed", FontStretchE::ExtraCondensed),
		value("ExtraExpanded", FontStretchE::ExtraExpanded),
		value("Medium", FontStretchE::Medium),
		value("Normal", FontStretchE::Normal),
		value("SemiCondensed", FontStretchE::SemiCondensed),
		value("SemiExpanded", FontStretchE::SemiExpanded),
		value("UltraCondensed", FontStretchE::UltraCondensed),
		value("UltraExpanded", FontStretchE::UltraExpanded)
	);

	registration::enumeration<TextAlignmentE>("nb::TextAlignmentE")
	(
		value("Left", TextAlignmentE::Left),
		value("Right", TextAlignmentE::Right),
		value("Center", TextAlignmentE::Center),
		value("Justify", TextAlignmentE::Justify)
	);

	registration::enumeration<TextWrappingE>("nb::TextWrappingE")
	(
		value("NoWrap", TextWrappingE::NoWrap),
		value("Wrap", TextWrappingE::Wrap),
		value("WrapWithOverflow", TextWrappingE::WrapWithOverflow)
	);

	registration::enumeration<TextTrimmingE>("nb::TextTrimmingE")
	(
		value("None", TextTrimmingE::None),
		value("CharacterEllipsis", TextTrimmingE::CharacterEllipsis),
		value("WordEllipsis", TextTrimmingE::WordEllipsis)
	);
	
	registration::enumeration<TextDecorationE>("nb::TextDecorationE")
	(
		value("OverLine", TextDecorationE::OverLine),
		value("Strikethrough", TextDecorationE::Strikethrough),
		value("Baseline", TextDecorationE::Baseline),
		value("Underline", TextDecorationE::Underline)
	);

	registration::enumeration<OrientationE>("nb::OrientationE")
	(
		value("Horizontal", OrientationE::Horizontal),
		value("Vertical", OrientationE::Vertical)
	);

	registration::enumeration<WindowStyleE>("nb::WindowStyleE")
	(
		value("None", WindowStyleE::None),
		value("Fixed", WindowStyleE::Fixed),
		value("SizeBox", WindowStyleE::SizeBox)
	);

	registration::enumeration<WindowStateE>("nb::WindowStateE")
	(
		value("Normal", WindowStateE::Normal),
		value("Maximized", WindowStateE::Maximized),
		value("Minimized", WindowStateE::Minimized)
	);

	registration::enumeration<PenLineCapE>("nb::PenLineCapE")
	(
		value("Flat", PenLineCapE::Flat),
		value("Round", PenLineCapE::Round),
		value("Square", PenLineCapE::Square),
		value("Triangle", PenLineCapE::Triangle)
	);

	registration::enumeration<PenLineJoinE>("nb::PenLineCapE")
	(
		value("Beval", PenLineJoinE::Beval),
		value("Miter", PenLineJoinE::Miter),
		value("Round", PenLineJoinE::Round)
	);
	
	registration::enumeration<ClickModeE>("nb::ClickModeE")
	(
		value("Hover", ClickModeE::Hover),
		value("Press", ClickModeE::Press),
		value("Release", ClickModeE::Release)
	);
	
	registration::enumeration<DockE>("nb::DockE")
	(
		value("Left", DockE::Left),
		value("Right", DockE::Right),
		value("Top", DockE::Top),
		value("Bottom", DockE::Bottom)
	);

}

void RttrRegistration::registerUIElementTypes()
{
	registration::class_<UIElement>("nb::UIElement")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, UIElement::NameProperty(), PropertyCategory::common(), "元素的名字，同级元素不可同名", 0),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, UIElement::VisibilityProperty(), PropertyCategory::appearance(), "元素的可见性", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, UIElement::OpacityProperty(), PropertyCategory::appearance(), "元素的不透明度系数", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, UIElement::FocusableProperty(), PropertyCategory::appearance(), "是否允许元素可获得焦点", 7),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property4, UIElement::WidthProperty(), PropertyCategory::appearance(), "元素的宽度", 0),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property5, UIElement::HeightProperty(), PropertyCategory::appearance(), "元素的高度", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property7, UIElement::MinWidthProperty(), PropertyCategory::appearance(), "元素的最小宽度约束", 6),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property8, UIElement::MinHeightProperty(), PropertyCategory::appearance(), "元素的最小高度约束", 7),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property9, UIElement::MaxWidthProperty(), PropertyCategory::appearance(), "元素的最大宽度约束", 8),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property10, UIElement::MaxHeightProperty(), PropertyCategory::appearance(), "元素的最大高度约束", 9),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property11, UIElement::MarginProperty(), PropertyCategory::appearance(), "元素的外边距，指与其他相邻元素之间的间距", 5),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property12, UIElement::HorizontalAlignmentProperty(), PropertyCategory::appearance(), "在父元素（如Panel或项控件）中组合此元素时所应用的水平对齐特征", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property13, UIElement::VerticalAlignmentProperty(), PropertyCategory::appearance(), "在父元素（如Panel或项控件）中组合此元素时所应用的垂直特征", 4),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property14, UIElement::FlowDirectionProperty(), PropertyCategory::appearance(), "方向，文本和其他元素在任何控制其布局的父元素中都按此方向流动", 12),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property15, UIElement::RenderTransformProperty(), PropertyCategory::transform(), "渲染变换", 1)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Control>("nb::Control")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Control::BackgroundProperty(), PropertyCategory::brush(), "描述元素背景的画笔", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Control::BorderBrushProperty(), PropertyCategory::brush(), "描述元素边框背景的画笔", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Control::BorderThicknessProperty(), PropertyCategory::appearance(), "元素边框的粗细", 4),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, Control::FontFamilyProperty(), PropertyCategory::text(), "字体名称", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property4, Control::FontSizeProperty(), PropertyCategory::text(), "字号", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property5, Control::FontStretchProperty(), PropertyCategory::text(), "字体在屏幕上缩紧或加宽的程度", 6),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property7, Control::FontStyleProperty(), PropertyCategory::text(), "字形", 7),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property8, Control::FontWeightProperty(), PropertyCategory::text(), "字体粗细", 8),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property9, Control::ForegroundProperty(), PropertyCategory::brush(), "前景色画笔", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property10, Control::PaddingProperty(), PropertyCategory::layout(), "控件内部的填充边距，指在对象和其他边距或边框之间插入的边距", 21),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property11, Control::HorizontalContentAlignmentProperty(), PropertyCategory::layout(), "元素内容的水平对齐方式", 15),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property12, Control::VerticalContentAlignmentProperty(), PropertyCategory::layout(), "元素内容的垂直对齐方式", 18),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property13, Control::TabIndexProperty(), PropertyCategory::common(), "元素的逻辑定位顺序", 18),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property14, Control::IsTabStopProperty(), PropertyCategory::common(), "是否是Tab键停止点", 17),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property15, Control::TemplateProperty(), PropertyCategory::common(), "模板", 19)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<ContentControl>("nb::ContentControl")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, ContentControl::ContentProperty(), PropertyCategory::common(), "元素的内容", 1)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Image>("nb::Image")
	(
		ClassDescriptorMetadata("其他", "Image", "图片，可设置多种适应模式"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Image::SourceProperty(), PropertyCategory::common(), "图像源", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Image::StretchProperty(), PropertyCategory::common(), "拉伸或填充的方式", 2)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<TextBlock>("nb::TextBlock")
	(
		ClassDescriptorMetadata("其他", "TextBlock", "画布，内部元素使用绝对坐标进行布局"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, TextBlock::BackgroundProperty(), PropertyCategory::brush(), "元素背景的画笔", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, TextBlock::ForegroundProperty(), PropertyCategory::text(), "前景色画笔", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, TextBlock::TextProperty(), PropertyCategory::common(), "文本内容", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, TextBlock::FontStyleProperty(), PropertyCategory::text(), "字形", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property4, TextBlock::FontSizeProperty(), PropertyCategory::text(), "字号", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property5, TextBlock::FontWeightProperty(), PropertyCategory::text(), "字体粗细", 5),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property6, TextBlock::LineHeightProperty(), PropertyCategory::text(), "行高", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property7, TextBlock::CharSpacingProperty(), PropertyCategory::text(), "字间距", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property8, TextBlock::PaddingProperty(), PropertyCategory::layout(), "控件内部的填充边距，指在对象和其他边距或边框之间插入的边距", 14),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property9, TextBlock::TextAlignmentProperty(), PropertyCategory::text(), "文本内容的水平对齐方式", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property10, TextBlock::TextTrimmingProperty(), PropertyCategory::text(), "文本超出内容区域时采用的文本裁剪行为", 11),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property11, TextBlock::TextWrappingProperty(), PropertyCategory::text(), "是否自动换行", 12),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property12, TextBlock::TextDecorationProperty(), PropertyCategory::text(), "下划线", 1)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;


	/////////////////////////Panels//////////////////////
	registration::class_<Panel>("nb::Panel")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Panel::BackgroundProperty(), PropertyCategory::brush(), "元素背景的画笔", 1)
	)
	;

	registration::class_<Canvas>("nb::Canvas")
	(
		ClassDescriptorMetadata("面板", "Canvas", "画布，内部元素使用绝对坐标进行布局"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Canvas::LeftProperty(), PropertyCategory::layout(), "元素左侧与其父Canvas左侧之间的距离", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Canvas::RightProperty(), PropertyCategory::layout(), "元素右侧与其父Canvas右侧之间的距离", 5),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Canvas::TopProperty(), PropertyCategory::layout(), "元素顶部与其父Canvas顶部之间的距离", 4),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Canvas::BottomProperty(), PropertyCategory::layout(), "元素底部与其父Canvas底部之间的距离", 6)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<DockPanel>("nb::DockPanel")
	(
		ClassDescriptorMetadata("面板", "DockPanel", "泊靠式面板，内部元素可以选择泊靠方式"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, DockPanel::LastChildFillProperty(), PropertyCategory::layout(), "最后一个子元素是否拉伸以填充剩余的可用空间", 5),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, DockPanel::DockProperty(), PropertyCategory::layout(), "子元素在父DockPanel中的位置", 3)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<WrapPanel>("nb::WrapPanel")
	(
		ClassDescriptorMetadata("面板", "WrapPanel", "自动折行面板，当一行元素排满后会自动换行"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, WrapPanel::OrientationProperty(), PropertyCategory::layout(), "子内容是水平排列还是垂直排列", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, WrapPanel::ItemWidthProperty(), PropertyCategory::layout(), "子内容是水平排列还是垂直排列", 6),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, WrapPanel::ItemHeightProperty(), PropertyCategory::layout(), "子内容是水平排列还是垂直排列", 7)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<StackPanel>("nb::StackPanel")
	(
		ClassDescriptorMetadata("面板", "StackPanel", "栈式面板,可以将包含元素排成一条直线，当添加或移除包含元素时，后面的元素会自动向下或向上移动"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, StackPanel::OrientationProperty(), PropertyCategory::layout(), "子内容是水平排列还是垂直排列", 3)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Grid>("nb::Grid")
	(
		ClassDescriptorMetadata("面板", "Grid", "网格。可以自定义行和列，并通过行列的数量、行高和列宽来调整控件的布局"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Grid::RowProperty(), PropertyCategory::layout(), "Grid中的子内容的行", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Grid::ColumnProperty(), PropertyCategory::layout(), "Grid中的子内容的列", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Grid::RowSpanProperty(), PropertyCategory::layout(), "Grid中的子内容所跨域的总行数", 3),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, Grid::ColumnSpanProperty(), PropertyCategory::layout(), "Grid中的子内容所跨域的总列数", 3)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<UniformGrid>("nb::UniformGrid")
	(
		ClassDescriptorMetadata("面板", "UniformGrid", "均匀网格。简化版的网格面板，等分的行和列，每个网格都具有相同的尺寸"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, UniformGrid::RowsProperty(), PropertyCategory::appearance(), "网格行数", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, UniformGrid::ColumnsProperty(), PropertyCategory::appearance(), "网格列数", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, UniformGrid::FirstColumnProperty(), PropertyCategory::appearance(), "第一行空白数（需显式指定了Colums才有效，如果大于等于Colums也无效）", 3)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;
	////////////////////////End Panel//////////////////////


	/////////////////////////ContentControls//////////////////////
	registration::class_<ContentControl>("nb::ContentControl");
	registration::class_<ButtonBase>("nb::ButtonBase")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, ButtonBase::ClickModeProperty(), PropertyCategory::misc(), "合适应该发生Click事件", 3)
	);

	registration::class_<Button>("nb::Button")
	(
		ClassDescriptorMetadata("内容控件", "Button", "按钮，可进行点击交互的控件"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Button::IsCancelProperty(), PropertyCategory::common(), "是否是取消按钮，用户可用Esc来调用默认按钮", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Button::IsDefaultProperty(), PropertyCategory::common(), "是否是默认按钮，用户可用Enter来调用默认按钮", 3)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<RepeatButton>("nb::RepeatButton")
	(
		ClassDescriptorMetadata("内容控件", "RepeatButton", "重复触发按钮，按钮的一种，可重复发出点击事件")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Window>("nb::Window")
	(
		ClassDescriptorMetadata("内容控件", "Window", "窗口，用于呈现子元素的顶级部件"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Window::WindowStateProperty(), PropertyCategory::common(), "指示窗口是普通、最小化还是最大化状态", 10),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Window::WindowStyleProperty(), PropertyCategory::appearance(), "窗口的边框样式", 10),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Window::TopmostProperty(), PropertyCategory::common(), "窗口置顶", 7),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, Window::LeftProperty(), PropertyCategory::layout(), "窗口距设备左端位置", 5),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property4, Window::TopProperty(), PropertyCategory::layout(), "窗口距设备顶部位置", 7),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property5, Window::TitleProperty(), PropertyCategory::common(), "窗口标题", 6),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property6, Window::IconProperty(), PropertyCategory::common(), "窗口图标", 2)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;
	//////////////////////End ContentControls/////////////////////


	/////////////////////////Shape///////////////////////////
	registration::class_<Shape>("nb::Shape")
	(
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Shape::FillProperty(), PropertyCategory::brush(), "该画笔指定如何绘制形状内部", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Shape::StrokeProperty(), PropertyCategory::brush(), "该画笔指定如何绘制形状轮廓", 2),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Shape::StrokeThicknessProperty(), PropertyCategory::appearance(), "形状轮廓的宽度（粗细）", 6),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, Shape::StrokeStartLineCapProperty(), PropertyCategory::appearance(), "描述笔划起点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", 16),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property4, Shape::StrokeEndLineCapProperty(), PropertyCategory::appearance(), "描述笔划终点处的形状，对没有笔划或者没有起点或终点（如椭圆）的形状不起作用", 13),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property5, Shape::StrokeDashArrayProperty(), PropertyCategory::appearance(), "用于绘制形状轮廓时的短划线和间隙的间隔长度，轮廓将呈现虚线", 10),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property6, Shape::StrokeDashOffsetProperty(), PropertyCategory::appearance(), "指定短划线在短划线图案中开始的距离（偏移值）", 12),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property7, Shape::StrokeDashCapProperty(), PropertyCategory::appearance(), "指定如何绘制每一小段短划线的两端", 11),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property8, Shape::StrokeLineJoinProperty(), PropertyCategory::appearance(), "指定形状顶点处使用的连接类型，对没有顶点的元素不起作用（如线段）", 14),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property9, Shape::StretchProperty(), PropertyCategory::appearance(), "描述如何调整内容大小以使其填充占据所分配的空间", 9)
	)
	;

	registration::class_<Line>("nb::Line")
	(
		ClassDescriptorMetadata("形状", "Line", "线段，形状的一种"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Line::X1Property(), PropertyCategory::appearance(), "线段起点的X分量", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Line::X2Property(), PropertyCategory::appearance(), "线段终点的X分量", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property2, Line::Y1Property(), PropertyCategory::appearance(), "线段起点的Y分量", 1),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property3, Line::Y2Property(), PropertyCategory::appearance(), "线段终点的Y分量", 1)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Polyline>("nb::Polyline")
	(
		ClassDescriptorMetadata("形状", "Polyline", "多线段，形状的一种"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Polyline::PointsProperty(), PropertyCategory::appearance(), "描述多线段的所有顶点", 5)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Polygon>("nb::Polygon")
	(
		ClassDescriptorMetadata("形状", "Polygon", "多边形，形状的一种"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Polygon::PointsProperty(), PropertyCategory::appearance(), "描述多边形的所有顶点", 5)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Path>("nb::Path")
	(
		ClassDescriptorMetadata("形状", "Path", "轨迹，形状的一种，可描述任意开口路径")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Rectangle>("nb::Rectangle")
	(
		ClassDescriptorMetadata("形状", "Rectangle", "矩形，形状的一种，可填充画刷，也可设置边框"),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property0, Rectangle::RadiusXProperty(), PropertyCategory::appearance(), "矩形的角变圆的椭圆的 x 轴半径", 4),
		PropertyDescriptorMetadata(RttrMetadataIndex::Property1, Rectangle::RadiusYProperty(), PropertyCategory::appearance(), "矩形的角变圆的椭圆的 y 轴半径", 5)
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Ellipse>("nb::Ellipse")
	(
		ClassDescriptorMetadata("形状", "Ellipse", "矩形，形状的一种，可填充画刷，也可设置边框")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

}

void RttrRegistration::registerConverters()
{
	type::register_converter_func([](const std::string &s, bool &ok)->nb::Point {
		nb::Point p;
		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 2)
		{
			ok = false;
		}
		else
		{
			ok = true;
			p = nb::Point(std::stof(segms[0]), std::stof(segms[1]));
		}
		return p;
	});

	type::register_converter_func([](const std::string &s, bool &ok)->nb::Color {
		nb::Color c;
		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 4)
		{
			ok = false;
		}
		else
		{
			ok = true;
			c = nb::Color(std::stoi(segms[0]), std::stoi(segms[1]), std::stoi(segms[2]), std::stoi(segms[3]));
		}
		return c;
	});

	type::register_converter_func([](const std::string &s, bool &ok)->nb::Thickness {

		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 4)
		{
			ok = false;
			return nb::Thickness();
		}
		else
		{
			ok = true;
			return nb::Thickness(std::stof(segms[0]), std::stof(segms[1]), std::stof(segms[2]), std::stof(segms[3]));;
		}
	});

	type::register_converter_func([](const std::string &s, bool &ok)->nb::DateTime {

		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 6)
		{
			ok = false;
			return nb::DateTime();
		}
		else
		{
			ok = true;
			return nb::DateTime(std::stoi(segms[0]), std::stoi(segms[1]),
				std::stoi(segms[2]), std::stoi(segms[3]), std::stoi(segms[4]), std::stoi(segms[5]));
		}
	});

	type::register_converter_func([](const std::string &s, bool &ok)->nb::TimeSpan {

		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() != 5)
		{
			ok = false;
			return nb::TimeSpan();
		}
		else
		{
			ok = true;
			return nb::TimeSpan(std::stoi(segms[0]), std::stoi(segms[1]),
				std::stoi(segms[2]), std::stoi(segms[3]), std::stoi(segms[4]));
		}
	});

	type::register_converter_func([](const std::string &s, bool &ok)->ImageSourcePtr {

		auto ret = std::make_shared<ImageSource>();
		ret->load((const unsigned char *)s.data(), s.size());
		ok = true;
		return ret;
	});

	type::register_converter_func([](const std::string &s, bool &ok)->BrushPtr
	{
		BrushPtr brush;

		std::vector<std::string> segms = nb::stringSplit(s, ",", true);
		if (segms.size() == 1)
		{
			auto imgSource = std::make_shared<ImageSource>();
			imgSource->load((const unsigned char *)s.data(), s.size());
			brush = std::make_shared<ImageBrush>(imgSource);
			ok = true;
		}
		else if (segms.size() == 4)
		{
			ok = true;
			nb::Color c(std::stoi(segms[0]), std::stoi(segms[1]), std::stoi(segms[2]), std::stoi(segms[3]));
			brush = std::make_shared<SolidColorBrush>(c);
		}
		else
		{
			ok = false;
		}
		return brush;
	});

}

rttr::detail::metadata nb::ClassDescriptorMetadata(const std::string & category, const std::string & dispayName, const std::string & description)
{
	return rttr::metadata(RttrMetadataIndex::ClassDescriptor, std::make_shared<ClassDescriptor>(category, dispayName, description));
}

rttr::detail::metadata nb::PropertyDescriptorMetadata(RttrMetadataIndex index, DependencyPropertyPtr dp, const PropertyCategory & category, const std::string & description, int order, RangePtr range)
{
	return rttr::metadata(index, std::make_shared<PropertyDescriptor>(dp, category, description, order, range));
}