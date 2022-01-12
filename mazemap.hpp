#ifndef mazemap_hpp
#define mazemap_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include "mainwin.hpp"
#include "objectbase.hpp"
using namespace std;
enum MapValue{
	block,
	speedup,
	speeddown,
	shuriken,
	trap,
	shield,
	count,
	portal,
	value_total
};

class MazeMap: public ObjectBase {
public:
    // constructor
    MazeMap(MainWin* );
    // destructor
    ~MazeMap();
    void loadMap(char path[]);  // csv file
    void render();

	vector < int > ghostStartPosX, ghostStartPosY;
	vector< vector<int> > getMap();
    bool loadTexture(char[] , int );
    void changeMap(int , int );
    
    int playerStartPosX, playerStartPosY;

private:
	vector< vector<int> > map;
	
	void dumpMap();
	void drawTexture(int , int , int);
	void renderTexture(SDL_Texture* pTextures, SDL_Rect* dstRect, SDL_Rect* srcRect, double angle);
	SDL_Rect* spriteRect(int i);
	
	SDL_Texture** pTextures;
    SDL_Rect SpriteRect[28];
};
#endif
