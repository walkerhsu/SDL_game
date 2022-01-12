#include "mainwin.hpp"
#include <iostream>
Result result = NONE;
MainWin::MainWin(int width, int height):
mWindow(NULL),
mRenderer(NULL),
bgTexture(NULL){
    nWidth  = 720;
    nHeight = 720;
    nBorder = 0;
    viewWidth  = width;
    viewHeight = height;
    unitWidth = 0;
    unitHeight = 0;
	init();
}

MainWin::~MainWin() {
    close();
}

bool MainWin::init() {
    //Initialization flag
    bool success = true;
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	}
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    gMusic=Mix_LoadMUS( "data/startpage.mp3" );
    if(!gMusic) cout<<"false"<<endl;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Create window
        mWindow = SDL_CreateWindow("Main Window",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   viewWidth,
                                   viewHeight,
                                   SDL_WINDOW_SHOWN );
        if( mWindow == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Create renderer for window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED );
            if( mRenderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                //Initialize PNG loading
                int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

void MainWin::close() {
    //Free loaded image texture
    SDL_DestroyTexture( bgTexture );
    bgTexture = NULL;
    
    //Destroy renderer & window
    SDL_DestroyRenderer( mRenderer );
    SDL_DestroyWindow( mWindow );
    mWindow = NULL;
    mRenderer = NULL;
    
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}


// texture loader for rendering
SDL_Texture* MainWin::loadTexture(char path[]){
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n",path, IMG_GetError() );
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( mRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    
    return newTexture;
}

bool MainWin::loadBgTexture(char path[]) {
    bgTexture = loadTexture(path);
    return bgTexture == NULL ? false : true ;
}

void MainWin::renderTexture(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip) {
    if (texture != NULL) {
        SDL_RenderCopyEx(mRenderer, texture, srcRect, dstRect, angle, NULL, flip);
        //SDL_RenderCopy(mRenderer,texture,srcRect,dstRect);
    }
}

void MainWin::mainLoop(){
    //Event handler
    bool quit = false;
    SDL_Event e;
    State state = START;
    SDL_Texture** mTexture = new SDL_Texture*[2];
    char path[] = "data/pagestart.png";
    mTexture[0] = loadTexture(path);
    char path1[] = "data/pageend.png";
    mTexture[1] = loadTexture(path1);
    while( !quit ) {
        //Handle events on queue
       switch(state){ 
	    	case START:
				if(Mix_PausedMusic()==1){
					Mix_ResumeMusic();
				}
		    	srcRect = *spriteRect(0);
				renderTexture(mTexture[0], &srcRect, NULL);
				SDL_RenderPresent( mRenderer );
		        SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
			    SDL_RenderClear( mRenderer );
			    
			    
		        while( SDL_PollEvent( &e ) != 0 ) {
		            //User requests quit
		            if( e.type == SDL_QUIT ) {
		                quit = true;
		            }
					else if( e.type == SDL_KEYDOWN ) {
						if(e.key.keysym.sym == SDLK_ESCAPE){
							quit = true;
						}
						else if(e.key.keysym.sym == SDLK_0){
                			state = GAME;
                			loadData(1); 
						}
		                else if(e.key.keysym.sym == SDLK_1){
                			state = GAME;
                			loadData(2); 
						}
						else if(e.key.keysym.sym == SDLK_2){
							state = GAME;
                			loadData(3); 
						}
						else if(e.key.keysym.sym == SDLK_3){
							state = GAME;
                			loadData(4); 
						}
						else if(e.key.keysym.sym == SDLK_4){
							state = GAME;
                			loadData(5); 
						}
		            }
		    	}
				break;
				
	    	case GAME:
	    		if(Mix_PausedMusic()==1){
					Mix_ResumeMusic();
				}
		        //Handle events on queue
		        while( SDL_PollEvent( &e ) != 0 ) {
		            //User requests quit
		            if( e.type == SDL_QUIT ) {
		                quit = true;
		            } 
					else if( e.type == SDL_KEYDOWN ) {
						if(e.key.keysym.sym == SDLK_r) {
							state = START;
						}
		                quit = handleKeyEvent(e);
		            }
		            else if(e.type==SDL_KEYUP){
		            	quit = handleKeyEvent(e);
					}
		        }
		        //clear screen as black
		        SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
			    SDL_RenderClear( mRenderer );
		        if(!quit) {
			        drawBGFrame();
			        quit = onRender();
			        if(quit){
			        	state = END;
			        	quit = false;
					}
			        
			        //update screen
			        SDL_RenderPresent( mRenderer );
				
				}
				break;
			
			case END:
				Mix_PauseMusic();
				if(result==WIN){
					srcRect = *spriteRect(1);
				}
				if(result==LOSE){
					srcRect = *spriteRect(2);
				}
				renderTexture(mTexture[1], &srcRect, NULL);
		        //clear screen as black
				SDL_RenderPresent( mRenderer );
		        SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
			    SDL_RenderClear( mRenderer );
			    
		        while( SDL_PollEvent( &e ) != 0 ) {
		            //User requests quit
		            if( e.type == SDL_QUIT ) {
		                quit = true;
		            }
					else if( e.type == SDL_KEYDOWN ) {
		                if (e.key.keysym.sym == SDLK_SPACE){
                			state = START;
                			result = NONE;
//                			SDL_DestroyTexture(mTexture);
//                			mTexture = NULL;
						}
						else if(e.key.keysym.sym == SDLK_ESCAPE){
							quit = true;
						}
		            }
		    	}
				break;
		} 
		
	}
}
SDL_Rect* MainWin::spriteRect(int i){
	SpriteRect[0].w=640;
	SpriteRect[0].h=526;
	SpriteRect[0].x=0;
	SpriteRect[0].y=0;
	SpriteRect[1].w=561;
	SpriteRect[1].h=250;
	SpriteRect[1].x=0;
	SpriteRect[1].y=20;
	SpriteRect[2].w=561;
	SpriteRect[2].h=250;
	SpriteRect[2].x=0;
	SpriteRect[2].y=270;
	return &SpriteRect[i];
}

void MainWin::drawBGFrame() {
    //set viewport, reserve space as border
    SDL_Rect viewport;
    viewport.x = nBorder;
    viewport.y = nBorder;
    viewport.w = viewWidth;
    viewport.h = viewHeight;
    SDL_RenderSetViewport( mRenderer, &viewport );
    
    //Render background texture
    if (bgTexture != NULL) {
        SDL_RenderCopy( mRenderer, bgTexture, NULL, NULL );
    }
}

bool MainWin::handleKeyEvent(SDL_Event e) {
    bool quit = false;
    //key press
    if(e.type == SDL_KEYDOWN) {
	    switch( e.key.keysym.sym )
	    {
	        case SDLK_UP:
	            onKeyUp(e);
	            break;
	        case SDLK_DOWN:
	            onKeyDown(e);
	            break;
	        case SDLK_LEFT:
	            onKeyLeft(e);
	            break;
	        case SDLK_RIGHT:
	            onKeyRight(e);
	            break;
	        case SDLK_SPACE:
	            onKeySpace(e);
	            break;
	        case SDLK_ESCAPE:
	            quit = true;
	            break;
	        default:
	            break;
	    }
	}
    return quit;
}

//override following to define the game behaviors
bool MainWin::onRender(){
    printf("override onRender() to custom the rendering\n");
    return false;
}
void MainWin::loadData(int) {
	printf("override loadData() to custom the rendering\n");
}
void MainWin::onKeyDown(SDL_Event e) {
    printf("Undefined, need to override onKeyDown()\n");
}
void MainWin::onKeyUp(SDL_Event e){
    printf("Undefined, need to override onKeyUp()\n");
}
void MainWin::onKeyLeft(SDL_Event e){
    printf("Undefined, need to override onKeyLeft()\n");
}
void MainWin::onKeyRight(SDL_Event e){
    printf("Undefined, need to override onKeyRight()\n");
}
void MainWin::onKeySpace(SDL_Event e){
    printf("Undefined, need to override onKeySpace()\n");
}
void MainWin::onKeyCustom(SDL_Event e){
    printf("Undefined, need to override onKeyCustom()\n");
}
