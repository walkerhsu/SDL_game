#include "player.hpp"
#include"SDL2/SDL.h"
#include<iostream>
#include"SDL2/SDL_mixer.h"
#include"SDL2/SDL_ttf.h"
using namespace std;
Player::Player(MainWin* handle, int startX , int startY , MazeMap* m):
ObjectBase(handle),
MapMaze(m){
    pos_x=startX * hWin->unitWidth;
	pos_y=startY * hWin->unitHeight;
	v_x=0,v_y=0;
	frame=0;
	stop=0;
	left=0;
	player_vx=0,player_vy=0,player_v=hWin->nHeight/150;
	direction = '\0';
	power = false,protect=false,trapUse=false;
	attframe=-1;
	att=0;
	fast=1;
	slow=1;
	trap=1;
	point=1;
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	}
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    win=Mix_LoadWAV("data/winsound.wav");
	
}	

// destructor
Player::~Player(){
	mazeMap.clear();
	delete win;
	delete MapMaze;
	MapMaze = NULL;
}

bool Player::checkWin(){
	int item = bumpintoWhat();
	if(point>=1000 && item==37){
		Mix_PlayChannel( -1, win, 0 );
		return true;
	} 
	else return false;
}

void Player::render() {
	renderFont(point);
    dstRect.w = hWin->unitWidth/1.5;
    dstRect.h = hWin->unitHeight/1.5;
    dstRect.x = pos_x;
    dstRect.y = pos_y;
    move();
    /*if(stop==1){
    	Mix_PlayChannel( -1, step, 0 );
    	if(Mix_PlayChannel( -1, step, 0 )==-1){
    		cout<<"step sound error"<<endl;
		}
	}*/
    //printf("player : %d , %d\n" , pos_x,pos_y);
    srcRect=*spriteRect();
    if(left==1) flip=true;
    renderTexture(&dstRect, &srcRect, angle);
    
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
		if(y-player_v>0&&mazeMap[(y-player_v)/(hWin->unitHeight)][x/(hWin->unitWidth)]!=0&&mazeMap[(y-player_v)/(hWin->unitHeight)][(x+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='d'){
		if(y+player_v+dstRect.h<(hWin->nHeight-5)&&mazeMap[(y+dstRect.h+player_v)/(hWin->unitHeight)][(x+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h+player_v)/(hWin->unitHeight)][x/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='l'){
		if(x-player_v>0&&mazeMap[y/(hWin->unitHeight)][(x-player_v)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h)/(hWin->unitHeight)][(x-player_v)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='r'){
		if(x+player_v+dstRect.w<(hWin->nWidth)&&mazeMap[(y+dstRect.h)/(hWin->unitHeight)][(x+player_v+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[y/(hWin->unitHeight)][(x+player_v+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	return false;
	/*if(c=='u'){
		if(y-player_v>0&&mazeMap[(y-player_v+1)/(hWin->unitHeight)][(x+x+dstRect.w-1)/2/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='d'){
		if(y+player_v+dstRect.h<(hWin->nHeight)&&mazeMap[(y+dstRect.h+player_v-1)/(hWin->unitHeight)][(x+x+dstRect.w-1)/2/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='l'){
		if(x-player_v>0&&mazeMap[(y+y+dstRect.y-1)/2/(hWin->unitHeight)][(x-player_v+1)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='r'){
		if(x+player_v+dstRect.w<(hWin->nWidth)&&mazeMap[(y+y+dstRect.h-1)/2/(hWin->unitHeight)][(x+player_v+dstRect.w-1)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	return false;*/
}
int Player::bumpintoWhat(){
	/*if(mazeMap[pos_y/hWin->unitWidth][pos_x/hWin->unitWidth]!=0&&mazeMap[pos_y/hWin->unitWidth][pos_x/hWin->unitWidth]!=1) 
		return mazeMap[pos_y/hWin->unitWidth][pos_x/hWin->unitWidth];
	if(mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][pos_x/hWin->unitWidth]!=0&&mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][pos_x/hWin->unitWidth]!=1)
		return mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][pos_x/hWin->unitWidth];
	if(mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth]!=0&&mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth]!=1)
		return mazeMap[(pos_y+dstRect.h)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth];
	if(mazeMap[(pos_y)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth]!=0&&mazeMap[(pos_y)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth]!=1)
		return mazeMap[(pos_y)/hWin->unitWidth][(pos_x+dstRect.w)/hWin->unitWidth];*/
	return mazeMap[pos_y/hWin->unitWidth][pos_x/hWin->unitHeight];
}
int Player::getW(){
	return dstRect.w;
}
int Player::getH(){
	return dstRect.h;
}
void Player::handleEvent(SDL_Event &e){
	const Uint8* keystate=SDL_GetKeyboardState(NULL);
	bool u=false,d=false,l=false,r=false;
	if(e.type==SDL_KEYDOWN){
		switch( e.key.keysym.sym ){
            case SDLK_UP:
            	if(checkcollide(pos_x,pos_y,'u')) {
            		u=true;
            		d=false,r=false,l=false;
            		//pos_y -= 10; 
            		player_vy=-player_v;
            		player_vx=0;
					stop=1;
				}
				direction = 'u';
				break;
        	case SDLK_DOWN: 
           		if(checkcollide(pos_x,pos_y,'d')) {
           			//pos_y += 10;
           			player_vy=player_v;
           			player_vx=0;
					stop=1;
					d=true;
					u=false,r=false,l=false;
				}
				direction = 'd';
				break;
            case SDLK_LEFT: 
            	if(checkcollide(pos_x,pos_y,'l')) {
            		l=true;
            		d=false,r=false,u=false;
            		//pos_x -= 10;
            		player_vx=-player_v;
            		player_vy=0;
					stop=1;
				}
				direction = 'l';
				left=1;
				break;
            case SDLK_RIGHT:
			 	if(checkcollide(pos_x,pos_y,'r')){
			 		r=true;
			 		d=false,u=false,l=false;
					//pos_x += 10; 
					player_vx=player_v;
					player_vy=0;
					stop=1;
				}	
				direction = 'r';
				left=0;
				break;
			case SDLK_SPACE:
				att=1;
				break;
			default:
				stop=0;
				break;
        }
	}
	if(keystate[SDL_SCANCODE_SPACE]){
		if(power==true) att=1;
	
	}	
	
	if(player_vx==0&&player_vy==0) stop=0;
	
	/*if(keystate[SDL_SCANCODE_UP]){
		if(checkcollide(pos_x,pos_y,'u')) {
			u=true;
           	pos_y -= 10; 
			stop=1;
		}
		left=0;
	}	
	else if(keystate[SDL_SCANCODE_DOWN]){
		if(checkcollide(pos_x,pos_y,'d')) {
			d=true;
           	pos_y += 10;
			stop=1;
		}
		left=0;
	}
	else if(keystate[SDL_SCANCODE_LEFT]){
		if(checkcollide(pos_x,pos_y,'l')) {
			l=true;
            pos_x -= 10;
			stop=1;
		}
		left=1;
	}	
	else if(keystate[SDL_SCANCODE_RIGHT]){
		if(checkcollide(pos_x,pos_y,'r')){
			r=true;
			pos_x += 10; 
			stop=1;
		}	
		left=0;
	}
	else stop=0;*/
}
void Player::move(){
	int item = bumpintoWhat();
	if(player_vx<0&&!checkcollide(pos_x,pos_y,'l')) player_vx=0;
	if(player_vx>0&&!checkcollide(pos_x,pos_y,'r')) player_vx=0;
	if(player_vy<0&&!checkcollide(pos_x,pos_y,'u')) player_vy=0;
	if(player_vy>0&&!checkcollide(pos_x,pos_y,'d')) player_vy=0;
	if(player_vx==0&&player_vy==0) stop=0;
	int row = pos_y/hWin->unitWidth;
	int col = pos_x/hWin->unitHeight;
	if(item==4){
		fast=1.5;
		MapMaze->changeMap(row , col);
		mazeMap[row][col]=1;
	}
	if(fast!=1){
		fastcnt++;
		if(fastcnt>=75){
			fast=1;
			fastcnt=0;
		}
	}
	if(item==5){
		slow=0.3;
		//MapMaze->changeMap(row , col);
		//mazeMap[row][col]=1;
	}
	if(slow!=1){
		slowcnt++;
		if(slowcnt>=75){
			slow=1;
			slowcnt=0;
		}
	}
	if(item==6){
		power=true;
		cout<<"power"<<endl;
		MapMaze->changeMap(row , col);
		mazeMap[row][col]=1;
		
	}
	if(item==7&&protect==false){
		trap=0;
		trapUse=true;
		stop=0;
		MapMaze->changeMap(row , col);
		mazeMap[row][col]=1;
	}
	if(item==7&&protect==true){
		MapMaze->changeMap(row , col);
		mazeMap[row][col]=1;
		//trapcnt++;
		//if(trapcnt>=13){
		//	protect=false;
		//	trapcnt=0;
		//}
	}
	if(trapUse||trap==0){
		trapcnt++;
		if(trapcnt>=100){
			trap=1;
			trapcnt=0;
			trapUse=false;
			stop=1;
		}
	}
	if(item==8){
		protect=true;
		cout<<"protect"<<endl;
		MapMaze->changeMap(row , col);
		mazeMap[row][col]=1;
		
	}
	if(item>=9 && item<=36){
		if(item==36 && point<0) {;} 
		else {
			changePoint(item);
			MapMaze->changeMap(row , col);
			mazeMap[row][col]=1;
			cout<<"point = "<<point<<endl;
		}
	}
	
	/*if(player_vx*fast*slow*trap!=0||player_vy*fast*slow*trap!=0){
		Mix_PlayChannel( -1, step, 0 );
	}*/
	pos_x+=player_vx*fast*slow*trap;
	pos_y+=player_vy*fast*slow*trap; 
	
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
	SpriteRect1[0].x=1838;
	SpriteRect1[0].y=90;
	SpriteRect1[0].w=302;
	SpriteRect1[0].h=310;
	SpriteRect1[1].x=1838;
	SpriteRect1[1].y=90;
	SpriteRect1[1].w=302;
	SpriteRect1[1].h=310;
	SpriteRect1[2].x=1838;
	SpriteRect1[2].y=90;
	SpriteRect1[2].w=302;
	SpriteRect1[2].h=310;
	SpriteRect1[3].x=1838;
	SpriteRect1[3].y=90;
	SpriteRect1[3].w=302;
	SpriteRect1[3].h=310;
	frame++;
	if(frame%16==0) frame=0;
	if(att==1){
		attframe++;
		if(attframe<=15)
			return &SpriteRect1[(attframe/4)] ;
		else{
			attframe=-1;
			att=0;
		}
	}
	if(stop==1)
		return &SpriteRect[(frame/4)];
	else if(stop==0)
		return &SpriteRect[4];
	
	
}
bool Player::checkIfPower() {
	return power;
}
void Player::resetPower(){
	power=false;
}

void Player::changePoint(int item){
	// +5 , +10 , +20 , +35 , +50 , +70 , +85 , +100
	// -5 , -10 , -20 , -35 , -50 , -70 , -85 , -100
	// *2 , *3 , *5 , *10
	// /2 , /3 , /5 , /10
	// *-1 , abs , ^2 , sqrt
	switch(item) {
		case 9:
			point+=5;
			break;
		case 10:
			point+=10;
			break;
		case 11:
			point+=20;
			break;
		case 12:
			point+=35;
			break;
		case 13:
			point+=50;
			break;
		case 14:
			point+=70;
			break;
		case 15:
			point+=85;
			break;
		case 16:
			point+=100;
			break;
		case 17:
			point-=5;
			break;
		case 18:
			point-=10;
			break;
		case 19:
			point-=20;
			break;
		case 20:
			point-=35;
			break;
		case 21:
			point-=50;
			break;
		case 22:
			point-=70;
			break;
		case 23:
			point-=85;
			break;
		case 24:
			point-=100;
			break;
		case 25:
			point*=2;
			break;
		case 26:
			point*=3;
			break;
		case 27:
			point*=5;
			break;
		case 28:
			point*=10;
			break;
		case 29:
			point/=2;
			break;
		case 30:
			point/=3;
			break;
		case 31:
			point/=5;
			break;
		case 32:
			point/=10;
			break;
		case 33:
			point*=-1;
			break;
		case 34:
			point=(point>0)?point:point*(-1);
			break;
		case 35:
			point*=point;
			break;
		case 36:
			if(point>=0)point=sqrt(point);
			break;
	}	
}
void Player::initMus(){
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	}
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	Mix_Chunk *pointup=Mix_LoadWAV("data/pointsound.wav");
	cout<<"point up loaded"<<endl;
	if(pointup==NULL){
		cout<<"pointup load error"<<endl;
	}
    return ;
}
bool Player::getPower(){
	return power;
}
bool Player::getProtect(){
	return protect;
}
void Player::renderFont(int point) {
	TTF_Font* Sans = TTF_OpenFont("data/xttf/xtff.ttf", 12);
	if(!Sans) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	   // handle error
	}
	string str = "pt : ";
	stringstream ss;
	ss << point;
	str += ss.str();
	
	SDL_Color Black = {255, 255, 255};
	
	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first

	SDL_Surface* surfaceMessage =
	    TTF_RenderText_Solid(Sans , str.c_str() , Black);
	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(hWin->mRenderer, surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 750;  //controls the rect's x coordinate 
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = 120; // controls the width of the rect
	Message_rect.h = 60; // controls the height of the rect
	

	SDL_RenderCopy(hWin->mRenderer, Message, NULL, &Message_rect);
	//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
