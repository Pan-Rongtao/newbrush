/*******************************************************
**	Rect/RectI
**	
**	矩形类，矩形内的点集合以左部和顶部（包含），向右和下方向延伸，
**	不包含右部和底部那个单位。
**	
**	比如Rect(0, 0, 0, 0) 长度和宽度为0，不包含任何点，即空矩形
**	又如Rect(0, 0, 1, 1) 长度和宽度为1，只包含了点(0, 0)。
**
**	简单来说，它是一个左闭右开区间
**	
**		潘荣涛
**	
********************************************************/

#pragma once
#include "Point.h"
#include "Size.h"

namespace nb{ namespace core{

//class Rect
class NB_API Rect
{
public:
	//构建一个Rect(0.0, 0.0, 0.0, 0.0)
	Rect();

	//构建一个Rect(x, y, width, height)
	Rect(float x, float y, float width, float height);

	//构建一个Rect(x, y, size.width, size.height)
	Rect(float x, float y, const Size &size);

	//构建一个Rect(leftTop.x, leftTop.y, width, height)
	Rect(const Point &leftTop, float width, float height);

	//构建一个Rect(leftTop.x, leftTop.y, size.width, size.height)
	Rect(const Point &leftTop, const Size &size);

	//构建一个Rect，塔尔左上角为leftTop，它的右下角为rightBottom
	Rect(const Point &leftTop, const Point &rightBottom);

	//从其他Rect构建一个Rect
	Rect(const Rect &other);

	//构建一个零Rect：左、右、顶、底、尺寸都是0.0被定义为Zero
	static Rect zero();

	//从左、顶、右、底部构建一个Rect
	static Rect fromLTRB(float left, float top, float right, float bottom);

	void operator = (const Rect &other);
	bool operator == (const Rect &other) const;
	bool operator != (const Rect &other) const;
	//逻辑操作将返回一个标准化的矩形
	//返回两个矩形的并集
	Rect operator | (const Rect &other) const;
	void operator |= (const Rect &other);
	//返回两个矩形的合集，如果无交集将返回Rect::Zero
	Rect operator & (const Rect &other) const;
	void operator &= (const Rect &other);

public:
	//设置矩形的x（左边），宽可能会被改变，但绝不会改变顶部、底部、右边和高
	void setX(float x) &;
	void setLeft(float left) &;

	//x(left)不可引用
	float x() const;
	float left() const;

	//设置矩形的y（顶部），高可能会被改变，但绝不会改变左边、底部、右边和宽
	void setY(float y) &;
	void setTop(float top) &;

	//y(top)不可引用
	float y() const;
	float top() const;

	//设置矩形的宽，右边可能会改变，但绝不会改变左边、顶部、底部和高
	void setWidth(float width) &;

	//宽，不可引用
	float width() const;

	//设置矩形的高，底部可能会改变，但绝不会改变左边、顶部、右边和宽
	void setHeight(float height) &;

	//高，不可引用
	float height() const;

	//设置矩形的尺寸，右边和底部可能会改变，但绝不会改变左边和顶部
	void setSize(float width, float height) &;
	void setSize(const Size &size) &;

	//尺寸
	Size size() const;

	//重置矩形
	void reset(float x, float y, float width, float height);

	//设置矩形的右边，宽可能会被改变，但绝不会改变左边、顶部、底部和高
	void setRight(float right) &;
	float right() const;

	//设置矩形的底部，高可能会被改变，但绝不会改变左边、顶部、右边和宽
	void setBottom(float bottom) &;
	float bottom() const;

	//设置矩形的左上角坐标（左边和顶部），宽和高都可能会改变，但绝不会改变右下角坐标（右边和底部）
	void setLeftTop(float left, float top) &;
	void setLeftTop(const Point &p) &;
	Point leftTop() const;

	//设置矩形的右上角坐标（右边和顶部），宽和高都可能会改变，但绝不会改变左下角坐标（左边和底部）
	void setRightTop(float right, float top) &;
	void setRightTop(const Point &p) &;
	Point rightTop() const;

	//设置矩形的左下角坐标（左边和底部），宽和高都可能会改变，但绝不会改变右上角坐标（右边和顶部）
	void setLeftBottom(float left, float bottom) &;
	void setLeftBottom(const Point &p) &;
	Point leftBottom() const;

	//设置矩形的右下角坐标（右边和底部），宽和高都可能会改变，但绝不会改变左上角坐标（左边和顶部）
	void setRightBottom(float right, float bottom) &;
	void setRightBottom(const Point &p) &;
	Point rightBottom() const;

	//中心
	Point center() const;

	//返回一个标准化的矩形，使它的尺寸为正，并且矫正四个角的坐标排序位置
	Rect normalize() const;

	//点是否属于该矩形区域（注意，除了左上角，左下角、右上角、右下角这几个点都不属于矩形区域包含的点集合）
	bool contains(float x, float y) const;
	bool contains(const Point &p) const;

	//矩形是否完全被此矩形包含
	bool contains(const Rect &rc) const;

	//尺寸为0被判定为Empty
	bool empty() const;

	//是否为Zero矩形
	bool isZero() const;

	//整个在水平和垂直方向移动一定值，不会改变矩形的形状
	void moveHorizontal(float fHorizontal);
	void moveVertical(float fVertical);
	void move(float nHorizontal, float nVertical);

	//移动某条边或者顶点以改变矩形的形状，并非移动整个矩形移动，offset为偏移值
	void moveOffsetLeft(float offset) &;
	void moveOffsetTop(float offset) &;
	void moveOffsetRight(float offset) &;
	void moveOffsetBottom(float offset) &;

	void moveOffsetLeftTop(float offsetX, float offsetY) &;
	void moveOffsetLeftTop(const Point &ptOffset) &;
	void moveOffsetRightTop(float offsetX, float offsetY) &;
	void moveOffsetRightTop(const Point &ptOffset) &;
	void moveOffsetLeftBottom(float offsetX, float offsetY) &;
	void moveOffsetLeftBottom(const Point &ptOffset) &;
	void moveOffsetRightBottom(float offsetX, float offsetY) &;
	void moveOffsetRightBottom(const Point &ptOffset) &;

	//是否与另一个Rect相交
	bool isInterset(const Rect &other) const;

	//与另一个Rect的交集，和 operator & 的效果是一样的
	Rect interset(const Rect &other) const;

	//与另一个Rect的并集，和 operator | 的效果是一样的
	Rect merge(const Rect &other) const;

private:
	float		m_x;
	float		m_y;
	float		m_width;
	float		m_height;
};

//class RectI
class NB_API RectI
{
public:
	//构建一个RectI(0, 0, 0, 0)
	RectI();

	//构建一个RectI(x, y, width, height)
	RectI(int x, int y, int width, int height);

	//构建一个RectI(x, y, size.width, size.height)
	RectI(int x, int y, const SizeI &size);

	//构建一个RectI(leftTop.x, leftTop.y, width, height)
	RectI(const PointI &leftTop, int width, int height);

	//构建一个RectI(leftTop.x, leftTop.y, size.width, size.height)
	RectI(const PointI &leftTop, const SizeI &size);

	//构建一个RectI，塔尔左上角为leftTop，它的右下角为rightBottom
	RectI(const PointI &leftTop, const PointI &rightBottom);

	//从其他RectI构建一个RectI
	RectI(const RectI &other);

	//构建一个零RectI：左、右、顶、底、尺寸都是0被定义为Zero
	static RectI zero();

	//从左、顶、右、底部构建一个Rect
	static RectI fromLTRB(int left, int top, int right, int bottom);

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

public:
	//设置矩形的x（左边），宽可能会被改变，但绝不会改变顶部、底部、右边和高
	void setX(int x) &;
	void setLeft(int left) &;

	//x(left)不可引用
	int x() const;
	int left() const;

	//设置矩形的y（顶部），高可能会被改变，但绝不会改变左边、底部、右边和宽
	void setY(int y) &;
	void setTop(int top) &;

	//y(top)不可引用
	int y() const;
	int top() const;

	//设置矩形的宽，右边可能会改变，但绝不会改变左边、顶部、底部和高
	void setWidth(int width) &;

	//宽，不可引用
	int width() const;

	//设置矩形的高，底部可能会改变，但绝不会改变左边、顶部、右边和宽
	void setHeight(int height) &;

	//高，不可引用
	int height() const;

	//设置矩形的尺寸，右边和底部可能会改变，但绝不会改变左边和顶部
	void setSize(int width, int height) &;
	void setSize(const SizeI &size) &;

	//尺寸
	SizeI size() const;

	//重置矩形
	void reset(int x, int y, int width, int height) &;

	//设置矩形的右边，宽可能会被改变，但绝不会改变左边、顶部、底部和高
	void setRight(int right) &;
	int right() const;

	//设置矩形的底部，高可能会被改变，但绝不会改变左边、顶部、右边和宽
	void setBottom(int bottom) &;
	int bottom() const;

	//设置矩形的左上角坐标（左边和顶部），宽和高都可能会改变，但绝不会改变右下角坐标（右边和底部）
	void setLeftTop(const PointI &p) &;
	PointI leftTop() const;

	//设置矩形的右上角坐标（右边和顶部），宽和高都可能会改变，但绝不会改变左下角坐标（左边和底部）
	void setRightTop(const PointI &p) &;
	PointI rightTop() const;

	//设置矩形的左下角坐标（左边和底部），宽和高都可能会改变，但绝不会改变右上角坐标（右边和顶部）
	void setLeftBottom(const PointI &p) &;
	PointI leftBottom() const;

	//设置矩形的右下角坐标（右边和底部），宽和高都可能会改变，但绝不会改变左上角坐标（左边和顶部）
	void setRightBottom(const PointI &p) &;
	PointI rightBottom() const;

	//中心
	PointI center() const;

	//返回一个标准化的矩形，使它的尺寸为正，并且矫正四个角的坐标排序位置
	RectI normalize() const;

	//点是否属于该矩形区域（注意，除了左上角，左下角、右上角、右下角这几个点都不属于矩形区域包含的点集合）
	bool contains(int x, int y) const;
	bool contains(const PointI &p) const;
	//矩形是否完全被此矩形包含
	bool contains(const RectI &rc) const;

	//尺寸为0被判定为Empty
	bool empty() const;

	//是否为Zero矩形
	bool isZero() const;

	//整个在水平和垂直方向移动一定值，不会改变矩形的形状
	void moveHorizontal(int nHorizontal);
	void moveVertical(int nVertical);
	void move(int nHorizontal, int nVertical);

	//移动某条边或者顶点以改变矩形的形状，并非移动整个矩形移动，offset为偏移值
	void moveOffsetLeft(int offset) &;
	void moveOffsetTop(int offset) &;
	void moveOffsetRight(int offset) &;
	void moveOffsetBottom(int offset) &;

	void moveOffsetLeftTop(int offsetX, int offsetY) &;
	void moveOffsetLeftTop(const PointI &ptOffset) &;
	void moveOffsetRightTop(int offsetX, int offsetY) &;
	void moveOffsetRightTop(const PointI &ptOffset) &;
	void moveOffsetLeftBottom(int offsetX, int offsetY) &;
	void moveOffsetLeftBottom(const PointI &ptOffset) &;
	void moveOffsetRightBottom(int offsetX, int offsetY) &;
	void moveOffsetRightBottom(const PointI &ptOffset) &;

	//是否与另一个RectI相交
	bool isInterset(const RectI &other) const;

	//与另一个RectI的交集，和 operator & 的效果是一样的
	RectI interset(const RectI &other) const;

	//与另一个RectI的并集，和 operator | 的效果是一样的
	RectI merge(const RectI &other) const;

private:
	int		m_x;
	int		m_y;
	int		m_width;
	int		m_height;
};

}}
