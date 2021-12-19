#ifndef mazemap_hpp
#define mazemap_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
using namespace std;

class MazeMap{
public:
    // constructor
    MazeMap();
    
    // destructor
    ~MazeMap();
    
    vector<vector<int> > matrix;

    void loadMap(char path[]);  // csv file
    void dumpMap();
};
#endif
