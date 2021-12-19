#ifndef game01_hpp
#define game01_hpp

#include <stdio.h>
#include "mainwin.hpp"
#include "mazemap.hpp"
#include "player.hpp"
#include "ghost.hpp"

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
    void onKeyDown();
    void onKeyUp();
    void onKeyLeft();
    void onKeyRight();
};

#endif
