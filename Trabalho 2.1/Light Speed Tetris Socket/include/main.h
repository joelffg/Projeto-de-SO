#ifndef MAIN_H_
#define MAIN_H_

#include "game.h"
#include "apiGPIO.h"
#include <cstdio>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <cmath>

class Mensagem {
    public:
        bool button;
        int pot;
        int ldr;
        Mensagem();
};
 
Mensagem::Mensagem()
{
    button = false;
}

void readPot (int startValue, Game* game, Mensagem* mensagem);
void readLDR (Game* game, Mensagem* mensagem);
void readButton (Game* game, Mensagem* mensagem);
void game(Mensagem mensagem, Game* g, int oldValue);

#endif