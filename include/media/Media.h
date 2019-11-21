#pragma once

namespace nb {
namespace media{

//笔帽样式
enum class PenLineCapE
{
	Flat,		//没有笔帽
	Round,		//圆形笔帽
	Square,		//矩形笔帽
	Triangle,	//三角形笔帽
};

//联接样式
enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};


}}