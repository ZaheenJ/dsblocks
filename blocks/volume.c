#include <stdio.h>
#include <stdlib.h>

#include "../util.h"
#include "volume.h"

#define ICON_MUTED 			"婢"
#define ICON_LOW                        "奄"
#define ICON_MEDIUM                     "奔"
#define ICON_HIGH                       "墳"

#define PULSEMIXER                      (char *[]){ "pulsemixer", NULL }
#define TOGGLEMUTE                      (char *[]){ "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL }

size_t
volumeu(char *str, int sigval)
{
	uint8_t volume, mute;
	FILE *fd = popen("pulsemixer --get-volume", "r");

	if (fscanf(fd, "%hhu", &volume) != 1)
		return 1;
	
	pclose(fd);
	fd = popen("pulsemixer --get-mute", "r");
	
	if (fscanf(fd, "%hhu", &mute) != 1)
		return 1;
	pclose(fd);

	if (mute)
        	return SPRINTF(str, COL1 ICON_MUTED);
	else if (volume < 33)
        	return SPRINTF(str, COL1 ICON_LOW " %hhu", volume);
	else if (volume < 66)
        	return SPRINTF(str, COL1 ICON_MEDIUM " %hhu", volume);
	else
        	return SPRINTF(str, COL1 ICON_HIGH " %hhu", volume);
}

void
volumec(int button)
{
        switch(button) {
                case 1:
                        cspawn(TOGGLEMUTE);
                        break;
                case 3:
                        cspawn(PULSEMIXER);
                        break;
        }
}
