#include <time.h>

#include "../util.h"
#include "date.h"

#define ICON_DATE                    " "

size_t
dateu(char *str, int sigval)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        return strftime(str, BLOCKLENGTH, COL5 ICON_DATE "%b %-m : %a %-d", &tm) + 1;
}
