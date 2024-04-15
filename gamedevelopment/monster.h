#ifndef MONSTER_H
#define MONSTER_H
#include "sdlgameobject.h"

class Monster : public SDLGameObject
{
public:
    Monster(const LoaderParams* pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:

};



#endif
