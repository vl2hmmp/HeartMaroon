
#include "utils.h"

int limit(int val, int min, int max)
{
	if (val < min)
		val = min;
	if (max < val)
		val = max;
	return val;
}
