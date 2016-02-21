#include "libm.h"

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
int __fpclassifyl(long double x)
{
	return __fpclassify(x);
}
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
int __fpclassifyl(long double x)
{
	union ldshape u = {x};
/*	int e = u.i.se & 0x7fff;
	int msb = u.i.m>>63;
	if (!e && !msb)
		return u.i.m ? FP_SUBNORMAL : FP_ZERO;
	if (!msb)
		return FP_NAN;
	if (e == 0x7fff)
		return u.i.m << 1 ? FP_NAN : FP_INFINITE;
	return FP_NORMAL;
*/
	int e = u.bits.exp;
	if (!e) {
		if (u.bits.m >> 63) return FP_NAN;
		else if (u.bits.m) return FP_SUBNORMAL;
		else return FP_ZERO;
	}
	if (e == 0x7fff)
		return u.bits.m & (uint64_t)-1>>1 ? FP_NAN : FP_INFINITE;
	return u.bits.m & (uint64_t)1<<63 ? FP_NORMAL : FP_NAN;
}
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384
int __fpclassifyl(long double x)
{
	union ldshape u = {x};
/*	int e = u.i.se & 0x7fff;
	u.i.se = 0;
	if (!e)
		return u.i2.lo | u.i2.hi ? FP_SUBNORMAL : FP_ZERO;
	if (e == 0x7fff)
		return u.i2.lo | u.i2.hi ? FP_NAN : FP_INFINITE;
*/
	int e = u.bits.exp;
	if (!e)
		return u.bits.mlo | u.bits.mhi ? FP_SUBNORMAL : FP_ZERO;
	if (e == 0x7fff)
		return u.bits.mlo | u.bits.mhi ? FP_NAN : FP_INFINITE;
	return FP_NORMAL;
}
#endif
