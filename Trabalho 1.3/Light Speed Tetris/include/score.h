#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <string>

using namespace std;

class Score{
    int score;
	

public:
    Score(){score = 0;};
    void setScore(int s){score = s;};
    void printMessage();
};

#endif
