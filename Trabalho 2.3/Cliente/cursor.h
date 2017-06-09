#ifndef CURSOR_H_
#define CURSOR_H_

using namespace std;

class Cursor{
public:
	void saveCursor();		//Save the cursor position
	void moveCursor(const int x,const int y);  //Move the cursor position to the (x, y) coordinates
	void resumeCursor();     //Restore the cursor position
};
#endif