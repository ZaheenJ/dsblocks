#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "util.h"

void
cspawn(char *const *arg)
{
        setsid();
        execvp(arg[0], arg);
        perror("cspawn - execvp");
        _exit(127);
}

void
csigself(int sig, int sigval)
{
        union sigval sv;

        sig += SIGRTMIN;
        sv.sival_int = sigval;
        if (sigqueue(pid, sig, sv) == -1) {
                perror("csigself - sigqueue");
                exit(1);
        }
}

/* getcmdout doesn't null terminate cmdout
 * make sure that terminal newline character is handled if the command spits one */
size_t
getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen)
{
        int fd[2];
        size_t trd;
        ssize_t rd;

        if (pipe(fd) == -1) {
                perror("getcmdout - pipe");
                cleanup();
                exit(1);
        }
        switch (fork()) {
                case -1:
                        perror("getcmdout - fork");
                        cleanup();
                        exit(1);
                case 0:
                        close(ConnectionNumber(dpy));
                        close(fd[0]);
                        if (fd[1] != STDOUT_FILENO) {
                                if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                                        perror("getcmdout - child - dup2");
                                        exit(1);
                                }
                                close(fd[1]);
                        }
                        execvp(arg[0], arg);
                        perror("getcmdout - child - execvp");
                        _exit(127);
                default:
                        close(fd[1]);
                        trd = 0;
                        do
                                rd = read(fd[0], cmdout + trd, cmdoutlen - trd);
                        while (rd > 0 && (trd += rd) < cmdoutlen);
                        if (rd == -1) {
                                perror("getcmdout - read");
                                cleanup();
                                exit(1);
                        }
                        close(fd[0]);
        }
        return trd;
}

int
readint(const char *path, int *var) {
        FILE *fp;

        if (!(fp = fopen(path, "r")))
                return 0;
        if (fscanf(fp, "%d", var) != 1) {
                fclose(fp);
                return 0;
        }
        fclose(fp);
        return 1;
}

int
readint32(const char *path, uint32_t *var) {
        FILE *fp;

        if (!(fp = fopen(path, "r")))
                return 0;
        if (fscanf(fp, "%u", var) != 1) {
                fclose(fp);
                return 0;
        }
        fclose(fp);
        return 1;
}

void
uspawn(char *const *arg)
{
        switch (fork()) {
                case -1:
                        perror("uspawn - fork");
                        cleanup();
                        exit(1);
                case 0:
                        close(ConnectionNumber(dpy));
                        setsid();
                        execvp(arg[0], arg);
                        perror("uspawn - child - execvp");
                        _exit(127);
        }
}
