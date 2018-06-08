/*******************************************************
**	RectI
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
#include "PointI.h"
#include "SizeI.h"

namespace nb{ namespace System{

class NB_EXPORT RectI
{
//public funs.
public:
	//设置矩形的x（左边），宽可能会被改变，但绝不会改变顶部、底部、右边和高
	void SetX(int x);
	int GetX() const;
	void SetLeft(int left);
	int GetLeft() const;

	//设置矩形的y（顶部），高可能会被改变，但绝不会改变左边、底部、右边和宽
	void SetY(int y);
	int GetY() const;
	void SetTop(int top);
	int GetTop() const;

	//设置矩形的右边，宽可能会被改变，但绝不会改变左边、顶部、底部和高
	void SetRight(int right);
	int GetRight() const;

	//设置矩形的底部，高可能会被改变，但绝不会改变左边、顶部、右边和宽
	void SetBottom(int bottom);
	int GetBottom() const;

	//设置矩形的左上角坐标（左边和顶部），宽和高都可能会改变，但绝不会改变右下角坐标（右边和底部）
	void SetLeftTop(const PointI &p);
	PointI GetLeftTop() const;

	//设置矩形的右上角坐标（右边和顶部），宽和高都可能会改变，但绝不会改变左下角坐标（左边和底部）
	void SetRightTop(const PointI &p);
	PointI GetRightTop() const;

	//设置矩形的左下角坐标（左边和底部），宽和高都可能会改变，但绝不会改变右上角坐标（右边和顶部）
	void SetLeftBottom(const PointI &p);
	PointI GetLeftBottom() const;

	//设置矩形的右下角坐标（右边和底部），宽和高都可能会改变，但绝不会改变左上角坐标（左边和顶部）
	void SetRightBottom(const PointI &p);
	PointI GetRightBottom() const;

	PointI GetCenter() const;

	//设置矩形的宽，右边可能会改变，但绝不会改变左边、顶部、底部和高
	void SetWidth(int width);
	int GetWidth() const;

	//设置矩形的高，底部可能会改变，但绝不会改变左边、顶部、右边和宽
	void SetHeight(int height);
	int GetHeight() const;

	//设置矩形的尺寸，右边和底部可能会改变，但绝不会改变左边和顶部
	void SetSize(int width, int height);
	void SetSize(const SizeI &size);

	SizeI GetSize() const;
	void GetSize(int &width, int &height) const;


	//重置矩形
	void Reset(int x, int y, int width, int height);

	//返回一个标准化的矩形，使它的尺寸为正，并且矫正四个角的坐标排序位置
	RectI Normalize() const;


	//点是否属于该矩形区域（注意，除了左上角，左下角、右上角、右下角这几个点都不属于矩形区域包含的点集合）
	bool Contains(int x, int y) const;
	bool Contains(const PointI &p) const;
	//矩形是否完全被此矩形包含
	bool Contains(const RectI &rc) const;

	//尺寸为0被判定为Empty
	bool IsEmpty() const;

	//是否为Zero矩形
	bool IsZero() const;

	bool Equals(const RectI &other) const;

	//整个在水平和垂直方向移动一定值，不会改变矩形的形状
	void MoveHorizontal(int nHorizontal);
	void MoveVertical(int nVertical);
	void Move(int nHorizontal, int nVertical);

	//移动某条边或者顶点以改变矩形的形状，并非移动整个矩形移动，offset为偏移值
	void MoveOffsetLeft(int offset);
	void MoveOffsetTop(int offset);
	void MoveOffsetRight(int offset);
	void MoveOffsetBottom(int offset);

	void MoveOffsetLeftTop(int offsetX, int offsetY);
	void MoveOffsetLeftTop(const PointI &ptOffset);
	void MoveOffsetRightTop(int offsetX, int offsetY);
	void MoveOffsetRightTop(const PointI &ptOffset);
	void MoveOffsetLeftBottom(int offsetX, int offsetY);
	void MoveOffsetLeftBottom(const PointI &ptOffset);
	void MoveOffsetRightBottom(int offsetX, int offsetY);
	void MoveOffsetRightBottom(const PointI &ptOffset);
	
	//是否与另一个RectI相交
	bool IsIntersetWith(const RectI &other) const;

	//与另一个RectI的交集，和 operator & 的效果是一样的
	RectI IntersetWith(const RectI &other) const;

	//与另一个RectI的并集，和 operator | 的效果是一样的
	RectI MergeWith(const RectI &other) const;

//Constructors & operators.
public:
	RectI();
	RectI(int x, int y, int width, int height);
	RectI(int x, int y, const SizeI &size);
	RectI(const PointI &leftTop, int width, int height);
	RectI(const PointI &leftTop, const SizeI &size);
	RectI(const PointI &leftTop, const PointI &rightBottom);
	RectI(const RectI &other);
	~RectI();

	void operator = (const RectI &other);

	bool operator == (const RectI &other) const;
	bool operator != (const RectI &other) const;

	//逻辑操作将返回一个标准化的矩形
	//返回两个矩形的并集
	RectI operator | (const RectI &other) const;
	void operator |= (const RectI &other);
	//返回两个矩形的合集，如果无交集将返回RectI::Zero
	RectI operator & (const RectI &other) const;
	void operator &= (const RectI &other);

//public static funs.
public:
	static RectI FromLTRB(int left, int top, int right, int bottom);

	//左、右、顶、底、尺寸都是0被定义为Zero
	static RectI Zero();

private:

	int		m_nX;
	int		m_nY;
	int		m_nWidth;
	int		m_nHeight;
};
//gloable static funs.
static bool Equals(const RectI &rc1, const RectI &rc2)
{
	return rc1.Equals(rc2);
}

}}
