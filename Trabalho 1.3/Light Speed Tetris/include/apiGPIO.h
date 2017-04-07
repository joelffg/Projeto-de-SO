#ifndef APIGPIO_H_
#define APIGPIO_H_

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

int getValue(int gpio);
bool setValue(int gpio, string value);
string getDirection(int gpio);
bool setDirection(int gpio, string direction);

#endif