#include <stdio.h>
#include <stdint.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#include "../util.h"
#include "cpu.h"

#define MAX_FILE_NAME 60
#define FREQ_FILE "/sys/devices/system/cpu/cpu%i/cpufreq/scaling_cur_freq"
#define ICON "﬙"

size_t cpuu(char *str, int sigval) {
	char fileName[MAX_FILE_NAME];
	uint8_t nThreads = get_nprocs_conf();
	uint32_t freq, freqAvg = 0;

	for (int i = 0; i < nThreads; i++) {
		sprintf(fileName, FREQ_FILE, i);

		if (!readint32(fileName, &freq))
			return 0;
		freqAvg += freq;
	}
	freqAvg /= nThreads;

	return SPRINTF(str, COL3 ICON " %.1f GHz %.1f%%", (float) freqAvg / 1000000, cpuPercent(20000));
}

float cpuPercent(uint32_t microseconds) {
	FILE *stat = fopen("/proc/stat", "r");
	uint32_t user[2], nice[2], system[2], idle[2], iowait[2], irq[2], softIrq[2], steal[2];
	uint32_t totalIdle[2], totalNonIdle[2], total[2], totalDiff, idleDiff;

	// Previous
	if (fscanf(stat, "%*s %u %u %u %u %u %u %u %u", 
			&user[0], &nice[0], &system[0], &idle[0],
			&iowait[0], &irq[0],& softIrq[0], &steal[0]) != 8)
		return 0;
	
	rewind(stat);
	usleep(microseconds);
	// Current
	if (fscanf(stat, "%*s %u %u %u %u %u %u %u %u", 
			&user[1], &nice[1], &system[1], &idle[1],
			&iowait[1], &irq[1], &softIrq[1], &steal[1]) != 8)
		return 0;

	for (int i = 0; i <= 1; i++) {
		totalIdle[i] = idle[i] + iowait[i];
		totalNonIdle[i] = user[i] + nice[i] + system[i] + irq[i] + softIrq[i] + steal[i];
		total[i] = totalIdle[i] + totalNonIdle[i];
	}

	totalDiff = total[1] - total[0];
	idleDiff = idle[1] - idle[0];

	fclose(stat);
	return (float) (totalDiff - idleDiff) * 100 / totalDiff;
}
