#ifndef EXIT_H
#define EXIT_H
#include "sdlgameobject.h"

class exitbutton : public SDLGameObject
{
public :
    exitbutton(const LoaderParams* pParams): SDLGameObject(pParams){}
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
