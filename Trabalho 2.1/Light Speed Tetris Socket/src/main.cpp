#include "../include/game.h"
#include "../include/apiGPIO.h"
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

class Mensagem {
    public:
        bool button;
        int pot;
        int ldr;
        Mensagem();
};

void readPot (int startValue, Game* game, Mensagem* mensagem) {

    int oldValue = startValue;

    int newValue = mensagem->pot;

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

void readLDR (Game* game, Mensagem* mensagem) {

    int speed = MINSPEED - mensagem->ldr * 200;

    fflush(stdout);
    usleep(speed);
    game->move(DOWN);
}

void readButton (Game* game, Mensagem* mensagem) {

    if (mensagem->button){
        fflush(stdout);
        game->roll();
    usleep(BDELAY);
    }
    else
        usleep(FRAMEWAIT);
}


void game(Mensagem mensagem, Game* g, int oldValue) {
    int pValue = oldValue;

    thread tPot (readPot, pValue, g, &mensagem);
    thread tLDR (readLDR, g, &mensagem);
    thread tBut (readButton, g, &mensagem);

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
    
    fflush(stdout);

    tPot.join();
    tLDR.join();
    tBut.join();
}
