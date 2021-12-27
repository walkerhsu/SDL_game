#ifndef ghost_hpp
#define ghost_hpp
#include<ctime>
#include<cstdlib>
#include <stdio.h>
#include "objectbase.hpp"
#include "mainwin.hpp"
#include<vector>
using namespace std;
class Ghost : public ObjectBase{
public:
    // constructor
    Ghost(MainWin* handle , int , int);
    // destructor
    ~Ghost();
    void render();
    SDL_Rect spriteRect[2];
    SDL_Rect spriteRect1[2];
    SDL_Rect* SpriteRect();
    void getplayerPos(int,int);
    void handleEvent(int ,int );
    vector< vector<int> > mazeMap;
	void getmazeMap(vector< vector<int> >);
	bool checkcollide(int,int,char);
	int pos_x,pos_y;
	int getW();
	int getH();
private:

	int v_x,v_y;
	int frame;
	int stop;
	int left;
	int player_x,player_y;
	int seed,moverandom;
};
#endif
