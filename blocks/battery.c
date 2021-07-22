#include <stdio.h>
#include <string.h>

#include "../util.h"
#include "battery.h"

#define ICONe                           COL2 "" COL0 /* unexpected error */
#define ICONa                           COL1 "" COL0 /* no battery */

#define ICON0                           "" COL0
#define ICON1                           "" COL0
#define ICON2                           "" COL0
#define ICON3                           "" COL0
#define ICON4                           "" COL0
#define ICON5                           "" COL0
#define ICON6                           "" COL0
#define ICON7                           "" COL0
#define ICON8                           "" COL0
#define ICON9                           "" COL0
#define ICON_CHARGE 			"ﮣ" COL0

#define ICON(bat)                       icons[(bat * (LENGTH(icons) - 1) + 50) / 100]

#define BATCAPFILE                      "/sys/class/power_supply/BAT0/capacity"
#define ACSTATEFILE                     "/sys/class/power_supply/AC/online"
#define BATCNOWFILE                     "/sys/class/power_supply/BAT0/charge_now"

size_t
batteryu(char *str, int ac)
{
        static char *icons[] = { ICON0, ICON1, ICON2, ICON3, ICON4,
                                 ICON5, ICON6, ICON7, ICON8, ICON9 };
        int bat;

        if (!readint(BATCAPFILE, &bat)) {
                strcpy(str, ICONa);
                return sizeof ICONa;
        }
        /* routine update */
        if (ac == NILL) {
                if (!readint(ACSTATEFILE, &ac))
                        return SPRINTF(str, ICONe "%d%%", bat);
                if (ac) {
                	return SPRINTF(str, "%s" ICON_CHARGE" %d%%", ICON(bat), bat);
                } else {
                        return SPRINTF(str, "%s %d%%", ICON(bat), bat);
                }
        /* charger plugged in */
        } else if (ac) {
                return SPRINTF(str, "%s" ICON_CHARGE" %d%%", ICON(bat), bat);
        /* charger plugged out */
        } else {
                return SPRINTF(str, "%s%d%%", ICON(bat), bat);
        }
}
