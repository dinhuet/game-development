#include "sdlgameobject.h"
#include "game.h"
#include <iostream>
SDLGameObject :: SDLGameObject(const LoaderParams* pParams) :

    m_position(pParams->getX(), pParams->getY()),
    m_velocity(0,0),
    m_acceleration(0,0)
{

    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1;
    m_currentFrame = 0;
}

void SDLGameObject::draw()
{
 TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY() ,
 m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}
void SDLGameObject::drawmonster()
{
    TextureManager::Instance()->draw(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, Game::Instance()->getRenderer());
}
void SDLGameObject :: update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
    m_position += m_velocity ;

    m_velocity += m_acceleration;
}

void SDLGameObject::clean()
{
    Game::Instance()->clean();
}

void SDLGameObject::load(int x, int y, int width, int height, std::string m_textureID)
{
    //TextureManager::Instance()->load(std::string filename, m_textureID, pRenderer);
}
float SDLGameObject::getpositionX()
{
    return m_position.getX();
}
float SDLGameObject::getpositionY()
{
    return m_position.getY();
}

SDL_Rect SDLGameObject::getcollisionbox()
{
    SDL_Rect rect;
    rect.x = m_position.getX() + 6;
    rect.y = m_position.getY() + 20;
    rect.h = m_height - 5;
    rect.w = m_width - 30;
    return rect;
}

void SDLGameObject::setpositionX(float x)
{
    m_position.setX(x);
}
