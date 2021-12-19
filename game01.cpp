#include "game01.hpp"

Game01::Game01(int width, int height):
MainWin(width, height),
mapMaze(NULL),
player(NULL),
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
    mapMaze = new MazeMap();
    if (mapMaze) {
        char path[] = "data/map01.csv";
        mapMaze->loadMap(path);
    }
    
    //load player texture
    player = new Player(this);
    if (player) {
        char path[] = "mouse.png";
        bool ret = player->loadTexture(path);
        if (!ret) {
            cout<<"Failed to load player texture\n";
        }
    }
    //ToDo, load other textures
    ghost = new Ghost(this);
    if (ghost) {
        char path[] = "ghost.png";
        bool ret = ghost->loadTexture(path);
        if (!ret) {
            cout<<"Failed to load ghost texture\n";
        }
    }
}

//custom the rendering
void Game01::onRender() {
    //draw player
    player->render();
	ghost->render();
    
}

void Game01::onKeyDown() {
	player->setAngle(0.f);
}

void Game01::onKeyUp(){
	player->setAngle(180.f);
}

void Game01::onKeyLeft(){
	player->setAngle(90.f);
}

void Game01::onKeyRight(){
	player->setAngle(-90.f);
}
