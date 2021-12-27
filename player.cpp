#include "player.hpp"

Player::Player(MainWin* handle, int startX , int startY):
ObjectBase(handle){
    pos_x=startX * hWin->unitWidth;
	pos_y=startY * hWin->unitHeight;
	v_x=0,v_y=0;
	frame=0;
	stop=0;
	left=0;
	player_v=10,slow=2;
}	

// destructor
Player::~Player(){
	
}
void Player::render() {
	const int FPS=60;
	const int frameDelay=1000/FPS;
	Uint32 frameStart;
	int frameTime;
	frameStart=SDL_GetTicks();
	
    dstRect.w = hWin->unitWidth/1.5;
    dstRect.h = hWin->unitHeight/1.5;
    dstRect.x = pos_x;
    dstRect.y = pos_y;
    printf("player : %d , %d\n" , pos_x,pos_y);
    srcRect=*spriteRect();
    if(left==1) flip=true;
    renderTexture(&dstRect, &srcRect, angle);
    
    frameTime=SDL_GetTicks()-frameStart;
	if(frameDelay>frameTime){
		SDL_Delay(frameDelay-frameTime);
	}
    //handleEvent(e);
}

void Player::setAngle(double playerAngle) {
	angle = playerAngle;
}
void Player::getmazeMap(vector< vector<int> > map){
	mazeMap=map;
}
bool Player::checkcollide(int x,int y,char c){
	if(c=='u'){
		if(y-10>=0&&mazeMap[(y-10)/(hWin->unitHeight)][x/(hWin->unitWidth)]!=0&&mazeMap[(y-10)/(hWin->unitHeight)][(x+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='d'){
		if(y+10+dstRect.h<=(hWin->nHeight)&&mazeMap[(y+dstRect.h+10)/(hWin->unitHeight)][(x+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h+10)/(hWin->unitHeight)][x/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='l'){
		if(x-10>=0&&mazeMap[y/(hWin->unitHeight)][(x-10)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h)/(hWin->unitHeight)][(x-10)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='r'){
		if(x+10+dstRect.w<=(hWin->nWidth)&&mazeMap[(y+dstRect.h)/(hWin->unitHeight)][(x+10+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[y/(hWin->unitHeight)][(x+10+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	return false;
}
int Player::bumpintoWhat(){
	if(mazeMap[pos_y/50][pos_x/50]!=0&&mazeMap[pos_y/50][pos_x/50]!=1) 
		return mazeMap[pos_y/50][pos_x/50];
	if(mazeMap[(pos_y+dstRect.h)/50][pos_x/50]!=0&&mazeMap[(pos_y+dstRect.h)/50][pos_x/50]!=1)
		return mazeMap[(pos_y+dstRect.h)/50][pos_x/50];
	if(mazeMap[(pos_y+dstRect.h)/50][(pos_x+dstRect.w)/50]!=0&&mazeMap[(pos_y+dstRect.h)/50][(pos_x+dstRect.w)/50]!=1)
		return mazeMap[(pos_y+dstRect.h)/50][(pos_x+dstRect.w)/50];
	if(mazeMap[(pos_y)/50][(pos_x+dstRect.w)/50]!=0&&mazeMap[(pos_y)/50][(pos_x+dstRect.w)/50]!=1)
		return mazeMap[(pos_y)/50][(pos_x+dstRect.w)/50];
}
int Player::getW(){
	return dstRect.w;
}
int Player::getH(){
	return dstRect.h;
}
void Player::handleEvent(SDL_Event &e){
	if(e.type==SDL_KEYDOWN){
		switch( e.key.keysym.sym ){
            case SDLK_UP:
            	if(checkcollide(pos_x,pos_y,'u')) {
            		pos_y -= 10; 
					stop=1;
				}
				left=0;
				break;
        	case SDLK_DOWN: 
           		if(checkcollide(pos_x,pos_y,'d')) {
           			pos_y += 10;
					stop=1;
				}
				left=0;
				break;
            case SDLK_LEFT: 
            	if(checkcollide(pos_x,pos_y,'l')) {
            		pos_x -= 10;
					stop=1;
				}
				left=1;
				break;
            case SDLK_RIGHT:
			 	if(checkcollide(pos_x,pos_y,'r')){
					pos_x += 10; 
					stop=1;
				}	
				left=0;
				break;
			default:
				stop=0;
				break;
        }
	}	
	else stop=0;
}
SDL_Rect* Player::spriteRect(){
//	frame=0;
	SpriteRect[0].w=371;
	SpriteRect[0].h=354;
	SpriteRect[0].x=76;
	SpriteRect[0].y=461;
	SpriteRect[1].w=319;
	SpriteRect[1].h=323;
	SpriteRect[1].x=478;
	SpriteRect[1].y=476;
	SpriteRect[2].w=335;
	SpriteRect[2].h=350;
	SpriteRect[2].x=856;
	SpriteRect[2].y=452;
	SpriteRect[3].w=346;
	SpriteRect[3].h=360;
	SpriteRect[3].x=1196;
	SpriteRect[3].y=461;
	SpriteRect[4].w=365;
	SpriteRect[4].h=383;
	SpriteRect[4].x=109;
	SpriteRect[4].y=77;
	frame++;
	if(frame%16==0) frame=0;
	if(stop==1)
		return &SpriteRect[(frame/4)];
	else if(stop==0)
		return &SpriteRect[4];
	
}

