#ifndef ghost_hpp
#define ghost_hpp

#include <stdio.h>
#include "objectbase.hpp"
#include "mainwin.hpp"
class Ghost : public ObjectBase{
public:
    // constructor
    Ghost(MainWin* handle);
    // destructor
    ~Ghost();

    void render();
};
#endif
