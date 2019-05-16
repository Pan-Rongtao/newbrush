#include "gui/WrapPanel.h"
#include <queue>

using namespace nb::core;
using namespace nb::gui;

WrapPanel::WrapPanel()
{
}

WrapPanel::~WrapPanel()
{
}

//当测量一个子元素时，遵循这样的原则：每个子元素的childMeasureSize，如果设置了ItemWidth和ItemHeight，则measure宽高固定为ItemWidth,ItemHeight。
//否则取availableSize
Size WrapPanel::measureOverride(const Size & availableSize)
{
	Size childMeasureSize;
	childMeasureSize.width() = ItemWidth == NB_DOUBLE_NAN ? availableSize.width() : ItemWidth;
	childMeasureSize.height() = ItemHeight == NB_DOUBLE_NAN ? availableSize.height() : ItemHeight;
	for (auto const &child : Children())
	{
		child->measure(childMeasureSize);
	}
	return availableSize;
}

auto assignDouble(const nb::core::Property_rw<double> &p)
{
	return p != NB_DOUBLE_NAN;
}

//计算每行/列的起始index和高/宽
auto calcLinesInfo(const std::vector<std::shared_ptr<UIElement>> &children, double limitLenght, bool horizontal)
{
	std::queue<std::pair<int, double>> ret;
	if (children.empty())	return ret;

	double sum = 0.0;
	ret.push({ 0, 0.0 });
	for (int i = 0; i != children.size(); ++i)
	{
		auto child = children[i];
		auto one = horizontal ? child->DesiredSize().width() : child->DesiredSize().height();
		if (sum + one <= limitLenght)
		{
			ret.back().first = i;
			ret.back().second = std::max(ret.back().second, (double)child->DesiredSize().height());
			sum += one;
		}
		else
		{
			ret.push({ i, 0.0 });
			sum = 0.0;
		}
	}
	return ret;
}

Size WrapPanel::arrangeOverride(const Size & finalSize)
{
	//水平方向
	if (Orientation == OrientationE::Horizontal)
	{
		//指定了ItemHeight，则每一行高度为ItemHeight
		if (assignDouble(ItemHeight))
		{
			Rect lastArrangeRect;
			for (auto const &child : Children())
			{
				Rect arrangeRect;
				arrangeRect.setWidth(assignDouble(ItemWidth) ? ItemWidth : child->DesiredSize().width());
				arrangeRect.setHeight(ItemHeight);
				//如果child的arrage.width大于finalSize.width且尝试放置child在新行的第一个，或者该行放置得下，不换行
				//否则换行
				if ((lastArrangeRect.x() == 0.0 && arrangeRect.width() > finalSize.width()) || (lastArrangeRect.x() + arrangeRect.width() <= finalSize.width()))
					arrangeRect.setLeftTop(lastArrangeRect.rightTop());
				else
					arrangeRect.setLeftTop({ 0.0f, arrangeRect.bottom() });

				child->arrage(arrangeRect);
				lastArrangeRect = arrangeRect;
			}
		}
		else	//否则，需要先计算每一行的最高item作为那一行的高度
		{
			auto linesInfo = calcLinesInfo(Children(), finalSize.width(), true);
			Rect arrangeRect;
			int col = 0;
			double yOffset = 0.0;
			for (int i = 0; i != Children().size(); ++i)
			{
				auto const &child = Children().at(i);
				arrangeRect.setWidth(assignDouble(ItemWidth) ? ItemWidth : child->DesiredSize().width());
				int tail = linesInfo.front().first;
				double h = linesInfo.front().second;
				if (i <= tail)
				{
					arrangeRect.setHeight(h);
					arrangeRect.setLeftTop( col * arrangeRect.width(), yOffset );
					++col;
				}
				else
				{
					yOffset += h;
					col = 0;
					linesInfo.pop();
					arrangeRect.setHeight(linesInfo.front().second);
					arrangeRect.setLeftTop( col * arrangeRect.width(), yOffset);
				}
				child->arrage(arrangeRect);
			}
		}
	}
	//垂直方向
	else
	{
		//指定了ItemWidth，则每一列高度为ItemWidth
		if (assignDouble(ItemWidth))
		{
			Rect lastArrangeRect;
			for (auto const &child : Children())
			{
				Rect arrangeRect;
				arrangeRect.setWidth(ItemWidth);
				arrangeRect.setHeight(assignDouble(ItemHeight) ? ItemHeight : child->DesiredSize().height());
				//如果child的arrage.height大于finalSize.height且尝试放置child在新行的第一个，或者该列放置得下，不换行
				//否则换列
				if ((lastArrangeRect.y() == 0.0 && arrangeRect.height() > finalSize.height()) || (lastArrangeRect.y() + arrangeRect.height() <= finalSize.height()))
					arrangeRect.setLeftTop(lastArrangeRect.leftBottom());
				else
					arrangeRect.setLeftTop({ arrangeRect.right(), 0.0 });

				child->arrage(arrangeRect);
				lastArrangeRect = arrangeRect;
			}
		}
		else	//否则，需要先计算每一列的最宽item作为那一列的宽度
		{
			auto linesInfo = calcLinesInfo(Children(), finalSize.height(), false);
			Rect arrangeRect;
			int row = 0;
			double xOffset = 0.0;
			for (int i = 0; i != Children().size(); ++i)
			{
				auto const &child = Children().at(i);
				arrangeRect.setHeight(assignDouble(ItemHeight) ? ItemHeight : child->DesiredSize().height());
				int tail = linesInfo.front().first;
				double w = linesInfo.front().second;
				if (i <= tail)
				{
					arrangeRect.setWidth(w);
					arrangeRect.setLeftTop( xOffset, row * arrangeRect.height() );
					++row;
				}
				else
				{
					xOffset += w;
					row = 0;
					linesInfo.pop();
					arrangeRect.setHeight(linesInfo.front().second);
					arrangeRect.setLeftTop(xOffset, row * arrangeRect.height());
				}
				child->arrage(arrangeRect);
			}
		}
	}
}
