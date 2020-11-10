#ifndef __SSINTERPOLATION__
#define __SSINTERPOLATION__


class SsCurve;

inline bool SsNeedsCurveParams(SsInterpolationType::_enum type)
{
	switch (type)
	{
	case SsInterpolationType::bezier:
	case SsInterpolationType::hermite:
		return true;
	}
	return false;
}

float	SsInterpolate(SsInterpolationType::_enum type, float time, float start, float end, const SsCurve * curve);

#endif
