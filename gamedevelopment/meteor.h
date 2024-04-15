#ifndef METEOR_H
#define METEOR_H
#include "sdlgameobject.h"

class Meteor : public SDLGameObject
{
public:
    Meteor(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

};



#endif


