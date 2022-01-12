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
	void handleEvent(int ,int );
	
	int pos_x,pos_y;
	int getW();
	int getH();
	
	void getmazeMap(vector< vector<int> >);
	void getplayerPos(int,int);

private:
	
	
	int v_x,v_y;
	int frame;
	int stop;
	int left;
	int player_x,player_y;
	int seed,moverandom;
	int ghost_v;
	bool u , d , l , r;
	vector< vector<int> > mazeMap;
	
	
	SDL_Rect spriteRect[2];
    SDL_Rect spriteRect1[2];
    SDL_Rect* SpriteRect();
    
	bool checkcollide(int,int,char);
	
};
#endif
