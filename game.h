
#ifndef GAME_H
#define GAME_H
#include "SDL.h"

#include <iostream>
#include <vector>
#include<string>
#include "khunglong.h"
#include "monster.h"
#include "bat.h"
class Game
{
    public:
        static Game* Instance()
{
 if(s_pInstance == 0)
 {
 s_pInstance = new Game();
 return s_pInstance;
 }
 return s_pInstance;
}

        bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
 void render();
 void update();
 void draw();
 void quit();
 void clean();
 void handleEvents();
 void loadmedia();
 void movebackground();
 SDL_Renderer* getRenderer() const { return m_pRenderer; }
void renderbackground();
void rendernextbackground();
void middlerenderbackground();
void checkcollisionbox(SDLGameObject* monster, SDLGameObject* khunglong);
void restartgame();
    protected:


    private:

    Game();
    static Game* s_pInstance;

        int m_currentFrame;
    std :: vector<SDL_Texture*> vectorTexture;
    std :: vector<std::string> vectorfilename;

        SDLGameObject* m_khunglong = 0;
        SDLGameObject* m_monster = 0;
        SDLGameObject* m_bat;
 SDL_Window* m_pWindow = 0;
SDL_Renderer* m_pRenderer = 0;
int backgroundX ;
int backgroundY;
float backgroundvelocity ;
float backgroundacceleration;
int backgroundwidth;
int backgroundheight;

std::vector<SDLGameObject*> vectormonster;
std::vector<SDLGameObject*> vectorbat;

unsigned int Time;
unsigned int lastMonsterSpawnTime;
unsigned int lastBatSpawnTime ;
unsigned int Time1;

const Uint8* keystates1 = SDL_GetKeyboardState(0);
bool checkcontinue;
};

#endif // GAME_H



