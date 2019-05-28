#include "gui/WrapPanel.h"
#include <queue>

using namespace nb::core;
using namespace nb::gui;

WrapPanel::WrapPanel()
	: ItemWidth(NB_DOUBLE_NAN)
	, ItemHeight(NB_DOUBLE_NAN)
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
	for (auto const &child : Children())
	{
		childMeasureSize.width() = ItemWidth != NB_DOUBLE_NAN ? ItemWidth : child->Width != NB_DOUBLE_NAN ? child->Width : 0.0;
		childMeasureSize.height() = ItemHeight != NB_DOUBLE_NAN ? ItemHeight : child->Height != NB_DOUBLE_NAN ? child->Height : 0.0;
		child->measure(childMeasureSize);
		auto sz = child->DesiredSize();
		bool b = false;
	}
	return availableSize;
}

auto assignDouble(const nb::core::Property_rw<double> &p)
{
	return p != NB_DOUBLE_NAN;
}

Size WrapPanel::arrangeOverride(const Size & finalSize)
{
	//计算每行（列）的起始index和高（宽）
	auto calcLinesInfo = [&]()->std::queue<std::pair<int, double>>
	{
		std::queue<std::pair<int, double>> ret;
		if (Children().empty())	return ret;

		double sum = 0.0;
		ret.push({ 0, 0.0 });
		for (int i = 0; i != Children().size(); ++i)
		{
			auto child = Children()[i];
			double one = 0.0;
			double maxLen = 0.0;
			if (Orientation == OrientationE::Horizontal)
			{
				maxLen = finalSize.width();
				one = ItemWidth != NB_DOUBLE_NAN ? ItemWidth : child->DesiredSize().width();
			}
			else
			{
				maxLen = finalSize.height();
				one = ItemHeight != NB_DOUBLE_NAN ? ItemHeight : child->DesiredSize().height();
			}

			if (sum + one <= maxLen)
			{
				ret.back().first = i;
				ret.back().second = std::max(ret.back().second, (double)(Orientation == OrientationE::Horizontal ? child->DesiredSize().height() : child->DesiredSize().width()));
				sum += one;
			}
			else
			{
				ret.push({ i, (Orientation == OrientationE::Horizontal ? child->DesiredSize().height() : child->DesiredSize().width()) });
				sum = one;
			}
		}
		return ret;
	};

	//水平方向
	double x = 0.0;
	double y = 0.0;
	Rect arrangeRect;
	if (Orientation == OrientationE::Horizontal)
	{
		//指定了ItemHeight，则每一行高度为ItemHeight
		if (ItemHeight != NB_DOUBLE_NAN)
		{
			for (auto const &child : Children())
			{
				double w = ItemWidth != NB_DOUBLE_NAN ? ItemWidth : child->DesiredSize().width();
				//如果该行放置得下，或者child的arrage.width大于finalSize.width且尝试放置child在新行的第一个，不换行，否则换行
				if ((x + w <= finalSize.width()) || (x == 0.0 && w > finalSize.width()))
				{
					arrangeRect.reset(x, y, w, ItemHeight);
					x += w;
				}
				else
				{
					y += ItemHeight;
					arrangeRect.reset(0.0, y, w, ItemHeight);
					x = w;
				}
				child->arrage(arrangeRect);
			}
		}
		else	//否则，需要先计算每一行的最高item作为那一行的高度
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != Children().size(); ++i)
			{
				auto const &child = Children().at(i);
				double w = ItemWidth != NB_DOUBLE_NAN ? ItemWidth : child->DesiredSize().width();
				if (i <= linesInfo.front().first)
				{
					arrangeRect.reset(x, y, w, linesInfo.front().second);
					x += w;
				}
				else
				{
					y += linesInfo.front().second;
					linesInfo.pop();
					arrangeRect.reset(0.0, y, w, linesInfo.front().second);
					x = w;
				}
				child->arrage(arrangeRect);
			}
		}
	}
	//垂直方向
	else
	{
		//指定了ItemWidth，则每一列高度为ItemWidth
		if (ItemWidth != NB_DOUBLE_NAN)
		{
			for (auto const &child : Children())
			{
				double h = ItemHeight != NB_DOUBLE_NAN ? ItemHeight : child->DesiredSize().height();
				//如果该列放置得下，或者child的arrage.height大于finalSize.width且尝试放置child在新列的第一个，不换列，否则换列
				if ((y + h <= finalSize.height()) || (y == 0.0 && h > finalSize.height()))
				{
					arrangeRect.reset(x, y, ItemWidth, h);
					y += h;
				}
				else
				{
					x += ItemWidth;
					arrangeRect.reset(x, 0.0, ItemWidth, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
		else	//否则，需要先计算每一列的最宽item作为那一列的宽度
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != Children().size(); ++i)
			{
				auto const &child = Children().at(i);
				double h = ItemHeight != NB_DOUBLE_NAN ? ItemHeight : child->DesiredSize().height();
				if (i <= linesInfo.front().first)
				{
					arrangeRect.reset(x, y, linesInfo.front().second, h);
					y += h;
				}
				else
				{
					x += linesInfo.front().second;
					linesInfo.pop();
					arrangeRect.reset(x, 0.0, linesInfo.front().second, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
	}
	return finalSize;
}
