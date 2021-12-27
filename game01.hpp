#ifndef game01_hpp
#define game01_hpp

#include <stdio.h>
#include "mainwin.hpp"
#include "mazemap.hpp"
#include "player.hpp"
#include "ghost.hpp"
#include<vector>
class Game01: public MainWin {
public:
    // constructor
    Game01(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);
    
    // destructor
    ~Game01();
    MazeMap* mapMaze;
    Player* player;
    Ghost* ghost;

private:
    void loadData();
    void onRender();
    void onKeyDown(SDL_Event);
    void onKeyUp(SDL_Event);
    void onKeyLeft(SDL_Event);
    void onKeyRight(SDL_Event);
    void onKeyEmpty(SDL_Event);
    
    void getplayerPos(int ,int);
    void getmazeMapP(vector< vector<int> >);
	void getmazeMapG(vector< vector<int> >);
	
	bool killPlayer();
	bool checkcollide();
	int getWofplayer();
	int getHofplayer();
	int getWofghost();
	int getHofghost();
};

#endif
