#include "mazemap.hpp"
MazeMap::MazeMap(MainWin* handle):
ObjectBase(handle){
    playerStartPosX = 0;
    playerStartPosY = 0;
	pTextures = new SDL_Texture*[value_total];
}

// destructor
MazeMap::~MazeMap(){
    map.clear();
    for(int i=0; i<value_total; i++) {
    	delete [] pTextures[i];
	}
	delete []pTextures;
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
    cout<<"map has "<<map.size()<<" rows and "<<map[0].size()<<" columns\n";
    cout<<"unitHeight = "<<hWin->unitHeight<<" , and unitWidth = "<<hWin->unitWidth<<endl;
    cout<<"player : "<<playerStartPosX<<' '<<playerStartPosY<<endl;
    for(int i=0; i<ghostStartPosX.size(); i++) {
    	cout<<"ghost[" << i << "]  : "<<ghostStartPosX[i]<<' '<<ghostStartPosY[i]<<endl;
	}
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
					ghostStartPosX.push_back(col);
					ghostStartPosY.push_back(row);
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
	//block
	if(number==0) renderTexture(pTextures[0], &dstRect, NULL, angle);
	//speedup
	else if(number==4) renderTexture(pTextures[1], &dstRect, NULL, angle);
	//speeddown
	else if(number==5) renderTexture(pTextures[2], &dstRect, NULL, angle);
	//shuriken
	else if(number==6) renderTexture(pTextures[3], &dstRect, NULL, angle);
	//trap
	else if(number==7) renderTexture(pTextures[4], &dstRect, NULL, angle);
	//shield
	else if(number==8) renderTexture(pTextures[5], &dstRect, NULL, angle);
	// +5 , +10 , +20 , +35 , +50 , +70 , +85 , +100
	// -5 , -10 , -20 , -35 , -50 , -70 , -85 , -100
	// *2 , *3 , *5 , *10
	// /2 , /3 , /5 , /10
	// *-1 , abs , ^2 , sqrt
	else if(number>=9 && number<=36) {
		srcRect = *spriteRect(number-9);
		renderTexture(pTextures[6], &dstRect, &srcRect, angle);
	}
	
	//portal
	else if(number==37) renderTexture(pTextures[7], &dstRect, NULL, angle);
}

void MazeMap::renderTexture(SDL_Texture* pTextures,SDL_Rect* dstRect, SDL_Rect* srcRect, double angle){
    if (hWin) {
    	if(flip) hWin->renderTexture(pTextures, srcRect, dstRect, angle, SDL_FLIP_HORIZONTAL);
        else hWin->renderTexture(pTextures, srcRect, dstRect, angle, SDL_FLIP_NONE);
        flip=false;
    }
}
bool MazeMap::loadTexture(char path[], int i) {
    pTextures[i] = hWin->loadTexture(path);
    return pTextures[i] == NULL ? false: true;
}

SDL_Rect* MazeMap::spriteRect(int i){
//	frame=0;
	SpriteRect[0].w=70;
	SpriteRect[0].h=42;
	SpriteRect[0].x=0;
	SpriteRect[0].y=0;
	SpriteRect[1].w=90;
	SpriteRect[1].h=45;
	SpriteRect[1].x=100;
	SpriteRect[1].y=0;
	SpriteRect[2].w=90;
	SpriteRect[2].h=45;
	SpriteRect[2].x=200;
	SpriteRect[2].y=0;
	SpriteRect[3].w=90;
	SpriteRect[3].h=45;
	SpriteRect[3].x=295;
	SpriteRect[3].y=0;
	SpriteRect[4].w=90;
	SpriteRect[4].h=45;
	SpriteRect[4].x=390;
	SpriteRect[4].y=0;
	SpriteRect[5].w=90;
	SpriteRect[5].h=45;
	SpriteRect[5].x=485;
	SpriteRect[5].y=0;
	SpriteRect[6].w=90;
	SpriteRect[6].h=45;
	SpriteRect[6].x=580;
	SpriteRect[6].y=0;
	SpriteRect[7].w=110;
	SpriteRect[7].h=45;
	SpriteRect[7].x=680;
	SpriteRect[7].y=0;
	SpriteRect[8].w=70;
	SpriteRect[8].h=42;
	SpriteRect[8].x=0;
	SpriteRect[8].y=70;
	SpriteRect[9].w=90;
	SpriteRect[9].h=45;
	SpriteRect[9].x=100;
	SpriteRect[9].y=70;
	SpriteRect[10].w=90;
	SpriteRect[10].h=45;
	SpriteRect[10].x=199;
	SpriteRect[10].y=64;
	SpriteRect[11].w=90;
	SpriteRect[11].h=45;
	SpriteRect[11].x=295;
	SpriteRect[11].y=70;
	SpriteRect[12].w=90;
	SpriteRect[12].h=45;
	SpriteRect[12].x=390;
	SpriteRect[12].y=70;
	SpriteRect[13].w=90;
	SpriteRect[13].h=45;
	SpriteRect[13].x=485;
	SpriteRect[13].y=70;
	SpriteRect[14].w=90;
	SpriteRect[14].h=45;
	SpriteRect[14].x=580;
	SpriteRect[14].y=70;
	SpriteRect[15].w=110;
	SpriteRect[15].h=45;
	SpriteRect[15].x=680;
	SpriteRect[15].y=70;
	SpriteRect[16].w=70;
	SpriteRect[16].h=50;
	SpriteRect[16].x=0;
	SpriteRect[16].y=140;
	SpriteRect[17].w=60;
	SpriteRect[17].h=50;
	SpriteRect[17].x=100;
	SpriteRect[17].y=140;
	SpriteRect[18].w=70;
	SpriteRect[18].h=50;
	SpriteRect[18].x=190;
	SpriteRect[18].y=140;
	SpriteRect[19].w=90;
	SpriteRect[19].h=50;
	SpriteRect[19].x=290;
	SpriteRect[19].y=140;
	SpriteRect[20].w=60;
	SpriteRect[20].h=45;
	SpriteRect[20].x=395;
	SpriteRect[20].y=140;
	SpriteRect[21].w=60;
	SpriteRect[21].h=45;
	SpriteRect[21].x=490;
	SpriteRect[21].y=140;
	SpriteRect[22].w=65;
	SpriteRect[22].h=45;
	SpriteRect[22].x=585;
	SpriteRect[22].y=140;
	SpriteRect[23].w=90;
	SpriteRect[23].h=45;
	SpriteRect[23].x=680;
	SpriteRect[23].y=140;
	SpriteRect[24].w=60;
	SpriteRect[24].h=35;
	SpriteRect[24].x=0;
	SpriteRect[24].y=220;
	SpriteRect[25].w=80;
	SpriteRect[25].h=60;
	SpriteRect[25].x=105;
	SpriteRect[25].y=205;
	SpriteRect[26].w=70;
	SpriteRect[26].h=65;
	SpriteRect[26].x=190;
	SpriteRect[26].y=200;
	SpriteRect[27].w=80;
	SpriteRect[27].h=65;
	SpriteRect[27].x=295;
	SpriteRect[27].y=200;
	
	return &SpriteRect[i];
}

void MazeMap::changeMap(int row , int col) {
	map[row][col]=1;
}
