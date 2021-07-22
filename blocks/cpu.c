#include <stdio.h>
#include <stdint.h>
// #include <inttypes.h>
#include <sys/sysinfo.h>

#include "../util.h"
#include "cpu.h"

#define MAX_FILE_NAME 60
#define FREQ_FILE "/sys/devices/system/cpu/cpu%i/cpufreq/scaling_cur_freq"
#define ICON ""

size_t cpuu(char *str, int sigval) {
	uint8_t nThreads = get_nprocs_conf();
	uint32_t freq, freqAvg = 0;

	for (int i = 0; i < nThreads; i++) {
		char fileName[MAX_FILE_NAME];
		sprintf(fileName, FREQ_FILE, i);

		if (!readint32(fileName, &freq))
			return 0;
		freqAvg += freq;
	}
	freqAvg /= nThreads;

	return SPRINTF(str, ICON " %.1f GHz", (float) freqAvg / 1000000);
}
