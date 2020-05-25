#include "stdafx.h"
#include "Curves.h"
#include <math.h>

int Ease(int start, int end, double process)
{
	if (process < 0 || process > 1)
		return 0;
	if(process < 0.5)
		return (int)(2 * (end - start) * pow(process, 2) + start);
	else
		return (int)(2 * (start - end) * pow(process - 1, 2) + end);
}

int Accel(int start, int end, double process)
{
	if (process < 0 || process > 1)
		return 0;
	return (int)((end - start) * pow(process, 3) + start);
}

int Decel(int start, int end, double process)
{
	if (process < 0 || process > 1)
		return 0;
	return (int)((end - start) * pow(process - 1, 3) + end);
}