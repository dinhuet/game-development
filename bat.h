#ifndef BAT_H
#define BAT_H
#include "sdlgameobject.h"

class Bat : public SDLGameObject
{
public :
    Bat(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean() ;

private :

};



#endif

