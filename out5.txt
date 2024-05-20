#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int st;

    if (fork())
        wait(&st);
    else
        while (1);
}