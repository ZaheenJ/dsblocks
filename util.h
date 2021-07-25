#include "shared.h"

#define COL0                            "\x0b" /* default status color */
#define COL1                            "\x0d" /* default icon color */
#define COL2                            "\x0e" /* alternate icon color */
#define COL3                            "\x0f" /* mail block - syncing */
#define COL4                            "\x10" /* mail block - frozen */
#define COL5                            "\x11" /* mail block - frozen */
#define COL6                            "\x12" /* mail block - frozen */

#define SCRIPT(name)                    "/home/zaheen/.local/bin/"name
#define TERMCMD(cmd)                    cspawn((char *[]){ "st", "-e", cmd, NULL })

#define SPRINTF(str, ...)               ({ \
                                                int len = snprintf(str, BLOCKLENGTH, __VA_ARGS__); \
                                                len < BLOCKLENGTH ? len + 1 : BLOCKLENGTH; \
                                        })

void cspawn(char *const *arg);
void csigself(int sig, int sigval);
size_t getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen);
int readint(const char *path, int *var);
int readint32(const char *path, uint32_t *var);
void uspawn(char *const *arg);
