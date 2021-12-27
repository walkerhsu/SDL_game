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
	SDL_Rect srcRect; 
    bool loadTexture(char path[]);
    void renderTexture(SDL_Rect* dstRect, SDL_Rect* srcRect, double angle);
	virtual void render();
	
};
#endif
