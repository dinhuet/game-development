#ifndef HEART_H
#define HEART_H
#include "sdlgameobject.h"

class   Heart : public SDLGameObject
{
public:
    Heart(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

};



#endif
