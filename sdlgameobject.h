#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include<SDL.h>
#include<string>
#include "vector2d.h"

#include "loaderparams.h"
#include "texturemanager.h"
class SDLGameObject
{
    public:
    SDLGameObject(const LoaderParams* pParams);
     virtual void load(int x, int y, int width, int height, std::string textureID);
    virtual void draw();
    virtual void drawmonster();
    virtual void update();
    virtual void clean();
    virtual float getpositionX();
    virtual float getpositionY();
    virtual SDL_Rect getcollisionbox();
    virtual void setpositionX(float x);
protected :
    Vector2D m_position;
 Vector2D m_velocity;
Vector2D m_acceleration;


 int m_width;
 int m_height;
 int m_currentRow;
 int m_currentFrame;
 std::string m_textureID;
 SDL_Renderer* pRenderer;
};


#endif // SDLGAMEOBJECT_H
