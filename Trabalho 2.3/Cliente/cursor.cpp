#include "cursor.h"
#include <cstdio>
#include <cstdlib>

void Cursor::moveCursor(const int x,const int y)
{
	int i;
	for(i = 0; i < y; i++)
		printf("\33[1B");
	for(i = 0; i < x; i++)
		printf("\33[1C");
}
void Cursor::saveCursor()
{
	//save cur and move to destination
	printf("\33[s");	
}
void Cursor::resumeCursor()
{
	printf("\33[u");
}
