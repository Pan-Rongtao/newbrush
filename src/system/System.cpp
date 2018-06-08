#include "system/System.h"
#include <math.h>

float nb::System::Pi()
{
	return 3.1415926f;
}

float nb::System::E()
{
	return 2.7182818f;
}

int nb::System::Round(float f)
{
	return (f > 0.0) ? int(f + 0.5) : int(f - 0.5);
}

Int64 nb::System::Round(double d)
{
	return (d > 0.0) ? Int64(d + 0.5) : Int64(d - 0.5);
}

double nb::System::Floor(double d)
{
	return floor(d);
}

double nb::System::Ceil(double d)
{
	return ceil(d);
}

double nb::System::Pow(double base, double exponentn)
{
	return pow(base, exponentn);
}

double nb::System::Log(double a, double N)
{
	return log(N) / log(a);
}

double nb::System::Log10(double N)
{
	return log10(N);
}

double nb::System::Loge(double N)
{
	return Log(E(), N);
}

double nb::System::Sqrt(double base)
{
	return sqrt(base);
}

double nb::System::AngleToRadian(double angle)
{
	return angle * Pi() / 180.0;
}

double nb::System::RadioToAngle(double radian)
{
	return radian * 180.0 / Pi();
}

bool nb::System::ApproximatelyEqual(float f1, float f2)
{
	return Abs(f1 - f2) <= 0.00001f;
}

bool nb::System::ApproximatelyEqual(double d1, double d2)
{
	return Abs(d1 - d2) <= 0.000000000001;
}

bool nb::System::MagnitudeEqual(float f1, float f2)
{
	return (Abs(f1 - f2) <= 0.00001f * Min(Abs(f1), Abs(f2)));
}

bool nb::System::MagnitudeEqual(double d1, double d2)
{
	return (Abs(d1 - d2) <= 0.000000000001 * Min(Abs(d1), Abs(d2)));
}

double nb::System::Sin(double angle)
{
	return sin(angle);
}

double nb::System::Cos(double angle)
{
	return cos(angle);
}

double nb::System::Tan(double angle)
{
	return tan(angle);
}
