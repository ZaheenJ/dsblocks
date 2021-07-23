#include <time.h>

#include "../util.h"
#include "time.h"

#define ICON_TIME                    " "

size_t
timeu(char *str, int sigval)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        return strftime(str, BLOCKLENGTH, COL6 ICON_TIME "%-l:%M %p", &tm) + 1;
}
