#ifndef game01_hpp
#define game01_hpp

#include <stdio.h>
#include "mainwin.hpp"
#include "mazemap.hpp"
#include "player.hpp"
#include "ghost.hpp"
#include "weapon.hpp"
#include<vector>
#include<SDL2/SDL_mixer.h>
extern Result result;

class Game01: public MainWin {
public:
    // constructor
    Game01(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);
    int time[5];
    int gameNum;
    // destructor
    ~Game01();
   
   
	MazeMap* mapMaze;
    Player* player;
    Ghost** ghost;
    Weapon* weapon;
    
private:
	
	void renderFont(int);
    
	bool onRender();
	
	void loadData(int);
    void onKeyDown(SDL_Event);
    void onKeyUp(SDL_Event);
    void onKeyLeft(SDL_Event);
    void onKeyRight(SDL_Event);
    void onKeySpace(SDL_Event);
    
    
	void getplayerPos(int ,int , int);
    void getmazeMapP(vector< vector<int> >);
	void getmazeMapG(vector< vector<int> > , int);
	
	int getWofplayer();
	int getHofplayer();
	int getWofghost(int);
	int getHofghost(int);
	int getHofWeapon();
	int getWofWeapon();
	
	bool killPlayer(int);
	bool collideWithGhost(int);
	
	bool timeChange;
	int howManyGhosts;
	
	Mix_Chunk *splash;
	Mix_Chunk *bomb;
	Mix_Chunk *lose;
	Mix_Chunk *win;
	Mix_Chunk *pointup;
	Mix_Chunk *pointdown;

};

#endif
