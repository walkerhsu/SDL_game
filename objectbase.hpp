#ifndef objectbase_hpp
#define objectbase_hpp

#include <stdio.h>
#include "mainwin.hpp"

class ObjectBase{
public:
    // constructor
    ObjectBase(MainWin* handle);
    
    // destructor
    ~ObjectBase();

    MainWin* hWin;
    SDL_Texture* pTexture;
    bool flip;
    double angle;
    SDL_Rect dstRect;

    bool loadTexture(char path[]);
    void renderTexture(SDL_Rect* dstRect, double angle);
	virtual void render();
	
};
#endif
