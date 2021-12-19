#include "player.hpp"
Player::Player(MainWin* handle):
ObjectBase(handle){
    
}

// destructor
Player::~Player(){
	
}

void Player::render() {
    dstRect.w = 100;
    dstRect.h = 100;
    dstRect.x = hWin->nBorder + hWin->viewWidth/2  - dstRect.w/2;
    dstRect.y = hWin->nBorder + hWin->viewHeight/2 - dstRect.h/2;
    renderTexture(&dstRect, angle);
}

void Player::setAngle(double playerAngle) {
	angle = playerAngle;
}
