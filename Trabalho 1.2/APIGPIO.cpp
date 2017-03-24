#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

int getValue(int gpio) {
    ifstream valueFile;

    string path = "/sys/class/gpio/gpio" + to_string(gpio) + "/value";

    valueFile.open(path,ios::in);
    if(valueFile.fail()) {
        valueFile.close();
    }
    else {
        int readValue;
        valueFile >> readValue;

        valueFile.close();
        return readValue;
    }
}

bool setValue(int gpio, string value) {
    ofstream valueFile;

    string path = "/sys/class/gpio/gpio" + to_string(gpio) + "/value";

    valueFile.open(path, ios::out);
    if(valueFile.fail()) {
        valueFile.close();
        return false;
    }
    else {
        valueFile << value;
        valueFile.close();
        return true;
    }
}

string getDirection(int gpio) {
    ifstream directionCheck;

    string path = "/sys/class/gpio/gpio" + to_string(gpio) + "/direction";

    directionCheck.open(path, ios::in|ios::binary);
    if(directionCheck.fail()) {
        directionCheck.close();
    }
    else {
        string readValue;
        directionCheck >> readValue;

        return readValue;
    }
}

bool setDirection(int gpio, string direction) {
    ofstream directionFile;

    string path = "/sys/class/gpio/gpio" + to_string(gpio) + "/direction";

    directionFile.open(path, ios::out);
    if(directionFile.fail()) {
        directionFile.close();
        return false;
    }
    else {
        directionFile << direction;
        directionFile.close();
        return true;
    }
}