//
// Created by kjanparvari on 5/18/20.
//

#include "types.h"
#include "stat.h"
#include "user.h"
#include "myHeaders.h"
#include "param.h"

struct timeStruct {
    int creationTime;
    int terminationTime;
    int sleepingTime;
    int readyTime;
    int runningTime;
};

// Struct to hold Childrens TT and WT Time
struct processTimeStruct {
    int pid;
    int turnAroundTime;
    int CBT;
    int waitingTime;
};

// Struct to hold Childrens Avg TT and Avg WT Time
struct averageTimeStruct {
    int averageTurnAroundTime;
    int averageCBT;
    int averageWaitingTime;
};

int main(void) {
    struct processTimeStruct pts[10];
    struct averageTimeStruct ats;

    // initializing avg timeStruct attrs to 0
    ats.averageTurnAroundTime = 0;
    ats.averageCBT = 0;
    ats.averageWaitingTime = 0;

    // Change The Scheduling Algorithm To The QUANTUM (the mocified one)
    changePolicy(SCHED_TYPE_MLQ);

    // Create children to print their pid 1000 times
    for (int f = 0; f < 10; f++) {
        int pid = fork();
        if (pid == 0) {      //if 0, that means that we are in the child process
            for (int i = 0; i < 1000; ++i)
                printf(1, "%d : %d \n", getpid(), i);
            exit();
        }
    }

    struct timeStruct *tv = malloc(sizeof(struct timeStruct));
    for (int f = 0; f < 10; f++) {
        // Set the pts variables after one of the children's work is finished
        pts[f].pid = waitForChild(tv);
        pts[f].turnAroundTime = tv->terminationTime - tv->creationTime;
        pts[f].CBT = tv->runningTime;
        pts[f].waitingTime = tv->sleepingTime + tv->readyTime;

        // Update the atv variablles
        ats.averageTurnAroundTime += pts[f].turnAroundTime;
        ats.averageCBT += pts[f].CBT;
        ats.averageWaitingTime += pts[f].waitingTime;
        /*printf(1, "pid %d create %d term %d ready %d sleep %d cbt %d \n"
        , ptv[f].pid, tv->creationTime, tv->terminationTime,
         tv->readyTime, tv->sleepingTime, tv->runningTime);*/
        /*printf(1, "creationTime %d\n", tv->creationTime);
        printf(1, "terminationTime %d\n", tv->terminationTime);
        printf(1, "readyTime %d\n", tv->readyTime);
        printf(1, "sleepingTime %d\n", tv->sleepingTime);
        printf(1, "runningTime %d\n \n", tv->runningTime);*/
    }

    // Print the required time variables of the children
    for (int i = 0; i < 10; i++) {
        printf(1, "Pid %d Turnaround time %d, CBT %d, and Waiting time %d .\n", pts[i].pid, pts[i].turnAroundTime,
               pts[i].CBT, pts[i].waitingTime);
    }

    // Print the average time variables of all of the children
    printf(1, "Average Turnaround time %d, Average CBT %d, and Average Waiting time %d .\n",
           (ats.averageTurnAroundTime / 10), (ats.averageCBT / 10), (ats.averageWaitingTime / 10));
    exit();
}