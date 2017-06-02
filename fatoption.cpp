#include "fatoption.h"


FatOption::FatOption()
{
}


FatOption::~FatOption()
{
}

bool FatOption::check(double size, double cir)
{
	return ( ( minSize <= size) && ( size <= maxSize ) ) && ( ( minCir <= cir) && ( cir <= maxCir ) );
}