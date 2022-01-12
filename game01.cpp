#include "game01.hpp"
#include<vector> 
#include<iostream>
#include"SDL2/SDL_ttf.h"
#include"SDL2/SDL_mixer.h"
using namespace std;
Game01::Game01(int width, int height):
MainWin(width, height),
mapMaze(NULL),
player(NULL),
weapon(NULL),
ghost(NULL){
	howManyGhosts=0;
	gameNum=0;
	timeChange=false;
}

Game01::~Game01() {
    delete mapMaze;
    mapMaze = NULL;

    delete player;
    player = NULL;
    
    for(int i=0; i<howManyGhosts; i++) {
    	delete[] ghost[i];
	}
	delete[] ghost;
	
	delete weapon;
	weapon = NULL;
	
	delete bomb;
	delete lose;
	delete win;
	delete pointup;
	delete pointdown;
}

void Game01::loadData(int i) {
    //load map
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	}
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    bomb=Mix_LoadWAV("data/bomb.wav");
    splash=Mix_LoadWAV("data/swordslash.wav");
	lose=Mix_LoadWAV("data/losesound.wav");
    
	pointup=Mix_LoadWAV("data/pointsound.wav");
	pointdown=Mix_LoadWAV("data/pointdown.wav");
    mapMaze = new MazeMap(this);
    if (mapMaze) {
    	if(i==1){
    		gameNum = 0;
    		time[gameNum]=30;
    		char path[] = "data/map01.csv";
			mapMaze->loadMap(path);
		}
		else if(i==2){
			gameNum = 1;
			time[gameNum]=40;
    		char path[] = "data/map02.csv";
			mapMaze->loadMap(path);
		}
		else if(i==3){
			gameNum = 2;
			time[gameNum]=55;
    		char path[] = "data/map03.csv";
			mapMaze->loadMap(path);
		}
		else if(i==4){
			gameNum = 3;
			time[gameNum]=55;
    		char path[] = "data/map04.csv";
			mapMaze->loadMap(path);
		}
		else if(i==5){
			gameNum = 4;
			time[gameNum]=80;
    		char path[] = "data/map05.csv";
			mapMaze->loadMap(path);
		}
        char path1[] = "data/block.png";
        bool ret = mapMaze->loadTexture(path1, 0);
        if (!ret) {
            cout<<"Failed to load block texture\n";
        }
        char path2[] = "data/speedup.png";
        ret = mapMaze->loadTexture(path2, 1);
        if (!ret) {
            cout<<"Failed to load speedup texture\n";
        }
        char path3[] = "data/speeddown.png";
        ret = mapMaze->loadTexture(path3, 2);
        if (!ret) {
            cout<<"Failed to load speeddown texture\n";
        }
        char path4[] = "data/shuriken.png";
        ret = mapMaze->loadTexture(path4, 3);
        if (!ret) {
            cout<<"Failed to load shuriken texture\n";
        }
        char path5[] = "data/trap.png";
        ret = mapMaze->loadTexture(path5, 4);
        if (!ret) {
            cout<<"Failed to load trap texture\n";
        }
        char path6[] = "data/shield.png";
        ret = mapMaze->loadTexture(path6, 5);
        if (!ret) {
            cout<<"Failed to load shield texture\n";
        }
        char path7[] = "data/count.png";
        ret = mapMaze->loadTexture(path7, 6);
        if (!ret) {
            cout<<"Failed to load count texture\n";
        }
        char path8[] = "data/portal.png";
        ret = mapMaze->loadTexture(path8, 7);
        if (!ret) {
            cout<<"Failed to load portal texture\n";
        }
    }
    
    //load player texture
    player = new Player(this, mapMaze->playerStartPosX , mapMaze->playerStartPosY , mapMaze);
    if (player) {
        char path[] = "data/ninja_perfect.png";
        bool ret = player->loadTexture(path);
        getmazeMapP(mapMaze->getMap());
        player->initMus();
        if (!ret) {
            cout<<"Failed to load player texture\n";
        }
    }
    //ToDo, load other textures
    howManyGhosts = mapMaze->ghostStartPosX.size();
    cout<<howManyGhosts<<endl;
    ghost = new Ghost* [howManyGhosts];
    for(int i=0; i<howManyGhosts; i++) {
    	ghost[i] = new Ghost(this, mapMaze->ghostStartPosX[i] , mapMaze->ghostStartPosY[i]);
	    if (ghost[i]) {
	        char path[] = "data/ghost01.png";
	        bool ret = ghost[i]->loadTexture(path);
	        getplayerPos(player->pos_x,player->pos_y , i);
	        getmazeMapG(mapMaze->getMap() , i);
	        if (!ret) {
	            cout<<"Failed to load ghost texture\n";
	        }
	    }
	}
}

//custom the rendering
bool Game01::onRender() {
	bool quit = false;
	static int passTime=0;
	const int FPS=60;
	const int frameDelay=1000/FPS;
	Uint32 frameStart;
	int frameTime;
	frameStart=SDL_GetTicks();
    //draw player
   // Mix_PlayMusic( gMusic, -1 );
    
    if(mapMaze)//{cout<<"map rendered\n"; 
		mapMaze->render();
    if(player){//{cout<<"player rendered\n"; 
    	int prepoint=player->point;
		player->render();
		if(player->point>prepoint){
			Mix_PlayChannel(-1,pointup,0);
			if(Mix_PlayChannel(-1,pointup,0)==-1) cout<<"error"<<endl;
		}
		if(player->point<prepoint){
			Mix_PlayChannel(-1,pointdown,0);
			if(Mix_PlayChannel(-1,pointdown,0)==-1) cout<<"error"<<endl;
		}
		
	}
	if(weapon) {
		if(weapon && !weapon->checkNotCollide(weapon->getPosX() , weapon->getPosY() , weapon->getDir()) ) {
	    	cout<<"weapon been hit\n";
	    	//delete weapon;
	    	weapon = NULL;
	    	cout<<"weapon deleted\n";
		}
		else weapon->render();
	}
    
	for(int i=0; i<howManyGhosts; i++) {
		//cout<<"ghost "<<i<<" :";
		if(ghost[i]) {
			ghost[i]->render();
			ghost[i]->handleEvent(player->pos_x,player->pos_y);
		}	
		if(weapon && ghost[i] && collideWithGhost(i) ) {
			Mix_PlayChannel( -1, bomb, 0 );
			if(Mix_PlayChannel( -1, bomb, 0 )==-1){
				cout<<"bomb sound error"<<endl;
			}
    		//delete weapon;
			weapon=NULL;	
    		//delete ghost[i];
    		ghost[i]=NULL;
    		cout<<"ghost["<<i<<"] and weapon being deleted\n";
		}
		if( ( player && ghost[i] && killPlayer(i) )|| time[gameNum]<=0 ){
			cout<<"kill"<<endl;
			quit = true;
			result = LOSE;
			Mix_PlayChannel( -1, lose, 0 );
			if(Mix_PlayChannel( -1, lose, 0 )==-1){
				cout<<"lose sound error"<<endl;
			}
		} 
		if(player->checkWin()){
			cout<<"win"<<endl;
			quit = true;
			result = WIN;
		}
	}
	
	frameTime=SDL_GetTicks()-frameStart;
	passTime++;
	if(passTime>60){
		time[gameNum]-=1;
		passTime=0;
		timeChange=true;
	}
	renderFont(time[gameNum]);
	if(timeChange){
		cout<<time[gameNum]<<endl;
		timeChange=false;
	}
	if(frameDelay>frameTime){
		SDL_Delay(frameDelay-frameTime);
	}
	
	return quit;
}
bool Game01::killPlayer(int i){
	int pw=getWofplayer(),ph=getHofplayer(),gh=getHofghost(i),gw=getWofghost(i);
	if(ghost[i]->pos_x+gw>=player->pos_x&&ghost[i]->pos_x+gw<=player->pos_x+pw){
		if(ghost[i]->pos_y+gh>=player->pos_y&&ghost[i]->pos_y+gh<=player->pos_y+ph)
			return true;
	}
	if(ghost[i]->pos_x+gw>=player->pos_x+pw&&ghost[i]->pos_x<=player->pos_x+pw){
		if(ghost[i]->pos_y+gh>=player->pos_y&&ghost[i]->pos_y+gh<=player->pos_y+ph)
			return true;
	}
	if(ghost[i]->pos_x+gw>=player->pos_x&&ghost[i]->pos_x+gw<=player->pos_x+pw){
		if(ghost[i]->pos_y<=player->pos_y+ph&&ghost[i]->pos_y>=player->pos_y)
			return true;
	}
	if(ghost[i]->pos_x+gw>=player->pos_x+pw&&ghost[i]->pos_x<=player->pos_x+pw){
		if(ghost[i]->pos_y<=player->pos_y+ph&&ghost[i]->pos_y>=player->pos_y)
			return true;
	}
	if(ghost[i]->pos_y<=player->pos_y&&ghost[i]->pos_y+gh>=player->pos_y+ph){
		if(ghost[i]->pos_x+gw>=player->pos_x&&ghost[i]->pos_x+gw<=player->pos_x+pw)
			return true;
	}
	if(ghost[i]->pos_y<=player->pos_y&&ghost[i]->pos_y+gh>=player->pos_y+ph){
		if(ghost[i]->pos_x+gw>=player->pos_x+pw&&ghost[i]->pos_x<=player->pos_x+pw)
			return true;
	}
	return false;
}
bool Game01::collideWithGhost(int i) {
	int weaponWidth=getWofWeapon()/2 , weaponHeight=getHofWeapon()/2 , ghostHeight=getHofghost(i)/2 , ghostWidth=getWofghost(i)/2;
	int weaponPosX = weapon->getPosX() , weaponPosY = weapon->getPosY() , ghostPosX = ghost[i]->pos_x , ghostPosY = ghost[i]->pos_y;
	//ghost left to weapon
	if ( (ghostPosX+ghostWidth) >= (weaponPosX-weaponWidth) && (ghostPosX <= weaponPosX) ) {
		//ghost up to weapon
		if((ghostPosY + ghostHeight)>=(weaponPosY-weaponHeight) && ( ghostPosY<=weaponPosY )){
			//Mix_PlayChannel( -1, bomb, 0 );
			return true;
		} 
		//ghost down to weapon
		if((weaponPosY+weaponHeight >= ghostPosY-ghostHeight) && (ghostPosY >= weaponPosY) ){
			//Mix_PlayChannel( -1, bomb, 0 );
			return true;
		} 
	}
	//ghost right to weapon
	if ((weaponPosX+weaponWidth >= ghostPosX-ghostWidth) && (ghostPosX>=weaponPosX)) {
		//ghost up to weapon
		if((ghostPosY + ghostHeight)>=(weaponPosY-weaponHeight) && ( ghostPosY<=weaponPosY )){
			//Mix_PlayChannel( -1, bomb, 0 );
			return true;
		} 
		//ghost down to weapon
		if((weaponPosY+weaponHeight >= ghostPosY-ghostHeight) && (ghostPosY >= weaponPosY) ){
			//Mix_PlayChannel( -1, bomb, 0 );
			return true;
		} 
	}
	
	return false;
}
int Game01::getHofplayer(){
	return player->getH();	
}
int Game01::getWofplayer(){
	return player->getW();
}
int Game01::getHofghost(int i){
	return ghost[i]->getH();
}
int Game01::getWofghost(int i){
	return ghost[i]->getW(); 
}
int Game01::getHofWeapon(){
	return weapon->getH();	
}
int Game01::getWofWeapon(){
	return weapon->getW();
}

void Game01::getmazeMapP(vector< vector<int> > map){
	player->getmazeMap(map);
}
void Game01::getmazeMapG(vector< vector<int> > map , int i){
	ghost[i]->getmazeMap(map);
}
void Game01::getplayerPos(int x,int y,int i){
	ghost[i]->getplayerPos(x,y);
}

void Game01::onKeyDown(SDL_Event e){
	//player->setAngle(90.f);
	player->handleEvent(e);
}

void Game01::onKeyUp(SDL_Event e){
	//player->setAngle(-90.f);
	player->handleEvent(e); 
}

void Game01::onKeyLeft(SDL_Event e){
	player->setAngle(0.f);
	player->handleEvent(e); 
}

void Game01::onKeyRight(SDL_Event e){
	player->setAngle(0.f);
	player->handleEvent(e); 
}
void Game01::onKeySpace(SDL_Event e){
	player->handleEvent(e);
	if(player->checkIfPower()) {
		Mix_PlayChannel( -1, splash, 0 );
		if(Mix_PlayChannel( -1, splash, 0 )==-1){
			cout<<"channel error"<<endl;
		}
		weapon = new Weapon(this , player->pos_x , player->pos_y , player->direction , mapMaze->getMap());
		player->resetPower();
		if (weapon) {
	        char path1[] = "data/weapon1.png";
	        bool ret = weapon->loadTexture(path1);
	        if (!ret) {
	            cout<<"Failed to load weapon texture\n";
	        }
	    }
	}
}
void Game01::renderFont(int time) {
	TTF_Font* Sans = TTF_OpenFont("data/xttf/xtff.ttf", 12);
	if(!Sans) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	   // handle error
	}
	string str = "time : ";
	stringstream ss;
	ss << time;
	str += ss.str();
	
	SDL_Color Black = {255, 255, 255};
	
	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first

	SDL_Surface* surfaceMessage =
	    TTF_RenderText_Solid(Sans , str.c_str() , Black);
	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 750;  //controls the rect's x coordinate 
	Message_rect.y = 200; // controls the rect's y coordinte
	Message_rect.w = 120; // controls the width of the rect
	Message_rect.h = 60; // controls the height of the rect
	

	SDL_RenderCopy(mRenderer, Message, NULL, &Message_rect);
	//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
