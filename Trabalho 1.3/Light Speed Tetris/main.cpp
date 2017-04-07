#include "include/game.h"
#include "include/apiGPIO.h"
#include <cstdio>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>

#define MINSPEED 1000000
#define FRAMEWAIT 16000
#define BDELAY 200000
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"

bool buttonIsPressed(){
    setDirection(115, "in");

    if(getValue(115) == 1)
        return true;
    else
        return false;
}

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

void readPot (int startValue, Game* game) {

    int oldValue = startValue;

    while(1)
    {
        int newValue = readAnalog(0);

        int diference = oldValue - newValue;

        if (abs(diference) > 100) {

            fflush(stdout);

            if (diference < 0)
                game->move(LEFT);
            else
                game->move(RIGHT);

            oldValue = newValue;
        }

        usleep(FRAMEWAIT);
    }
}

void readLDR (Game* game) {

    int speed;

    while(1)
    {
        speed = MINSPEED - readAnalog(1) * 200;

        fflush(stdout);
        usleep(speed);
        game->move(DOWN);
    }
}

void readButton (Game* game) {

    while(1)
    {
        if (buttonIsPressed()){
            fflush(stdout);
            game->roll();
	    usleep(BDELAY);
        }
        else
            usleep(FRAMEWAIT);
    }
}


int main()
{
    Game g;
    g.gameInit();
    int pValue = readAnalog(0);

    thread tPot (readPot, pValue, &g);
    thread tLDR (readLDR, &g);
    thread tBut (readButton, &g);

    sched_param sch1, sch2, sch3;

    int policy1, policy2, policy3;

    pthread_getschedparam(tPot.native_handle(), &policy1, &sch1);
    sch1.sched_priority = 3;

    pthread_getschedparam(tLDR.native_handle(), &policy2, &sch2);
    sch2.sched_priority = 2;

    pthread_getschedparam(tBut.native_handle(), &policy3, &sch3);
    sch3.sched_priority = 1;

    if (pthread_setschedparam(tPot.native_handle(), SCHED_RR, &sch1)) {
        std::cout << "Failed to setschedparam(1): " << std::strerror(errno) << '\n';
    }

    if (pthread_setschedparam(tLDR.native_handle(), SCHED_RR, &sch2)) {
        std::cout << "Failed to setschedparam(3): " << std::strerror(errno) << '\n';
    }
    if (pthread_setschedparam(tBut.native_handle(), SCHED_RR, &sch3)) {
        std::cout << "Failed to setschedparam(3): " << std::strerror(errno) << '\n';
    }

    tPot.join();
    tLDR.join();
    tBut.join();
    
    return 0;
}
