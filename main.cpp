#include "game01.hpp"
#include "SDL2/SDL_mixer.h"
#include"SDL2/SDL_ttf.h"
int main( int argc, char* args[] ) {
    //create game window
    Game01 gm01 = Game01(926,720);
    //load background image
    bool drawBG  = true;
    if (drawBG) {
        char path[] = "data/grayback2.0.jpg";
        if( !gm01.loadBgTexture(path) ) {
            printf("Warning, failed to load background image!\n" );
        }
    }
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	}
	if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_Music *gMusic;
    gMusic=Mix_LoadMUS( "data/startpage.mp3" );
    if(!gMusic) cout<<"false"<<endl;
    Mix_PlayMusic( gMusic, -1 );
    if(Mix_PlayMusic( gMusic, 1 )==-1){
    	cout<<"music error"<<endl;
	}
     
    gm01.mainLoop();
    return 0;
}

