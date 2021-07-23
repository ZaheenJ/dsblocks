#include <stdio.h>

#include "../util.h"
#include "ram.h"

#define ICON ""

size_t ramu(char *str, int sigval) {

	FILE *meminfo = fopen("/proc/meminfo", "r");
	float memAvailable, memTotal, memUsed, memUsedPercent;

	if (fscanf(meminfo, "MemTotal: %f kB\n"
			"MemFree: %*f kB\n"
			"MemAvailable: %f kB\n",
			&memTotal, &memAvailable) != 2)
			return 0;
	memUsed = memTotal - memAvailable;
	memUsedPercent = (memUsed / memTotal) * 100;

	fclose(meminfo);
	return SPRINTF(str, COL2 ICON " %.2f GB %.1f%%", memUsed / 1000000, memUsedPercent);
}
