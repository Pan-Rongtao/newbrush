#include "newbrush/gui/RttrRegistration.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/Log.h"
#include "newbrush/core/Binding.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Panel.h"
#include "newbrush/gui/Canvas.h"
#include "newbrush/gui/DockPanel.h"
#include "newbrush/gui/WrapPanel.h"
#include "newbrush/gui/StackPanel.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/UniformGrid.h"
#include "newbrush/gui/Button.h"
#include "newbrush/gui/RepeatButton.h"
#include "newbrush/gui/Image.h"
#include "newbrush/gui/TextBlock.h"
#include "newbrush/gui/Line.h"
#include "newbrush/gui/Polyline.h"
#include "newbrush/gui/Polygon.h"
#include "newbrush/gui/Path.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/media/Color.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/core/DateTime.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/ImageSource.h"

using namespace nb;
using namespace rttr;

//enum类型需要主动注册，因为需要把枚举值注册
//控件类型需主动注册，因为需要注册构造函数和metadata
//作为Property属性类型的类型不要主动注册，让RTTR自动生成（用到什么就会自动生成什么）

RTTR_REGISTRATION
{
	RttrRegistration::doRegister();
}

std::vector<DependencyPropertyPtr> RttrRegistration::getTypeSelfPropertys(rttr::type t)
{
	std::vector<DependencyPropertyPtr> ret;
	for (auto i = (int)RttrClassMetadataIndex::Property0; i <= (int)RttrClassMetadataIndex::PropertyMax; ++i)
	{
		var vProperty = t.get_metadata((RttrClassMetadataIndex)i);
		type ttt = vProperty.get_type();
		if (vProperty.is_type<DependencyPropertyPtr>())
		{
			const DependencyPropertyPtr &p = vProperty.get_value<DependencyPropertyPtr>();
			ret.push_back(p);
		}
		else if(vProperty.is_valid())
		{
			Log::error("[%s]'s metadata[%d] must be set as [DependencyPropertyPtr] type", t.get_name().data(), i);
		}
	}
	return ret;
}

std::vector<DependencyPropertyPtr> RttrRegistration::getTypeAllPropertys(rttr::type t)
{
	std::vector<DependencyPropertyPtr> ret;
	auto selfPros = getTypeSelfPropertys(t);
	ret.insert(ret.end(), selfPros.begin(), selfPros.end());

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

}

void RttrRegistration::registerUIElementTypes()
{
	registration::class_<UIElement>("nb::UIElement")
	(
		metadata(RttrClassMetadataIndex::Property0, UIElement::NameProperty()),
		metadata(RttrClassMetadataIndex::Property1, UIElement::VisibilityProperty()),
		metadata(RttrClassMetadataIndex::Property2, UIElement::OpacityProperty()),
		metadata(RttrClassMetadataIndex::Property3, UIElement::FocusableProperty()),
		metadata(RttrClassMetadataIndex::Property4, UIElement::WidthProperty()),
		metadata(RttrClassMetadataIndex::Property5, UIElement::HeightProperty()),
		metadata(RttrClassMetadataIndex::Property7, UIElement::MinWidthProperty()),
		metadata(RttrClassMetadataIndex::Property8, UIElement::MinHeightProperty()),
		metadata(RttrClassMetadataIndex::Property9, UIElement::MaxWidthProperty()),
		metadata(RttrClassMetadataIndex::Property10, UIElement::MaxHeightProperty()),
		metadata(RttrClassMetadataIndex::Property11, UIElement::MarginProperty()),
		metadata(RttrClassMetadataIndex::Property12, UIElement::HorizontalAlignmentProperty()),
		metadata(RttrClassMetadataIndex::Property13, UIElement::VerticalAlignmentProperty()),
		metadata(RttrClassMetadataIndex::Property14, UIElement::FlowDirectionProperty()),
		metadata(RttrClassMetadataIndex::Property15, UIElement::RenderTransformProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Control>("nb::Control")
	(
		metadata(RttrClassMetadataIndex::Property0, Control::BackgroundProperty()),
		metadata(RttrClassMetadataIndex::Property1, Control::BorderBrushProperty()),
		metadata(RttrClassMetadataIndex::Property2, Control::BorderThicknessProperty()),
		metadata(RttrClassMetadataIndex::Property3, Control::FontFamilyProperty()),
		metadata(RttrClassMetadataIndex::Property4, Control::FontSizeProperty()),
		metadata(RttrClassMetadataIndex::Property5, Control::FontStretchProperty()),
		metadata(RttrClassMetadataIndex::Property7, Control::FontStyleProperty()),
		metadata(RttrClassMetadataIndex::Property8, Control::FontWeightProperty()),
		metadata(RttrClassMetadataIndex::Property9, Control::ForegroundProperty()),
		metadata(RttrClassMetadataIndex::Property10, Control::PaddingProperty()),
		metadata(RttrClassMetadataIndex::Property11, Control::HorizontalContentAlignmentProperty()),
		metadata(RttrClassMetadataIndex::Property12, Control::VerticalContentAlignmentProperty()),
		metadata(RttrClassMetadataIndex::Property13, Control::TabIndexProperty()),
		metadata(RttrClassMetadataIndex::Property14, Control::IsTabStopProperty()),
		metadata(RttrClassMetadataIndex::Property15, Control::TemplateProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<ContentControl>("nb::ContentControl")
	(
		metadata(RttrClassMetadataIndex::Property0, ContentControl::ContentProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Image>("nb::Image")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "其他"),
		metadata(RttrClassMetadataIndex::DisplayName, "Image"),
		metadata(RttrClassMetadataIndex::Description, "图片，可设置多种适应模式"),
		metadata(RttrClassMetadataIndex::Property0, Image::SourceProperty()),
		metadata(RttrClassMetadataIndex::Property1, Image::StretchProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<TextBlock>("nb::TextBlock")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "其他"),
		metadata(RttrClassMetadataIndex::DisplayName, "TextBlock"),
		metadata(RttrClassMetadataIndex::Description, "画布，内部元素使用绝对坐标进行布局"),
		metadata(RttrClassMetadataIndex::Property0, TextBlock::BackgroundProperty()),
		metadata(RttrClassMetadataIndex::Property1, TextBlock::ForegroundProperty()),
		metadata(RttrClassMetadataIndex::Property2, TextBlock::TextProperty()),
		metadata(RttrClassMetadataIndex::Property3, TextBlock::FontStyleProperty()),
		metadata(RttrClassMetadataIndex::Property4, TextBlock::FontSizeProperty()),
		metadata(RttrClassMetadataIndex::Property5, TextBlock::FontWeightProperty()),
		metadata(RttrClassMetadataIndex::Property6, TextBlock::LineHeightProperty()),
		metadata(RttrClassMetadataIndex::Property7, TextBlock::CharSpacingProperty()),
		metadata(RttrClassMetadataIndex::Property8, TextBlock::PaddingProperty()),
		metadata(RttrClassMetadataIndex::Property9, TextBlock::TextAlignmentProperty()),
		metadata(RttrClassMetadataIndex::Property10, TextBlock::TextTrimmingProperty()),
		metadata(RttrClassMetadataIndex::Property11, TextBlock::TextWrappingProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;


	/////////////////////////Panels//////////////////////
	registration::class_<Panel>("nb::Panel")
	(
		metadata(RttrClassMetadataIndex::Property0, Panel::BackgroundProperty())
	)
	;

	registration::class_<Canvas>("nb::Canvas")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "Canvas"),
		metadata(RttrClassMetadataIndex::Description, "画布，内部元素使用绝对坐标进行布局")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<DockPanel>("nb::DockPanel")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "DockPanel"),
		metadata(RttrClassMetadataIndex::Description, "泊靠式面板，内部元素可以选择泊靠方式"),
		metadata(RttrClassMetadataIndex::Property0, DockPanel::LastChildFillProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<WrapPanel>("nb::WrapPanel")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "WrapPanel"),
		metadata(RttrClassMetadataIndex::Description, "自动折行面板，当一行元素排满后会自动换行"),
		metadata(RttrClassMetadataIndex::Property0, WrapPanel::OrientationProperty()),
		metadata(RttrClassMetadataIndex::Property1, WrapPanel::ItemWidthProperty()),
		metadata(RttrClassMetadataIndex::Property2, WrapPanel::ItemHeightProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<StackPanel>("nb::StackPanel")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "StackPanel"),
		metadata(RttrClassMetadataIndex::Description, "栈式面板,可以将包含元素排成一条直线，当添加或移除包含元素时，后面的元素会自动向下或向上移动"),
		metadata(RttrClassMetadataIndex::Property0, StackPanel::OrientationProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Grid>("nb::Grid")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "Grid"),
		metadata(RttrClassMetadataIndex::Description, "网格。可以自定义行和列，并通过行列的数量、行高和列宽来调整控件的布局")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<UniformGrid>("nb::UniformGrid")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "面板"),
		metadata(RttrClassMetadataIndex::DisplayName, "UniformGrid"),
		metadata(RttrClassMetadataIndex::Description, "均匀网格。简化版的网格面板，等分的行和列，每个网格都具有相同的尺寸"),
		metadata(RttrClassMetadataIndex::Property0, UniformGrid::RowsProperty()),
		metadata(RttrClassMetadataIndex::Property1, UniformGrid::ColumnsProperty()),
		metadata(RttrClassMetadataIndex::Property2, UniformGrid::FirstColumnProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;
	////////////////////////End Panel//////////////////////


	/////////////////////////ContentControls//////////////////////
	registration::class_<ContentControl>("nb::ContentControl");
	registration::class_<ButtonBase>("nb::ButtonBase");

	registration::class_<Button>("nb::Button")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "内容控件"),
		metadata(RttrClassMetadataIndex::DisplayName, "Button"),
		metadata(RttrClassMetadataIndex::Description, "按钮，可进行点击交互的控件"),
		metadata(RttrClassMetadataIndex::Property0, Button::IsCancelProperty()),
		metadata(RttrClassMetadataIndex::Property1, Button::IsDefaultProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<RepeatButton>("nb::RepeatButton")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "内容控件"),
		metadata(RttrClassMetadataIndex::DisplayName, "RepeatButton"),
		metadata(RttrClassMetadataIndex::Description, "重复触发按钮，按钮的一种，可重复发出点击事件")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Window>("nb::Window")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "内容控件"),
		metadata(RttrClassMetadataIndex::DisplayName, "Window"),
		metadata(RttrClassMetadataIndex::Description, "窗口，用于呈现子元素的顶级部件"),
		metadata(RttrClassMetadataIndex::Property0, Window::WindowStateProperty()),
		metadata(RttrClassMetadataIndex::Property1, Window::WindowStyleProperty()),
		metadata(RttrClassMetadataIndex::Property2, Window::TopmostProperty()),
		metadata(RttrClassMetadataIndex::Property3, Window::LeftProperty()),
		metadata(RttrClassMetadataIndex::Property4, Window::TopProperty()),
		metadata(RttrClassMetadataIndex::Property5, Window::TitleProperty()),
		metadata(RttrClassMetadataIndex::Property6, Window::IconProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;
	//////////////////////End ContentControls/////////////////////


	/////////////////////////Shape///////////////////////////
	registration::class_<Shape>("nb::Shape")
	(
		metadata(RttrClassMetadataIndex::Property0, Shape::FillProperty()),
		metadata(RttrClassMetadataIndex::Property1, Shape::StrokeProperty()),
		metadata(RttrClassMetadataIndex::Property2, Shape::StrokeThicknessProperty()),
		metadata(RttrClassMetadataIndex::Property3, Shape::StrokeStartLineCapProperty()),
		metadata(RttrClassMetadataIndex::Property4, Shape::StrokeEndLineCapProperty()),
		metadata(RttrClassMetadataIndex::Property5, Shape::StrokeDashArrayProperty()),
		metadata(RttrClassMetadataIndex::Property6, Shape::StrokeDashOffsetProperty()),
		metadata(RttrClassMetadataIndex::Property7, Shape::StrokeDashCapProperty()),
		metadata(RttrClassMetadataIndex::Property8, Shape::StrokeLineJoinProperty()),
		metadata(RttrClassMetadataIndex::Property9, Shape::StretchProperty())
	)
	;

	registration::class_<Line>("nb::Line")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Line"),
		metadata(RttrClassMetadataIndex::Description, "线段，形状的一种"),
		metadata(RttrClassMetadataIndex::Property0, Line::X1Property()),
		metadata(RttrClassMetadataIndex::Property1, Line::X2Property()),
		metadata(RttrClassMetadataIndex::Property2, Line::Y1Property()),
		metadata(RttrClassMetadataIndex::Property3, Line::Y2Property())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Polyline>("nb::Polyline")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Polyline"),
		metadata(RttrClassMetadataIndex::Description, "多线段，形状的一种"),
		metadata(RttrClassMetadataIndex::Property0, Polyline::PointsProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Polyline>("nb::Polyline")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Polyline"),
		metadata(RttrClassMetadataIndex::Description, "多线段，形状的一种"),
		metadata(RttrClassMetadataIndex::Property0, Polyline::PointsProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Polygon>("nb::Polygon")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Polygon"),
		metadata(RttrClassMetadataIndex::Description, "多边形，形状的一种"),
		metadata(RttrClassMetadataIndex::Property0, Polygon::PointsProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Path>("nb::Path")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Path"),
		metadata(RttrClassMetadataIndex::Description, "轨迹，形状的一种，可描述任意开口路径")
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Rectangle>("nb::Rectangle")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Rectangle"),
		metadata(RttrClassMetadataIndex::Description, "矩形，形状的一种，可填充画刷，也可设置边框"),
		metadata(RttrClassMetadataIndex::Property0, Rectangle::RadiusXProperty()),
		metadata(RttrClassMetadataIndex::Property1, Rectangle::RadiusYProperty())
	)
	.constructor<>()(policy::ctor::as_std_shared_ptr)
	;

	registration::class_<Ellipse>("nb::Ellipse")
	(
		metadata(RttrClassMetadataIndex::AsVisual, true),
		metadata(RttrClassMetadataIndex::Category, "形状"),
		metadata(RttrClassMetadataIndex::DisplayName, "Ellipse"),
		metadata(RttrClassMetadataIndex::Description, "矩形，形状的一种，可填充画刷，也可设置边框")
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
