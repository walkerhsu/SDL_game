#include "mazemap.hpp"
MazeMap::MazeMap(MainWin* handle):
ObjectBase(handle){
    playerStartPosX = 0;
    playerStartPosY = 0;
    ghostStartPosX = 0;
    ghostStartPosY = 0;
}

// destructor
MazeMap::~MazeMap(){
    map.clear();
}

void MazeMap::loadMap(char path[]){
    map.clear();
    
    //readfile
    fstream file;
    file.open(path);
    string line;
    int row=0;
    while (getline(file, line, '\n')) { //read till rew line char
        if (line.length() > 0) {
            vector<int> element = vector<int>();
            map.push_back(element);
        }
        istringstream templine(line); //string to stream
        string data;
        while (getline(templine, data, ',')) { //read till comma
            map[row].push_back(atoi(data.c_str() ) ); //string to int
        }
        row++;
    }
    file.close();
    hWin->unitWidth = (hWin->nWidth) / map[0].size();
    hWin->unitHeight= (hWin->nHeight) / map[0].size();
    dumpMap();
    cout<<"player : "<<playerStartPosX<<' '<<playerStartPosY<<endl;
    cout<<"ghost  : "<<ghostStartPosX<<' '<<ghostStartPosY<<endl;
}

void MazeMap::dumpMap(){
    if (map.size() >0) {
        for (int row=0; row< map.size(); row++){
            for (int col=0; col<map[row].size(); col++ ) {
                cout << map[row][col];
                //player start place
                if(map[row][col]==2) {
                	playerStartPosX = col;
                	playerStartPosY = row;
				}
				//ghost start place
				else if(map[row][col]==3) {
					ghostStartPosX = col;
					ghostStartPosY = row;
				}
            }
            cout << endl;
        }
    }
}
vector< vector<int> > MazeMap::getMap() {
	return map;
}

void MazeMap::render() {
	if (map.size() > 0) {
        for (int row=0; row< map.size(); row++){
            for (int col=0; col<map[row].size(); col++ ) {
                drawTexture(map[row][col] , row , col);
            }
        }
    }
} 

void MazeMap::drawTexture(int number, int row, int col) {
	dstRect.x = col * hWin->unitWidth;
	dstRect.y = row * hWin->unitHeight; 
	dstRect.w = hWin->unitWidth;
	dstRect.h = hWin->unitHeight; 
	if(number==0) renderTexture(&dstRect, NULL, angle);
}

