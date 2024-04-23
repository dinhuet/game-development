#include "khunglong.h"
#include <iostream>
#include "game.h"
Khunglong::Khunglong(const LoaderParams* pParams) : SDLGameObject(pParams) {
    jumping = false;
}

void Khunglong::draw()
{
    //SDLGameObject::returnm_currentRow(2);
    SDLGameObject::draw();
}
void Khunglong::update()
{


    if ((keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_SPACE]) && !jumping)
    {
        Game::Instance()->soundeffect("sound/jump_sound.wav", 0);
        std::cout << "up success\n";
        m_velocity.setY(-7);

        m_acceleration.setY(0.35);
        jumping = true;

    }
    if (m_velocity.getY() > 0) // Nếu vận tốc dọc là dương, tức là nhân vật đang rơi xuống
    {
        // Kiểm tra xem nhân vật đã đạt đến độ cao 500 chưa
        if (m_position.getY() >= 500)
        {
            m_velocity.setY(0);
            // Nếu như đã đạt đến độ cao 500, ngừng áp dụng gia tốc dọc
            m_acceleration.setY(0);
            jumping = false;
        }
    }
    if (keystates[SDL_SCANCODE_RIGHT])
    {
        if (m_position.getX() <= 900)
            m_position += {2, 0};

    }
    if (keystates[SDL_SCANCODE_LEFT])
    {
        if (m_position.getX() >= -2)
            m_position += {-2, 0};
    }
    SDLGameObject::update();

}


void Khunglong::clean() {}


