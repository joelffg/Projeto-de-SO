#include "train.h"
#include <ctime>

Train::Train(int id, int x, int y, Semaphore *sem[])
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 20;
    enable = false;
    semaphores = sem;
}

Train::~Train()
{
    threadTrem.join();
}

void Train::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Train::setEnable(bool enable)
{
    this->enable = enable;
}

void Train::start()
{
    threadTrem = std::thread(&Train::run,this);
}

void Train::run()
{
    while(true){
        if (enable)
        {
            switch(id)
            {
                case 1:
                    emit updatePos(id,x,y);
                    if (x < 80 && y == 20)
                    {
                        if(x == 60)
                        {
                            semaphores[0]->P();
                            emit updateSem(1,false);
                            emit updateLog(id,x,y,1,false);
                        }
                        x+= 5;
                    }
                    else if (x == 80 && y < 230)
                    {
                        if(y == 110)
                        {
                            semaphores[0]->V();
                            emit updateSem(1,true);
                            emit updateLog(id,x,y,1,true);
                        }
                        if(y == 140)
                        {
                            semaphores[1]->P();
                            emit updateSem(2,false);
                            emit updateLog(id,x,y,2,false);
                        }
                        y+= 5;
                    }
                    else if (x > 10 && y == 230){
                        if(x == 60){
                            semaphores[1]->V();
                            emit updateSem(2,true);
                            emit updateLog(id,x,y,2,true);
                        }
                        x-= 5;
                    }
                    else
                    {
                        if (y == 130)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        y-= 5;
                    }
                    break;
                case 2:
                    emit updatePos(id,x,y);
                    if (x < 210 && y == 20)
                    {
                        if(x == 100)
                        {
                            semaphores[0]->V();
                            emit updateSem(1,true);
                            emit updateLog(id,x,y,1,true);
                        }
                        if(x == 150)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        if(x == 190)
                        {
                            semaphores[2]->P();
                            emit updateSem(3,false);
                            emit updateLog(id,x,y,3,false);
                            semaphores[3]->P();
                            emit updateSem(4,false);
                            emit updateLog(id,x,y,4,false);
                        }
                        x+= 5;
                    }
                    else if (x == 210 && y < 90)
                        y+= 5;
                    else if (x > 80 && y == 90)
                    {
                        if(x == 100)
                        {
                            semaphores[0]->P();
                            emit updateSem(1,false);
                            emit updateLog(id,x,y,1,false);
                        }
                        if(x == 130)
                        {
                            semaphores[2]->V();
                            emit updateSem(3,true);
                            emit updateLog(id,x,y,3,true);
                        }
                        if(x == 190)
                        {
                            semaphores[3]->V();
                            emit updateSem(4,true);
                            emit updateLog(id,x,y,4,true);
                        }
                        x-= 5;
                    }
                    else
                        y-= 5;
                    break;
                case 3:
                    emit updatePos(id,x,y);
                    if (x < 340 && y == 20)
                    {
                        if (x == 230)
                        {
                            semaphores[3]->V();
                            emit updateSem(4, true);
                            emit updateLog(id,x,y,4,true);
                        }
                        if (x == 280)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        if (x == 320)
                        {
                            semaphores[5]->P();
                            emit updateSem(6, false);
                            emit updateLog(id,x,y,6,false);
                        }
                        x+= 5;
                    }
                    else if (x == 340 && y < 90)
                        y+= 5;
                    else if (x > 210 && y == 90)
                    {
                        if (x == 290)
                        {
                            semaphores[3]->P();
                            emit updateSem(4, false);
                            emit updateLog(id,x,y,4,false);
                            semaphores[4]->P();
                            emit updateSem(5, false);
                            emit updateLog(id,x,y,5,false);
                        }
                        if (x == 320)
                        {
                            semaphores[5]->V();
                            emit updateSem(6, true);
                            emit updateLog(id,x,y,6,true);
                        }
                        x-= 5;
                    }
                    else
                    {
                        if (y == 70)
                        {
                            semaphores[4]->V();
                            emit updateSem(5, true);
                            emit updateLog(id,x,y,5,true);
                        }
                        y-= 5;
                    }
                    break;
                case 4:
                    emit updatePos(id,x,y);
                    if (x < 410 && y == 20)
                    {
                        if (x == 360)
                        {
                            semaphores[5]->V();
                            emit updateSem(6, true);
                            emit updateLog(id,x,y,6,true);
                        }
                        x+= 5;
                    }
                    else if (x == 410 && y < 230)
                    {
                        if (y == 130)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        y+= 5;
                    }
                    else if (x > 340 && y == 230)
                    {
                        if (x == 360)
                        {
                            semaphores[6]->P();
                            emit updateSem(7, false);
                            emit updateLog(id,x,y,7,false);
                        }
                        x-= 5;
                    }
                    else
                    {
                        if (y == 110)
                        {
                            semaphores[5]->P();
                            emit updateSem(6, false);
                            emit updateLog(id,x,y,6,false);
                        }
                        if (y == 140)
                        {
                            semaphores[6]->V();
                            emit updateSem(7, true);
                            emit updateLog(id,x,y,7,true);
                        }
                        y-= 5;
                    }
                    break;
                case 5:
                    emit updatePos(id,x,y);
                    if (x < 340 && y == 160)
                    {
                        if (x == 290)
                        {
                            semaphores[7]->V();
                            emit updateSem(8, true);
                            emit updateLog(id,x,y,8,true);
                        }
                        if (x == 230)
                        {
                            semaphores[8]->V();
                            emit updateSem(9, true);
                            emit updateLog(id,x,y,9,true);
                        }
                        if (x == 320)
                        {
                            semaphores[6]->P();
                            emit updateSem(7, false);
                            emit updateLog(id,x,y,7,false);
                        }
                        x+= 5;
                    }
                    else if (x == 340 && y < 230)
                        y+= 5;
                    else if (x > 210 && y == 230)
                    {
                        if (x == 230)
                        {
                            semaphores[7]->P();
                            emit updateSem(8, false);
                            emit updateLog(id,x,y,8,false);
                            semaphores[8]->P();
                            emit updateSem(9, false);
                            emit updateLog(id,x,y,9,false);
                        }
                        if (x == 280)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        if (x == 320)
                        {
                            semaphores[6]->V();
                            emit updateSem(7, true);
                            emit updateLog(id,x,y,7,true);
                        }
                        x-= 5;
                    }
                    else
                        y-= 5;
                    break;
                case 6:
                    emit updatePos(id,x,y);
                    if (x < 210 && y == 160)
                    {
                        if (x == 100)
                        {
                            semaphores[1]->V();
                            emit updateSem(2,true);
                            emit updateLog(id,x,y,2,true);
                        }
                        if (x == 130)
                        {
                            semaphores[8]->P();
                            emit updateSem(9,false);
                            emit updateLog(id,x,y,9,false);
                            semaphores[9]->P();
                            emit updateSem(10,false);
                            emit updateLog(id,x,y,10,false);
                        }
                        x+= 5;
                    }
                    else if (x == 210 && y < 230)
                    {
                        if (y == 180)
                        {
                            semaphores[9]->V();
                            emit updateSem(10,true);
                            emit updateLog(id,x,y,10,true);
                        }
                        y+= 5;
                    }
                    else if (x > 80 && y == 230)
                    {
                        if (x == 100)
                        {
                            semaphores[1]->P();
                            emit updateSem(2,false);
                            emit updateLog(id,x,y,2,false);
                        }
                        if (x == 150)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        if (x == 190)
                        {
                            semaphores[8]->V();
                            emit updateSem(9,true);
                            emit updateLog(id,x,y,9,true);
                        }
                        x-= 5;
                    }
                    else
                        y-= 5;
                    break;
                case 7:
                    emit updatePos(id,x,y);
                    if (x < 270 && y == 90)
                    {
                        if (x == 230)
                        {
                            semaphores[2]->V();
                            emit updateSem(3,true);
                            emit updateLog(id,x,y,3,true);
                        }
                        x+= 5;
                    }
                    else if (x == 270 && y < 160)
                    {
                        if (y == 110)
                        {
                            semaphores[4]->V();
                            emit updateSem(5,true);
                            emit updateLog(id,x,y,5,true);
                        }
                        if (y == 130)
                        {
                            gettimeofday(&time, 0);
                            emit sendTime(id, time);
                        }
                        if (y == 140)
                        {
                            semaphores[9]->P();
                            emit updateSem(10,false);
                            emit updateLog(id,x,y,10,false);
                            semaphores[7]->P();
                            emit updateSem(8,false);
                            emit updateLog(id,x,y,8,false);
                        }
                        y+= 5;
                    }
                    else if (x > 150 && y == 160)
                    {
                        if (x == 190)
                        {
                            semaphores[7]->V();
                            emit updateSem(8,true);
                            emit updateLog(id,x,y,8,true);
                        }
                        x-= 5;
                    }
                    else
                    {
                        if (y == 110)
                        {
                            semaphores[4]->P();
                            emit updateSem(5,false);
                            emit updateLog(id,x,y,5,false);
                            semaphores[2]->P();
                            emit updateSem(3,false);
                            emit updateLog(id,x,y,3,false);
                        }
                        if (y == 140)
                        {
                            semaphores[9]->V();
                            emit updateSem(10,true);
                            emit updateLog(id,x,y,10,true);
                        }
                        y-= 5;
                    }
                    break;
                default:
                    break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

