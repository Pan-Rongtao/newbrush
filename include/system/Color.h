/*******************************************************
**	Color
**
**	颜色类
**	提供RGB颜色模式、HSV（与HSB是一样的）颜色模式、32位整型
**	和十六进制#RRGGBBAA字符串格式（如#FF00FFFF）的构建方式。
**	
**
**	可对各模式的参数进行设置和查询
**	RGB模式：R、G、B（整型参数范围为0~255，浮点参数为0.0~1.0）
**  SHV模式：S、H、B（S[0.0,360.0]、H[0.0,1.0]、B[0.0,1.0]
**	
**
**		潘荣涛
**	
********************************************************/

#pragma once
#include "core/ValueObject.h"
#include "Global.h"
#include "SystemDef.h"

namespace nb{namespace System{

class NB_SYSTEM_DECLSPEC_INTERFACE Color : public Core::ValueObject
{
	NB_OBJECT_TYPE_DECLARE();

//public funs.
public:
	//0~255 argb
	int GetAlpha() const;
	int GetRed() const;
	int GetGreen() const;
	int GetBlue() const;

	void SetAlpha(int a);
	void SetRed(int r);
	void SetGreen(int g);
	void SetBlue(int b);

	void SetRgb(int r, int g, int b);
	void SetArgb(int a, int r, int g, int b);

	//不允许使用引用，因为使用引用做运算不能检测到值异常
/*		const int &A() const;
	int &A();
	const int &R() const;
	int &R();
	const int &G() const;
	int &G();
	const int &B() const;
	int &B();
*/
	//0.0~1.0 argb
	float GetAlphaF() const;
	float GetRedF() const;
	float GetGreenF() const;
	float GetBlueF() const;

	void SetAlphaF(float a);
	void SetRedF(float r);
	void SetGreenF(float g);
	void SetBlueF(float b);

	void SetRgbF(float r, float g, float b);
	void SetArgbF(float a, float r, float g, float b);

	//HSV色调、饱和度、亮度
	float GetHue() const;
	float GetSaturation() const;
	float GetValue() const;
	void SetHue(float h);
	void SetSaturation(float s);
	void SetValue(float v);
	void SetHsv(float h, float s, float v);

	////屏蔽cmyk格式
	//void SetCmyk(int c, int m, int y, int k);
	//void GetCmyk(int *c, int *m, int *y, int *k);

	//void SetRgbaHexString(const String &sHex);
	//String GetRgbaHexString() const;

	//转换成32位整数，0xAARRGGBB
	void SetInteger32(unsigned int argb);
	//0xAARRGGBB
	unsigned int ToInteger32() const;

	bool Equals(const Color &other) const;

	bool IsEmpty() const;
//Constructors & operators override
public:
	Color();
	Color(int r, int g, int b);
	Color(int a, int r, int g, int b);
	Color(const Color &other);
	~Color();

	void operator =(const Color &other);

	bool operator ==(const Color &other) const;
	bool operator !=(const Color &other) const;

//public static funs.
public:
	//整型argb是否合法，argb：[0~255]
	static bool IsValidArgb(int a, int r, int g, int b);

	//浮点argb是否合法，argb：[0.0~1.0]
	static bool IsValidArgbF(float a, float r, float g, float b);

	//HSV格式数据是否合法，h：[0.0~360.0]	s：[0.0~1.0]	v：[0.0~1.0]
	static bool IsValidHsv(float h, float s, float v);

	//argb组成的32位整形数，格式化为0xAARRGGBB
	static Color FromInteger32(unsigned int argb);

	//HSV（色调、饱和度、亮度）格式的数据读入，h：[0.0~360.0]	s：[0.0~1.0]	v：[0.0~1.0]
	static Color FromHsv(float h, float s, float v);

	////屏蔽cmyk格式
	//Cmyk格式的数据格式
	//static Color FromCmyk(int c, int m, int y, int k);

	//浮点形式的argb，a、r、g、b范围0.0~1.0
	static Color FromRgbF(float r, float g, float b);
	static Color FromArgbF(float a, float r, float g, float b);

	static Color Empty();
	//#AARRGGBB argb字符串
	//static Color FromArgbHexString(const String &sHex);


private:
	//返回值将被四舍五入，比如如果R计算为127.5，置为128
	static int ArgbF2Argb(float f);
	//返回结果将保持float的小数精度
	static float Argb2ArgbF(int n);

	//rgbF与hsv的转换
	static void RgbF2Hsv(float r, float g, float b, float &h, float &s, float &v);
	static void Hsv2RgbF(float h, float s, float v, float &r, float &g, float &b);


	int		m_nAlpha;
	int		m_nRed;
	int		m_nGreen;
	int		m_nBlue;
};

}}
