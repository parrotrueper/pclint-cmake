/**
 * \file util_DateTime.c
 * \brief Date utilities
 *
 */

#include "util_DateTime.h"


/**
 * \brief Check if specified year is a leap year
 * \param i_u32Year  Year to check
 * \returns true if it is a leap year
 **/
bool util_DateTime_IsLeapYear(uint32_t i_u32Year)
{
	bool bResult = true;

	/* If it's not a fourth year, it's not a leap year */
	if (i_u32Year % 4){
		bResult = false;
	}
	/* It is a fourth year, if it's a century then special handling needed */
	else if (!(i_u32Year % 100)){
		/* If it's not a fourth century then it's not a leap year */
		if (i_u32Year % 400){
			bResult = false;
		}
		/* Otherwise it's a leap year */
	}
	/* Otherwise it's a leap year */

	return bResult;
}

