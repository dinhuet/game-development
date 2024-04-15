#include "monster.h"
#include <iostream>
Monster::Monster(const LoaderParams* pParams) : SDLGameObject(pParams) {
    m_velocity.setX(-3);
}

void Monster::draw()
{

    SDLGameObject::drawmonster();
}
void Monster::update()
{

    //m_acceleration.setX(-0.0001);
    SDLGameObject::update();
}

void Monster::clean()
{

}




