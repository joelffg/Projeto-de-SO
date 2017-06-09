#ifndef TREM_H
#define TREM_H

#include "semaphore.h"
#include <QObject>
#include <thread>
#include <chrono>
#include <sys/time.h>

using namespace std;

class Train : public QObject
{
    Q_OBJECT
public:
    Train(int,int,int, Semaphore*[]);
    ~Train();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);

signals:
    void updatePos(int,int,int);
    void updateSem(int,bool);
    void updateLog(int,int,int,int,bool);
    void sendTime(int, struct timeval);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
   Semaphore **semaphores;
   struct timeval time;
};

#endif // TREM_H



