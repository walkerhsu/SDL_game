#include "mainwin.hpp"

MainWin::MainWin(int width, int height):
mWindow(NULL),
mRenderer(NULL),
bgTexture(NULL){
    nWidth  = width;
    nHeight = height;
    nBorder = 0;
    viewWidth  = width - nBorder*2;
    viewHeight = height - nBorder*2;
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
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Create window
        mWindow = SDL_CreateWindow("Main Window",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   nWidth,
                                   nHeight,
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
    while( !quit ) {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            } 
			else if( e.type == SDL_KEYDOWN ) {
                quit = handleKeyEvent(e);
            }
            else if(e.type==SDL_KEYUP){
            	quit=handleKeyEvent(e);
			}
        }
       
        //clear screen as black
        SDL_SetRenderDrawColor( mRenderer, 0x00, 0x00, 0x00, 0xFF );
        SDL_RenderClear( mRenderer );
        drawBGFrame();
        
        //custom rendering
        onRender();
        
        //update screen
        SDL_RenderPresent( mRenderer );
    }
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
            onKeySpace();
            break;
        case SDLK_ESCAPE:
            quit = true;
            break;
        default:
            onKeyEmpty(e);
            break;
    }
    return quit;
}

//override following to define the game behaviors
void MainWin::onRender(){
    printf("override onRender() to custom the rendering\n");
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
void MainWin::onKeyEmpty(SDL_Event e){
	printf("Undefined, need to override onKeyEmpty()\n");
}
void MainWin::onKeySpace(){
    printf("Undefined, need to override onKeySpace()\n");
}
void MainWin::onKeyCustom(SDL_Event e){
    printf("Undefined, need to override onKeyCustom()\n");
}
