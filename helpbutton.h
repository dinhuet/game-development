#ifndef HELP_H
#define HELP_H
#include "sdlgameobject.h"

class helpbutton : public SDLGameObject
{
public :
   helpbutton(const LoaderParams* pParams): SDLGameObject(pParams){}
    virtual void draw()
    {
        SDLGameObject::draw();
    }
    virtual void update()
    {
        SDLGameObject::update();
    }

private :

};



#endif
