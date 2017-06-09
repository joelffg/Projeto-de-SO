#include "semaphore.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

Semaphore::Semaphore(key_t key, int startValue)
{
    semaphoreId = semget(key,1,IPC_CREAT|0600);
    if (semaphoreId == -1)
    {
        perror("Error ao criar semaforo\n");
        exit(1);
    }
    arg.val = startValue;

    semctl(semaphoreId,0,SETVAL,arg);

    //seta os valores dos structureOperations
    structureOperationP.sem_num = 0;
    structureOperationP.sem_op = -1; //P()
    structureOperationP.sem_flg = SEM_UNDO;

    structureOperationV.sem_num = 0;
    structureOperationV.sem_op = 1; //V()
    structureOperationV.sem_flg = SEM_UNDO;
}

Semaphore::~Semaphore()
{
    semctl(semaphoreId,0,IPC_RMID,arg);
}

void Semaphore::P()
{
    semop(semaphoreId,&structureOperationP,1);
}

void Semaphore::V()
{
    semop(semaphoreId,&structureOperationV,1);
}

int Semaphore::getSemaphoreId()
{
  return semaphoreId;
}

int Semaphore::getValue()
{
    return semctl(semaphoreId,0,GETVAL,arg);
}
