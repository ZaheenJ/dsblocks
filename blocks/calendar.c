#include <time.h>

#include "../util.h"
#include "calendar.h"

#define ICON_DATE                    COL0" "
#define ICON_TIME                    COL0" "

size_t
calendaru(char *str, int sigval)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        return strftime(str, BLOCKLENGTH, ICON_DATE "%b %-m : %a %-d : %-l:%M %p", &tm) + 1;
}
