#ifndef player_hpp
#define player_hpp
#include<vector>
#include <stdio.h>
#include <cmath>
#include "mainwin.hpp"
#include "mazemap.hpp" 
#include "objectbase.hpp" 
#include"SDL2/SDL_mixer.h"
using namespace std;

class Player: public ObjectBase {
public:
	int player_vx,player_vy,player_v;
	SDL_Event e;
    // constructor
    Player(MainWin* handle , int , int , MazeMap*);
	
    // destructor
    ~Player();
    
    
    bool checkcollide(int ,int ,char);
    bool checkIfPower();
    
    int bumpintoWhat();
    
	void resetPower();
    	
	int getW();
    int getH();
    void getmazeMap( vector< vector<int> >);
    bool checkWin();
    int pos_x,pos_y;
    int point;
	char direction;
	void initMus();
	
	bool getPower();
	bool getProtect();
	
	void render();
	void handleEvent(SDL_Event&);
    void setAngle(double);
private:
	MazeMap* MapMaze;
	void renderFont(int );
	int a;
	int v_x,v_y;
	int frame;
	int stop;
	int left;
	int trapcnt,fastcnt,slowcnt;
	int att,attframe;
	
	bool protect,trapUse;
	double fast,slow;
	double trap;
	bool power; 
	
	void changePoint(int);
	
	void move();
    
	vector< vector<int> > mazeMap;

	SDL_Rect* spriteRect();
    SDL_Rect SpriteRect[5];
    SDL_Rect SpriteRect1[4]; 
    	
    Mix_Chunk *win;
};
#endif
