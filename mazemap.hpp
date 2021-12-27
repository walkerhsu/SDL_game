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

class MazeMap: public ObjectBase {
public:
    // constructor
    MazeMap(MainWin* );
    // destructor
    ~MazeMap();
    void loadMap(char path[]);  // csv file
    void render();
    void drawTexture(int , int , int);
	int playerStartPosX;
	int playerStartPosY;
	int ghostStartPosX;
	int ghostStartPosY;
    vector< vector<int> > getMap();
private:
	void dumpMap();
	vector< vector<int> > map;
};
#endif
