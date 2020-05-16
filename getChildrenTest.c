//
// Created by kjanparvari on 5/10/20.
//

#include "types.h"
#include "stat.h"
#include "user.h"


int
main(void) {
//    int a;
//    int *flag = &a;  // zero means its free to print - one means someone is printing
//    *(flag) = 0;
//    fork();
//    fork();
//    fork();
//
//    while (*(flag) == 1) {continue;}
//
//    *(flag) = 1;
//    printf(1, getchildren());
//    printf(1, "\n");
//    *(flag) = 0;
//
//    while (*(flag) == 1) {continue;}
    if (fork() != 0)
        if (fork() != 0)
            if (fork() != 0)
                if (fork() != 0)
                    printf(1, getchildren());

    while (wait() != -1)
        wait();

    exit();
}