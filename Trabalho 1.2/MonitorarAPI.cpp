#include <unistd.h>
#include "APIGPIO.cpp"

enum power {
	off = 0,
	on = 1
};

void setVermelho(power p){
	setDirection(60, "out");
	setValue(60, to_string(p));
}

void setAmarelo(power p){
	setDirection(50, "out");
	setValue(50, to_string(p));
}

void setVerde(power p){
	setDirection(51, "out");
	setValue(51, to_string(p));
}

void setAll(power p){
	setVermelho(p);
	setAmarelo(p);
	setVerde(p);
}

bool buttonIsPressed(){
	setDirection(115, "in");
	
	if(getValue(115) == 1)
		return true;
	else
		return false;
}