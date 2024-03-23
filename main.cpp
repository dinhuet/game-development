#include <SDL.h>
#include "game.h"
#include <bits/stdc++.h>
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const Uint8* keystates = SDL_GetKeyboardState(0);
int main(int agrc, char* agrv[])
{   srand(time(0));
    Uint32 frameStart, frameTime;
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        if(!Game::Instance()->init("Dinosaur game",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0))
        {
            std::cout << "fail to init\n";
            return 1;
        }
        Game::Instance()->loadmedia();
        SDL_Event  event;
        bool out = false;
        while(!out)
        {
            while(SDL_PollEvent(&event) != 0)
            {
                if(event.type == SDL_QUIT)
                {
                    out = true;
                }
            }
            frameStart = SDL_GetTicks();
            Game::Instance()->update();
            Game::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;
            if(frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }

        }
        Game::Instance()->clean();
        Game::Instance()->quit();
    }
    return 0;
}
