#include <SDL.h>
#include "game.h"
#include <iostream>
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
const Uint8* keystates = SDL_GetKeyboardState(0);
int menu = 1;

int main(int agrc, char* agrv[])
{
    bool continuegame = true;
    bool playing = true;
    bool out = false;
    srand(time(0));
    Uint32 frameStart, frameTime;
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {

        if (!Game::Instance()->init("Dinosaur game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0))
        {
            std::cout << "fail to init\n";
            return 1;
        }

        Game::Instance()->loadmenu();
        Game::Instance()->loadmedia();

        SDL_Event event;

        while (continuegame == true)
        {
            if (menu == 1)
            {
                Game::Instance()->stopallsoundeffect();
                Game::Instance()->soundeffect("menu_audio.wav", -1);
            }
            while (menu == 1)
            {

                while (SDL_PollEvent(&event)) {

                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;

                    if (mouseX > 420 && mouseX < 580 && mouseY > 210 && mouseY < 330)
                    {

                        Game::Instance()->rendermenubutton0();
                        if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            menu = 0;
                            out = false;
                            playing = true;

                            Game::Instance()->stopallsoundeffect();
                            Game::Instance()->soundeffect("mouse_click.wav", 0);
                        }
                    }
                    else if (mouseX > 420 && mouseX < 580 && mouseY > 340 && mouseY < 460)
                    {
                        Game::Instance()->rendermenubutton1();
                        if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            Game::Instance()->soundeffect("mouse_click.wav", 0);
                            bool back = false;
                            while (!back)
                            {
                                while (SDL_PollEvent(&event))
                                {
                                    mouseX = event.motion.x;
                                    mouseY = event.motion.y;

                                    if (mouseX > 30 && mouseX < 140 && mouseY > 30 && mouseY < 120)
                                    {
                                        std::cout << 1;
                                        Game::Instance()->rendermenubutton4();
                                        if (event.type == SDL_MOUSEBUTTONDOWN)
                                        {
                                            Game::Instance()->soundeffect("mouse_click.wav", 0);
                                            back = true;
                                        }
                                    }
                                    else
                                    {
                                        Game::Instance()->rendermenubutton3();
                                    }
                                }
                            }
                        }
                    }

                    else if (mouseX > 420 && mouseX < 580 && mouseY > 470 && mouseY < 590)
                    {
                        Game::Instance()->rendermenubutton2();
                        if (event.type == SDL_MOUSEBUTTONDOWN)
                        {
                            Game::Instance()->soundeffect("mouse_click.wav", 0);
                            SDL_Delay(500);
                            Game::Instance()->clean();
                            Game::Instance()->quit();
                        }
                    }
                    else
                    {
                        Game::Instance()->rendermenu();
                    }
                }
            }
            Game::Instance()->soundeffect("bkgr_audio.wav", -1);

            Game::Instance()->loadtoplay(3);
            Game::Instance()->loadtoplay(2);
            Game::Instance()->loadtoplay(1);

            while (!out)
            {
                frameStart = SDL_GetTicks();
                SDL_Event  event;
                while (SDL_PollEvent(&event) != 0)
                {
                    if (event.type == SDL_QUIT)
                    {
                        out = true;
                        continuegame = false; // Thoát khỏi vòng lặp chính
                    }
                    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        menu = 1;
                        playing = false;
                        out = true;
                    }
                }
                if (playing)
                {
                    Game::Instance()->update();
                    Game::Instance()->render();
                }
                frameTime = SDL_GetTicks() - frameStart;
                if (frameTime < DELAY_TIME)
                {
                    SDL_Delay((int)(DELAY_TIME - frameTime));
                }

            }
            if (continuegame == false)
            {
                Game::Instance()->clean();
                Game::Instance()->quit();
            }
        }

    }
    return 0;
}
