#ifndef CUR_H_
#define CUR_H_

#include<iostream>
using namespace std;

class Cur{
public:
		void saveCur();
		void moveCur(const int x,const int y);
		void resumeCur();
};
#endif

