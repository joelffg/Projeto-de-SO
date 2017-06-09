#ifndef DATASYSTEM_H
#define DATASYSTEM_H

#include <QObject>
#include <vector>
#include <sys/time.h>
#include "semaphore.h"

using namespace std;

class DataSystem: public QObject
{
    Q_OBJECT
public slots:
    void recvTime(int, struct timeval);

signals:
    void updateData(int,int,double);

public:
    DataSystem();
    ~DataSystem();

private:
    vector<double> *tData[7];
    struct timeval lastTime[7];
    bool started[7];
    double media[7], desv[7], lastV[7];

    Semaphore *dataSemaphore;
};

#endif // DATASYSTEM_H
