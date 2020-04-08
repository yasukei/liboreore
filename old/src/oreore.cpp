#include <stdio.h>

extern "C"
{
void oreore(void)
{
	printf("oreore\n");
#ifdef MYDEBUG
	printf("oreore2\n");
#endif
};
} // extern "C"

