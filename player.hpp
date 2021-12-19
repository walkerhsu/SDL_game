#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "mainwin.hpp"
#include "objectbase.hpp" 

class Player: public ObjectBase {
public:
    // constructor
    Player(MainWin* handle);
    
    // destructor
    ~Player();
    
    void render();
    void setAngle(double playerAngle);
};
#endif
