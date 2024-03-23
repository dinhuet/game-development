#ifndef KHUNGLONG_H
#define KHUNGLONG_H
#include "sdlgameobject.h"
#include "monster.h"
class Khunglong : public SDLGameObject
{
public :
    Khunglong(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() ;

private :
    const Uint8* keystates = SDL_GetKeyboardState(0);
    bool jumping;

};



#endif
