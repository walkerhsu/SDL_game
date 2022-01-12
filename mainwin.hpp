#ifndef mainwin_hpp
#define mainwin_hpp
//Using SDL and standard IO
#include "SDL2/SDL.h" 
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <string>
using namespace std;
enum Result{
	NONE,
	WIN,
	LOSE
};

enum State{
	START,
	GAME,
	END
};

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
	int unitWidth;
	int unitHeight;
    // constructor
    MainWin(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);
    Mix_Music *gMusic;
    // destructor
    ~MainWin();

//    void loadTexture(string textureText, SDL_Color textColor);
	SDL_Texture* loadTexture(char path[]);
    void mainLoop();

    bool loadBgTexture(char path[]);
    void renderTexture(SDL_Texture* texture, SDL_Rect* srcRect=NULL, SDL_Rect* dstrect=NULL, float angle=0, SDL_RendererFlip flip=SDL_FLIP_NONE);
  	Mix_Music* backmus; 
protected:
    //override following to define the game behavior
    virtual void loadData(int);
    virtual bool onRender();
    virtual void onKeyDown(SDL_Event);
    virtual void onKeyUp(SDL_Event);
    virtual void onKeyLeft(SDL_Event);
    virtual void onKeyRight(SDL_Event);
    virtual void onKeySpace(SDL_Event);
    virtual void onKeyCustom(SDL_Event);
    
private:
    SDL_Texture* bgTexture = NULL;   //background displayed texture

    bool init();
    void close();
    
    bool handleKeyEvent(SDL_Event e);
    void drawBGFrame();
    
    SDL_Rect srcRect;
	SDL_Rect* spriteRect(int i);
	SDL_Rect SpriteRect[2];
};

#endif
