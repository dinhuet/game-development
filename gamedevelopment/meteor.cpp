#include "meteor.h"
#include <iostream>
Meteor::Meteor(const LoaderParams* pParams) : SDLGameObject(pParams) {
    //m_velocity.setX(-4);
}

void Meteor::draw()
{

    SDLGameObject::draw();
}
void Meteor::update()
{

    m_velocity.setX(-2.5);
    m_velocity.setY(2.5);
    SDLGameObject::update();
    m_currentFrame = int(((SDL_GetTicks() / 200) % 4));
}

void Meteor::clean()
{

}





