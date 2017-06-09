#include "datasystem.h"
#include <vector>
#include <cmath>

DataSystem::DataSystem()
{
    for (int i = 0; i < 7; i++){
        tData[i] = new vector<double>();
        started[i] = false;
    }

    dataSemaphore = new Semaphore(1228, 1);
}

void DataSystem::recvTime(int id, struct timeval time)
{
    dataSemaphore->P();

    if (started[id-1])
    {
        lastV[id-1] = (time.tv_sec - lastTime[id-1].tv_sec) + (time.tv_usec - lastTime[id-1].tv_usec)/1000000.0;
        emit updateData(id, 2, lastV[id-1]);
        tData[id-1]->push_back(lastV[id-1]);


        if (tData[id-1]->size() > 1)
        {
            int n = tData[id-1]->size();
            double sum = 0, auxDesv, sumDesv = 0;

            for (int i = 0; i < n; i++)
                sum += tData[id-1]->at(i);

            media[id-1] = sum/n;
            emit updateData(id, 0, media[id-1]);

            for (int i = 0; i < n; i++)
            {
                auxDesv = tData[id-1]->at(i) - media[id-1];
                sumDesv += (auxDesv*auxDesv);
            }

            sumDesv /= n;
            desv[id-1] = sqrt(sumDesv);
            emit updateData(id, 1, desv[id-1]);
        }
    }
    else
        started[id-1] = true;

    lastTime[id-1] = time;

    dataSemaphore->V();
}

DataSystem::~DataSystem()
{
    delete dataSemaphore;
}
