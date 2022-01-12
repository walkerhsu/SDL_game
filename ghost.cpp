#include "ghost.hpp"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <iostream>
using namespace std;
Ghost::Ghost(MainWin* handle , int startX , int startY):
ObjectBase(handle){
    //Todo
    pos_x=startX*hWin->unitWidth;
	pos_y=startY*hWin->unitHeight;
    frame=0;
    left=0;
    ghost_v=2;
    u=false,d=false,l=true,r=false;
    //seed=srand(time(0));
   // moverandom=rand();
}

// destructor
Ghost::~Ghost(){
    //Todo
}
void Ghost::getmazeMap(vector< vector<int> > map){
	mazeMap=map;
}
void Ghost::getplayerPos(int x,int y){
	player_x=x;
	player_y=y;
} 
int Ghost::getW(){
	return dstRect.w;
}
int Ghost::getH(){
	return dstRect.h;
}
bool Ghost::checkcollide(int x,int y,char c){
	if(c=='u'){
		if(y-ghost_v>0&&mazeMap[(y-ghost_v)/(hWin->unitHeight)][(x+2)/(hWin->unitWidth)]!=0&&mazeMap[(y-ghost_v)/(hWin->unitHeight)][(x+dstRect.w-2)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='d'){
		if(y+ghost_v+dstRect.h<(hWin->nHeight)&&mazeMap[(y+dstRect.h+ghost_v)/(hWin->unitHeight)][(x+dstRect.w-5)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h+ghost_v)/(hWin->unitHeight)][(x+5)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='l'){
		if(x-ghost_v>0&&mazeMap[(y+2)/(hWin->unitHeight)][(x-ghost_v+1)/(hWin->unitWidth)]!=0&&mazeMap[(y+dstRect.h-2)/(hWin->unitHeight)][(x-ghost_v)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	if(c=='r'){
		if(x+ghost_v+dstRect.w<(hWin->nWidth)&&mazeMap[(y+dstRect.h-2)/(hWin->unitHeight)][(x+ghost_v+dstRect.w)/(hWin->unitWidth)]!=0&&mazeMap[(y+2)/(hWin->unitHeight)][(x+ghost_v+dstRect.w)/(hWin->unitWidth)]!=0){
			return true;
		}
	}
	return false;
}

void Ghost::handleEvent(int x,int y){
	bool move=false;
	int ran=rand();
	char c;
	if(ran%2==0){
		c='u';
	}
	else c='d';
	if(l==true){
		if(checkcollide(pos_x,pos_y,'l')){
			pos_x-=2;
			u=false;
			d=false;
			r=false;
			left=1;
		}
		else{
			if(c=='u'){
				if(checkcollide(pos_x,pos_y,'u')){
					pos_y-=2;
					u=true;
					d=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'r')){
					pos_x+=2;
					r=true;
					l=false;
					u=false;
					d=false;
					left=0;
				}
			}
			else if(c=='d'){
				if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'u')){
					pos_y-=2;
					u=true;
					d=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'r')){
					pos_x+=2;
					r=true;
					l=false;
					u=false;
					d=false;
					left=0;
				}
			}
		}
	}
	else if(r==true){
		if(checkcollide(pos_x,pos_y,'r')){
			pos_x+=2;
			u=false;
			d=false;
			l=false;
			left=0;
		}
		else{
			if(c=='u'){
				if(checkcollide(pos_x,pos_y,'u')){
					pos_y-=2;
					u=true;
					d=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'l')){
					pos_x-=2;
					l=true;
					r=false;
					u=false;
					d=false;
					left=1;
				}
			}
			else if(c=='d'){
				if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'u')){
					pos_y-=2;
					u=true;
					d=false;
					r=false;
					l=false;
				}
				else if(checkcollide(pos_x,pos_y,'l')){
					pos_x-=2;
					l=true;
					r=false;
					u=false;
					d=false;
					left=1;
				}
			}
		}
	}	
	if(ran%2==0) c='l';	
	else c='r';
	
	if((u==true)){
		if(checkcollide(pos_x,pos_y,'u')){
			pos_y-=2;
			l=false;
			d=false;
			r=false;
		}
		else {
			if(c=='r') {
				if(checkcollide(pos_x,pos_y,'r')){
					pos_x+=2;
					r=true;
					u=false;
					d=false;
					l=false;
					left=0;
				}
				else if(checkcollide(pos_x,pos_y,'l')){
					pos_x-=2;
					l=true;
					u=false;
					d=false;
					r=false;
					left=1;
				} 
				else if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
			}
			else if(c=='l') {
				if(checkcollide(pos_x,pos_y,'l')){
					pos_x-=2;
					r=false;
					u=false;
					d=false;
					l=true;
					left=1;
				}
				else if(checkcollide(pos_x,pos_y,'r')){
					pos_x+=2;
					r=true;
					u=false;
					d=false;
					l=false;
					left=0;
				} 
				else if(checkcollide(pos_x,pos_y,'d')){
					pos_y+=2;
					d=true;
					u=false;
					r=false;
					l=false;
				}
			}
		}
		
	}
	else if((d==true)){
		if(checkcollide(pos_x,pos_y,'d')){
			pos_y+=2;
			u=false;
			l=false;
			r=false;
		}
		else if(c=='r') {
			if(checkcollide(pos_x,pos_y,'r')){
				pos_x+=2;
				r=true;
				u=false;
				d=false;
				l=false;
				left=0;
			}
			else if(checkcollide(pos_x,pos_y,'l')){
					pos_x-=2;
					l=true;
					u=false;
					d=false;
					r=false;
					left=1;
			} 
			else if(checkcollide(pos_x,pos_y,'u')){
				pos_y-=2;
				u=true;
				d=false;
				r=false;
				l=false;
			}
		}
		else if(c=='l') {
			if(checkcollide(pos_x,pos_y,'l')){
				pos_x-=2;
				r=false;
				u=false;
				d=false;
				l=true;
				left=1;
			}
			else if(checkcollide(pos_x,pos_y,'r')){
				pos_x+=2;
				l=true;
				u=false;
				d=false;
				r=false;
				left=1;
			} 
			else if(checkcollide(pos_x,pos_y,'u')){
				pos_y-=2;
				u=true;
				d=false;
				r=false;
				l=false;
			}
		}
	}
}
void Ghost::render() {
	//Todo
	
    dstRect.w = hWin->unitWidth-1;
    dstRect.h = hWin->unitHeight-1;
    dstRect.x = pos_x;
    dstRect.y = pos_y;
    //printf("ghost : %d , %d\n" , pos_x,pos_y);
    srcRect=*SpriteRect();
    renderTexture(&dstRect, &srcRect, angle);
    
}
SDL_Rect* Ghost::SpriteRect(){
	spriteRect[0].w=142;
	spriteRect[0].h=181;
	spriteRect[0].x=37;
	spriteRect[0].y=9;
	spriteRect1[0].w=144;
	spriteRect1[0].h=181;
	spriteRect1[0].x=252;
	spriteRect1[0].y=9;
	if(left==0) 
		return &spriteRect[0];
	else 
		return &spriteRect1[0];
}

