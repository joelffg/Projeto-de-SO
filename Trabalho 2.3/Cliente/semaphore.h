#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

class Semaphore
{
public:
    Semaphore(key_t,int);
    ~Semaphore();
    void P();
    void V();
    int getSemaphoreId();
    int getValue();

private:
    union semun{int val;} arg;
    int semaphoreId;
    struct sembuf structureOperationV, structureOperationP;
};

#endif // SEMAPHORE_H
