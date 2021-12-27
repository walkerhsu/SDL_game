#include "game01.hpp"
#include<vector> 
#include<iostream>
using namespace std;
Game01::Game01(int width, int height):
MainWin(width, height),
mapMaze(NULL),
player(NULL),

//Manage manager;
//auto& newPlayer(manager.addEntity());

ghost(NULL){
    loadData();
}

Game01::~Game01() {
    delete mapMaze;
    mapMaze = NULL;

    delete player;
    player = NULL;
}

void Game01::loadData() {
    //load map
    mapMaze = new MazeMap(this);
    if (mapMaze) {
        char path[] = "data/map01.csv";
        mapMaze->loadMap(path);
        char path1[] = "data/block.png";
        bool ret = mapMaze->loadTexture(path1);
        if (!ret) {
            cout<<"Failed to load block texture\n";
        }
    }
    
    //load player texture
    player = new Player(this, mapMaze->playerStartPosX , mapMaze->playerStartPosY);
    if (player) {
        char path[] = "data/ninja_perfect.png";
        bool ret = player->loadTexture(path);
        getmazeMapP(mapMaze->getMap());
        if (!ret) {
            cout<<"Failed to load player texture\n";
        }
    }
    //ToDo, load other textures
    ghost = new Ghost(this, mapMaze->ghostStartPosX , mapMaze->ghostStartPosY);
    if (ghost) {
        char path[] = "data/ghost01.png";
        bool ret = ghost->loadTexture(path);
        getplayerPos(player->pos_x,player->pos_y);
        getmazeMapG(mapMaze->getMap());
        if (!ret) {
            cout<<"Failed to load ghost texture\n";
        }
    }
   
    
}

//custom the rendering
void Game01::onRender() {
    //draw player
    mapMaze->render();
    player->render();
	ghost->render();
    ghost->handleEvent(player->pos_x,player->pos_y);
	if(killPlayer()==true) cout<<"kill"<<endl;
}
bool Game01::killPlayer(){
	int pw=getWofplayer(),ph=getHofplayer(),gh=getHofghost(),gw=getWofghost();
	if(ghost->pos_x+gw>player->pos_x&&ghost->pos_x+gw<player->pos_x+pw){
		if(ghost->pos_y+gh>player->pos_y&&ghost->pos_y+gh>player->pos_y+ph)
			return true;
	}
	if(ghost->pos_x+gw>player->pos_x+pw&&ghost->pos_x<player->pos_x+pw){
		if(ghost->pos_y+gh>player->pos_y&&ghost->pos_y+gh>player->pos_y+ph)
			return true;
	}
	if(ghost->pos_x+gw>player->pos_x&&ghost->pos_x+gw<player->pos_x+pw){
		if(ghost->pos_y<player->pos_y+ph&&ghost->pos_y>player->pos_y)
			return true;
	}
	if(ghost->pos_x+gw>player->pos_x+pw&&ghost->pos_x<player->pos_x+pw){
		if(ghost->pos_y<player->pos_y+ph&&ghost->pos_y>player->pos_y)
			return true;
	}
	return false;
}
int Game01::getHofplayer(){
	return player->getH();	
}
int Game01::getWofplayer(){
	return player->getW();
}
int Game01::getHofghost(){
	return ghost->getH();
}
int Game01::getWofghost(){
	return ghost->getW(); 
}

void Game01::getmazeMapP(vector< vector<int> > map){
	player->getmazeMap(map);
}
void Game01::getmazeMapG(vector< vector<int> > map){
	ghost->getmazeMap(map);
}
void Game01::getplayerPos(int x,int y){
	ghost->getplayerPos(x,y);
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
void Game01::onKeyEmpty(SDL_Event e){
	player->handleEvent(e);
}
