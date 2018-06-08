/*******************************************************
**	Rect（RectI的浮点形式）
**	
**	矩形类，矩形内的点集合以左部和顶部（包含），向右和下方向延伸，
**	不包含右部和底部那个单位。
**	
**	比如RectI(0, 0, 0, 0) 长度和宽度为0，不包含任何点，即空矩形
**	又如RectI(0, 0, 1, 1) 长度和宽度为1，只包含了点(0, 0)。
**
**	简单来说，它是一个左闭右开区间
**	
**		潘荣涛
**	
********************************************************/

#pragma once
#include "RectI.h"
#include "Point.h"
#include "Size.h"

namespace nb{ namespace System{

class NB_EXPORT Rect
{
	//public funs.
public:
	//设置矩形的x（左边），宽可能会被改变，但绝不会改变顶部、底部、右边和高
	void SetX(float x);
	float GetX() const;
	void SetLeft(float left);
	float GetLeft() const;

	//设置矩形的y（顶部），高可能会被改变，但绝不会改变左边、底部、右边和宽
	void SetY(float y);
	float GetY() const;
	void SetTop(float top);
	float GetTop() const;

	//设置矩形的右边，宽可能会被改变，但绝不会改变左边、顶部、底部和高
	void SetRight(float right);
	float GetRight() const;

	//设置矩形的底部，高可能会被改变，但绝不会改变左边、顶部、右边和宽
	void SetBottom(float bottom);
	float GetBottom() const;

	//设置矩形的左上角坐标（左边和顶部），宽和高都可能会改变，但绝不会改变右下角坐标（右边和底部）
	void SetLeftTop(const Point &p);
	Point GetLeftTop() const;

	//设置矩形的右上角坐标（右边和顶部），宽和高都可能会改变，但绝不会改变左下角坐标（左边和底部）
	void SetRightTop(const Point &p);
	Point GetRightTop() const;

	//设置矩形的左下角坐标（左边和底部），宽和高都可能会改变，但绝不会改变右上角坐标（右边和顶部）
	void SetLeftBottom(const Point &p);
	Point GetLeftBottom() const;

	//设置矩形的右下角坐标（右边和底部），宽和高都可能会改变，但绝不会改变左上角坐标（左边和顶部）
	void SetRightBottom(const Point &p);
	Point GetRightBottom() const;

	Point GetCenter() const;

	//设置矩形的宽，右边可能会改变，但绝不会改变左边、顶部、底部和高
	void SetWidth(float width);
	float GetWidth() const;

	//设置矩形的高，底部可能会改变，但绝不会改变左边、顶部、右边和宽
	void SetHeight(float height);
	float GetHeight() const;

	//设置矩形的尺寸，右边和底部可能会改变，但绝不会改变左边和顶部
	void SetSize(float width, float height);
	void SetSize(const Size &size);

	Size GetSize() const;
	void GetSize(float &width, float &height) const;


	//重置矩形
	void Reset(float x, float y, float width, float height);

	//返回一个标准化的矩形，使它的尺寸为正，并且矫正四个角的坐标排序位置
	Rect Normalize() const;


	//点是否属于该矩形区域（注意，除了左上角，左下角、右上角、右下角这几个点都不属于矩形区域包含的点集合）
	bool Contains(float x, float y) const;
	bool Contains(const Point &p) const;
	//矩形是否完全被此矩形包含
	bool Contains(const Rect &rc) const;

	//尺寸为0被判定为Empty
	bool IsEmpty() const;

	//是否为Zero矩形
	bool IsZero() const;

	//相等
	bool Equals(const Rect &other) const;

	//整个在水平和垂直方向移动一定值，不会改变矩形的形状
	void MoveHorizontal(float fHorizontal);
	void MoveVertical(float fVertical);
	void Move(float nHorizontal, float nVertical);

	//移动某条边或者顶点以改变矩形的形状，并非移动整个矩形移动，offset为偏移值
	void MoveOffsetLeft(float offset);
	void MoveOffsetTop(float offset);
	void MoveOffsetRight(float offset);
	void MoveOffsetBottom(float offset);

	void MoveOffsetLeftTop(float offsetX, float offsetY);
	void MoveOffsetLeftTop(const Point &ptOffset);
	void MoveOffsetRightTop(float offsetX, float offsetY);
	void MoveOffsetRightTop(const Point &ptOffset);
	void MoveOffsetLeftBottom(float offsetX, float offsetY);
	void MoveOffsetLeftBottom(const Point &ptOffset);
	void MoveOffsetRightBottom(float offsetX, float offsetY);
	void MoveOffsetRightBottom(const Point &ptOffset);

	RectI ToRectI() const;

	//舍入到最接近的整数值构成的PointI
	RectI ToRoundRectI() const;

	//是否与另一个RectI相交
	bool IsIntersetWith(const Rect &other) const;

	//与另一个RectI的交集，和 operator & 的效果是一样的
	Rect IntersetWith(const Rect &other) const;

	//与另一个RectI的并集，和 operator | 的效果是一样的
	Rect MergeWith(const Rect &other) const;
	//Constructors & operators.
public:
	Rect();
	Rect(float x, float y, float width, float height);
	Rect(float x, float y, const Size &size);
	Rect(const Point &leftTop, float width, float height);
	Rect(const Point &leftTop, const Size &size);
	Rect(const Point &leftTop, const Point &rightBottom);
	Rect(const Rect &other);
	~Rect();

	void operator = (const Rect &other);

	bool operator == (const Rect &other) const;
	bool operator != (const Rect &other) const;

	//逻辑操作将返回一个标准化的矩形
	//返回两个矩形的并集
	Rect operator | (const Rect &other) const;
	void operator |= (const Rect &other);
	//返回两个矩形的合集，如果无交集将返回RectI::Zero
	Rect operator & (const Rect &other) const;
	void operator &= (const Rect &other);

	//public static funs.
public:
	//左、右、顶、底、尺寸都是0被定义为Zero
	static Rect Zero();

	static Rect FromLTRB(float left, float top, float right, float bottom);

	static Rect FromRectI(const RectI &rc);

private:

	float		m_fX;
	float		m_fY;
	float		m_fWidth;
	float		m_fHeight;
};
//gloable static funs.
static bool Equals(const Rect &rc1, const Rect &rc2)
{
	return rc1.Equals(rc2);
}

}}
