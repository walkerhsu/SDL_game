#ifndef weapon_hpp
#define weapon_hpp
#include <vector>
#include <stdio.h>
#include <iostream>
#include "mainwin.hpp"
#include "objectbase.hpp" 
using namespace std;

class Weapon: public ObjectBase {
public:
    // constructor
    Weapon(MainWin* handle , int , int , char , vector<vector<int> >);
    // destructor
    ~Weapon();
    //SDL_Rect* spriteRect();
    //SDL_Rect SpriteRect[5];
    void render();
    bool checkNotCollide(const int , const int ,const char);
   
    int getW();
    int getH();
    int getPosX();
    int getPosY();
    char getDir();
    void operator+= (int);
	
private:
	char dir; //'l' , 'r' , 'u' , 'd'
	int posX,posY;
	int weaponSpeed;
	vector< vector<int> > mazeMap;
	
};
#endif

