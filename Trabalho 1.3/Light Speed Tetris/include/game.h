#ifndef GAME_H_
    #define GAME_H_

#include "graph.h"
#include "rand.h"
#include "score.h"

enum MARK{
	GAME_STOP = -1,
	GAME_PAUSE = 0,
	GAME_RUN = 1
};


class Game
{
private:
    int m_penal[24][17];
	color m_color[24][17];
    Context* m_graph;

    pthread_mutex_t mutex_lock;
	Context* nextGraph;
	MARK mark;
public:
    int x;
    int y;
    int auxValue;


private:
    Score s;
private:
        bool recoverPenal();
        bool isAttachBottom();
        bool isAttachLeft();
        bool isAttachRight();
        char getShape();
        bool setPenal();
        bool erasePenal();
public:
    Game();

	~Game();

        void createCube();
        void move(int dir);
        void roll();
        void stop();
        void erase();
        void down(int level);

    void fall();

	void printNextCube(Context* m_graph);
	void gameInit();

MARK getMark();
void setMark( MARK );

void printHelep();

};
#endif