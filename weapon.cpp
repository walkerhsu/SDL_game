#include "weapon.hpp"
//constructor
Weapon::Weapon(MainWin* handle , int startPosX , int startPosY , char direction , vector<vector<int> > m):
ObjectBase(handle){
	posX = startPosX;
	posY = startPosY;
	
	dstRect.w = hWin->unitWidth/2;
	dstRect.h = hWin->unitHeight/2;
	dstRect.x = posX+hWin->unitWidth/2;
	dstRect.y = posY+hWin->unitHeight/2;
	
	dir = direction;
	weaponSpeed = 20;
	mazeMap = m;
	m.clear();
}
//destructor
Weapon::~Weapon() {
	mazeMap.clear();
}
void Weapon::render() {
	
    dstRect.x = posX+dstRect.w/2;
    dstRect.y = posY+dstRect.h/2;
    
    *this+=weaponSpeed;
	
    renderTexture(&dstRect, NULL, angle);
    
}

bool Weapon::checkNotCollide(const int x, const int y, const char c){
	if(c=='u'){
		if(posY-weaponSpeed>=0&&mazeMap[(posY-weaponSpeed)/(hWin->unitHeight)][posX/(hWin->unitWidth)]!=0&&mazeMap[(posY-weaponSpeed)/(hWin->unitHeight)][(posX+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	else if(c=='d'){
		if(posY+weaponSpeed+dstRect.h<=(hWin->nHeight)&&mazeMap[(posY+dstRect.h+weaponSpeed)/(hWin->unitHeight)][(posX+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[(posY+dstRect.h+weaponSpeed)/(hWin->unitHeight)][posX/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	else if(c=='l'){
		if(posX-weaponSpeed>=0&&mazeMap[posY/(hWin->unitHeight)][(posX-weaponSpeed)/(hWin->unitWidth)]!=0&&mazeMap[(posY+dstRect.h)/(hWin->unitHeight)][(posX-weaponSpeed)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	else if(c=='r'){
		if(posX+weaponSpeed+dstRect.w<=(hWin->nWidth)&&mazeMap[(posY+dstRect.h)/(hWin->unitHeight)][(posX+weaponSpeed+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[posY/(hWin->unitHeight)][(posX+weaponSpeed+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	return false;
}
void Weapon::operator+=(int v){
	switch(this->dir) {
		case 'u':
			this->angle=0.f;
			this->posY-=v;
			break;
		case 'd':
			this->angle=-180.f;
			this->posY+=v;
			break;
		case 'l':
			this->angle=-90.f;
			this->posX-=v;
			break;
		case 'r':		
			this->angle=90.f;
			this->posX+=v;
			break;
	}
}

int Weapon::getW(){
	return dstRect.w;
}
int Weapon::getH(){
	return dstRect.h;
}
char Weapon::getDir(){
	return dir;
}
int Weapon::getPosX(){
	return posX;
}
int Weapon::getPosY(){
	return posY;
}
