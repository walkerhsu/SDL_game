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
	hWin = NULL;
	pTexture = NULL;
}

bool ObjectBase::loadTexture(char path[]) {
    pTexture = hWin->loadTexture(path);
    return pTexture == NULL ? false: true;
}

void ObjectBase::renderTexture(SDL_Rect* dstRect, double angle){
    if (hWin) {
        hWin->renderTexture(pTexture, dstRect, angle);
    }
}

void ObjectBase::render(){
	printf("override render() to custom the rendering\n");
}

