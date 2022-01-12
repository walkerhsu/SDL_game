#include "objectbase.hpp"

ObjectBase::ObjectBase(MainWin* handle):
hWin(handle){
    flip=false;
    angle=0.f;
    dstRect.x=0;
    dstRect.y=0;
    dstRect.h=0;
    dstRect.w=0;
}

ObjectBase::~ObjectBase(){
	delete hWin;
	delete pTexture;
}

bool ObjectBase::loadTexture(char path[]) {
    pTexture = hWin->loadTexture(path);
    return pTexture == NULL ? false: true;
}

void ObjectBase::renderTexture(SDL_Rect* dstRect, SDL_Rect* srcRect, double angle){
    if (hWin) {
    	if(flip) hWin->renderTexture(pTexture, srcRect, dstRect, angle, SDL_FLIP_HORIZONTAL);
        else hWin->renderTexture(pTexture, srcRect, dstRect, angle, SDL_FLIP_NONE);
        flip=false;
    }
}

void ObjectBase::render(){
	printf("override render() to custom the rendering\n");
}

