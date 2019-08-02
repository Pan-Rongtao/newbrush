#include "gui/WrapPanel.h"
#include <queue>

using namespace nb::core;
using namespace nb::gui;

WrapPanel::WrapPanel()
	: ItemWidth(NAN)
	, ItemHeight(NAN)
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
	for (auto const &child : m_children)
	{
		childMeasureSize.width() = !std::isnan(ItemWidth()) ? ItemWidth() : !std::isnan(child->Width()) ? child->Width() : 0.0f;
		childMeasureSize.height() = !std::isnan(ItemHeight()) ? ItemHeight() : !std::isnan(child->Height()) ? child->Height() : 0.0f;
		child->measure(childMeasureSize);
	}
	return availableSize;
}

//arrange两个方向维度进行：
//当Orientation == OrientationE::Horizontal时，分两种情况：1、指定了ItemHeight，则每一行高度为ItemHeight，累加每个item，当累加宽度超过finnalSize.width时，换行；2、未指定ItemHeight，先遍历items，确定行信息（每一行的开头下标，以及最高项作为该行的高）
//当Orientation == OrientationE::Vertical时，分两种情况：1、指定了ItemWdith，则每一行高度为ItemWidth，累加每个item，当累加高度超过finalSize.height时，换列；2、未指定ItemWidth，先遍历items，确定列信息（每一列的开头下标，以及最宽项作为该列的宽）
Size WrapPanel::arrangeOverride(const Size & finalSize)
{
	//计算行（列）信息，返回没行（列）的起始index和高（宽）std::queue<std::pair<int, float>>
	auto calcLinesInfo = [&]()->std::queue<std::pair<int, float>>
	{
		std::queue<std::pair<int, float>> ret;
		if (m_children.empty())	return ret;

		auto sum = 0.0f;
		ret.push({ 0, 0.0f });
		for (int i = 0; i != m_children.size(); ++i)
		{
			auto child = m_children[i];
			auto one = 0.0f;
			auto maxLen = 0.0f;
			if (Orientation == OrientationE::Horizontal)
			{
				maxLen = finalSize.width();
				one = !std::isnan(ItemWidth()) ? ItemWidth() : child->DesiredSize().width();
			}
			else
			{
				maxLen = finalSize.height();
				one = !std::isnan(ItemHeight()) ? ItemHeight() : child->DesiredSize().height();
			}

			if (sum + one <= maxLen)
			{
				ret.back().first = i;
				ret.back().second = std::max<float>(ret.back().second, Orientation == OrientationE::Horizontal ? child->DesiredSize().height() : child->DesiredSize().width());
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

	auto x = 0.0f;
	auto y = 0.0f;
	Rect arrangeRect;
	if (Orientation == OrientationE::Horizontal)
	{
		//指定了ItemHeight，每个item的高度都为iItemHeight
		//否则，需要先计算每一行的最高item作为那一行的高度
		if (!std::isnan(ItemHeight))
		{
			for (auto const &child : m_children)
			{
				auto w = !std::isnan(ItemWidth()) ? ItemWidth() : child->DesiredSize().width();
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
		else
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != m_children.size(); ++i)
			{
				auto const &child = m_children.at(i);
				auto w = !std::isnan(ItemWidth()) ? ItemWidth() : child->DesiredSize().width();
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
	else//垂直方向
	{
		//指定了ItemWidth，则每一列高度为ItemWidth
		//否则，需要先计算每一列的最宽item作为那一列的宽度
		if (!std::isnan(ItemWidth))
		{
			for (auto const &child : m_children)
			{
				auto h = !std::isnan(ItemHeight()) ? ItemHeight() : child->DesiredSize().height();
				//如果该列放置得下，或者child的arrage.height大于finalSize.width且尝试放置child在新列的第一个，不换列，否则换列
				if ((y + h <= finalSize.height()) || (y == 0.0 && h > finalSize.height()))
				{
					arrangeRect.reset(x, y, ItemWidth, h);
					y += h;
				}
				else
				{
					x += ItemWidth;
					arrangeRect.reset(x, 0.0f, ItemWidth, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
		else
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != m_children.size(); ++i)
			{
				auto const &child = m_children.at(i);
				auto h = !std::isnan(ItemHeight()) ? ItemHeight() : child->DesiredSize().height();
				if (i <= linesInfo.front().first)
				{
					arrangeRect.reset(x, y, linesInfo.front().second, h);
					y += h;
				}
				else
				{
					x += linesInfo.front().second;
					linesInfo.pop();
					arrangeRect.reset(x, 0.0f, linesInfo.front().second, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
	}
	return finalSize;
}
