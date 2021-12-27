#include "game01.hpp"

int main( int argc, char* args[] ) {
    //create game window
    
    Game01 gm01 = Game01(500, 500);
    
    //load background image
    bool drawBG  = true;
    if (drawBG) {
        char path[] = "data/background.jpg";
        if( !gm01.loadBgTexture(path) ) {
            printf("Warning, failed to load background image!\n" );
        }
    }
    
    // start rendering
    gm01.mainLoop();
    return 0;
}
/*bugs :
1:player can't move smoothly
2:player can't move at the lowest level
3:ghost will move in an endless loop
*/
