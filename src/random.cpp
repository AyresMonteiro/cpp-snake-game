#include <stdlib.h>
#include <ctime>

int random_int(int range_init, int range_end)
{
	static bool seeded = 0;

	if (!seeded)
	{
		srand((unsigned)time(0));
	}

	return range_init + (rand() % range_end);
}