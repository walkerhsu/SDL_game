#ifndef mainwin_hpp
#define mainwin_hpp
//Using SDL and standard IO
#include "SDL2/SDL.h" 
#include "SDL2/SDL_image.h"
#include <stdio.h>

//window dimension constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

class MainWin {
public:
    SDL_Window*     mWindow;    //the window we'll be rendering to
    SDL_Renderer*   mRenderer;  //the window renderer
    
    int nWidth;
    int nHeight;
    int nBorder;                //border, can be zero
    int viewWidth;              //window width  - 2 * border width
    int viewHeight;             //window height - 2 * border height

    // constructor
    MainWin(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);
    
    // destructor
    virtual ~MainWin();

    SDL_Texture* loadTexture(char path[]);
    void mainLoop();

    bool loadBgTexture(char path[]);
    void renderTexture(SDL_Texture* texture, SDL_Rect* dstrect=NULL, float angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE);
  
protected:
    //override following to define the game behavior
    virtual void onRender();
    virtual void onKeyDown();
    virtual void onKeyUp();
    virtual void onKeyLeft();
    virtual void onKeyRight();
    virtual void onKeySpace();
    virtual void onKeyCustom(SDL_Event e);

private:
    SDL_Texture*    bgTexture = NULL;   //background displayed texture
    
private:
    bool init();
    void close();
    
    bool handleKeyEvent(SDL_Event e);
    void drawBGFrame();
};

#endif
