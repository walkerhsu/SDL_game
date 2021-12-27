#ifndef player_hpp
#define player_hpp
#include<vector>
#include <stdio.h>
#include "mainwin.hpp"
#include "objectbase.hpp" 
using namespace std;

class Player: public ObjectBase {
public:
	int player_v;
	SDL_Event e;
    // constructor
    Player(MainWin* handle , int , int);
	
    // destructor
    ~Player();
    SDL_Rect* spriteRect();
    SDL_Rect SpriteRect[5];
    void render();
    int getW();
    int getH();
    void setAngle(double playerAngle);
    bool checkcollide(int ,int ,char);
    void handleEvent(SDL_Event& e);
    vector< vector<int> > mazeMap;
	int pos_x,pos_y;
	void getmazeMap( vector< vector<int> >);
	int bumpintoWhat();
private:
	int a;
	int v_x,v_y;
	int frame;
	int stop;
	int left;
	int trap,fast,slow,power,protect;
};
#endif
