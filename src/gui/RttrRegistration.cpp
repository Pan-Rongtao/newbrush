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

using namespace nb;
using namespace rttr;

RTTR_REGISTRATION
{
	//enums
	registration::enumeration<StretchE>("StretchE")
	(
		value("Origion", StretchE::Origion),
		value("Fill", StretchE::Fill),
		value("Uniform", StretchE::Uniform),
		value("UniformToFill", StretchE::UniformToFill)
	);
	registration::enumeration<VisibilityE>("VisibilityE")
	(
		value("Hidden", VisibilityE::Hidden),
		value("Visible", VisibilityE::Visible),
		value("Collapsed", VisibilityE::Collapsed)
	);
	registration::enumeration<HorizontalAlignmentE>("HorizontalAlignmentE")
	(
		value("Left", HorizontalAlignmentE::Left),
		value("Center", HorizontalAlignmentE::Center),
		value("Right", HorizontalAlignmentE::Right),
		value("Stretch", HorizontalAlignmentE::Stretch)
	);
	registration::enumeration<VerticalAlignmentE>("VerticalAlignmentE")
	(
		value("Top", VerticalAlignmentE::Top),
		value("Center", VerticalAlignmentE::Center),
		value("Bottom", VerticalAlignmentE::Bottom),
		value("Stretch", VerticalAlignmentE::Stretch)
	);
	registration::enumeration<FlowDirectionE>("FlowDirectionE")
	(
		value("LeftToRight", FlowDirectionE::LeftToRight),
		value("RightToLeft", FlowDirectionE::RightToLeft)
	);
	registration::enumeration<FontStyleE>("FontStyleE")
	(
		value("Normal", FontStyleE::Normal),
		value("Italic", FontStyleE::Italic),
		value("Oblique", FontStyleE::Oblique)
	);
	registration::enumeration<TextAlignmentE>("TextAlignmentE")
	(
		value("Left", TextAlignmentE::Left),
		value("Right", TextAlignmentE::Right),
		value("Center", TextAlignmentE::Center),
		value("Justify", TextAlignmentE::Justify)
	);
	registration::enumeration<TextWrappingE>("TextWrappingE")
	(
		value("NoWrap", TextWrappingE::NoWrap),
		value("Wrap", TextWrappingE::Wrap),
		value("WrapWithOverflow", TextWrappingE::WrapWithOverflow)
	);
	registration::enumeration<TextTrimmingE>("TextTrimmingE")
	(
		value("None", TextTrimmingE::None),
		value("CharacterEllipsis", TextTrimmingE::CharacterEllipsis),
		value("WordEllipsis", TextTrimmingE::WordEllipsis)
	);
	registration::enumeration<OrientationE>("OrientationE")
	(
		value("Horizontal", OrientationE::Horizontal),
		value("Vertical", OrientationE::Vertical)
	);
	registration::enumeration<WindowStyleE>("WindowStyleE")
	(
		value("None", WindowStyleE::None),
		value("Fixed", WindowStyleE::Fixed),
		value("SizeBox", WindowStyleE::SizeBox)
	);
	registration::enumeration<WindowStateE>("WindowStateE")
	(
		value("Normal", WindowStateE::Normal),
		value("Maximized", WindowStateE::Maximized),
		value("Minimized", WindowStateE::Minimized)
	);
	registration::enumeration<PenLineCapE>("PenLineCapE")
	(
		value("Flat", PenLineCapE::Flat),
		value("Round", PenLineCapE::Round),
		value("Square", PenLineCapE::Square),
		value("Triangle", PenLineCapE::Triangle)
	);
	registration::enumeration<PenLineJoinE>("PenLineCapE")
	(
		value("Beval", PenLineJoinE::Beval),
		value("Miter", PenLineJoinE::Miter),
		value("Round", PenLineJoinE::Round)
	);

	auto k = nb::getTickCount();

	/////////////////////////Point//////////////////////
	registration::class_<Point>("nb::Point")
		.constructor<>()()
		.constructor<float, float>()(policy::ctor::as_object)
		;
	//////////////////////End Point/////////////////////

	/////////////////////////Binding//////////////////////
	registration::enumeration<BindingModeE>("BindingModeE")
	(
		value("OneTime", BindingModeE::OneTime),
		value("OneWayToTarget", BindingModeE::OneWayToTarget),
		value("OneWayToSource", BindingModeE::OneWayToSource),
		value("TwoWay", BindingModeE::TwoWay)
	);
	//////////////////////End Binding/////////////////////


	/////////////////////////Object//////////////////////

	registration::class_<Object>("nb::Object").constructor<>();
	registration::class_<DependencyObject>("nb::DependencyObject").constructor<>();

	/////////////////////////UIElement//////////////////////
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

	//////////////////////End Shape/////////////////////

	auto kk = nb::getTickCount();
	Log::info("RTTR registration cost [%d] ms.", kk - k);
}

std::vector<DependencyPropertyPtr> RttrRegistration::getTypeSelfPropertys(rttr::type t)
{
	std::vector<std::shared_ptr<DependencyProperty>> ret;
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
	std::vector<std::shared_ptr<DependencyProperty>> ret;
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
