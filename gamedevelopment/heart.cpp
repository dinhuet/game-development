#include "heart.h"
#include <iostream>
Heart::Heart(const LoaderParams* pParams) : SDLGameObject(pParams) {
    m_velocity.setX(-3);
}

void Heart::draw()
{

    SDLGameObject::drawmonster();
}
void Heart::update()
{

    //m_acceleration.setX(-0.0001);
    SDLGameObject::update();
}

void Heart::clean()
{

}



