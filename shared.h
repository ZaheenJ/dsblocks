#include <limits.h>
#include <stdint.h>
#include <X11/Xlib.h>

#define BLOCKLENGTH                     32
#define NILL                            INT_MIN

#define LENGTH(X)                       (sizeof X / sizeof X[0])

void cleanup();

extern Display *dpy;
extern pid_t pid;
