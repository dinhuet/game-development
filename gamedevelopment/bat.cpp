#include "bat.h"
#include <iostream>
Bat::Bat(const LoaderParams* pParams) : SDLGameObject(pParams) {
    m_velocity.setX(-4);
}

void Bat::draw()
{

    SDLGameObject::draw();
}
void Bat::update()
{

    m_acceleration.setX(-0.05);
    m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
    SDLGameObject::update();
}

void Bat::clean()
{

}





