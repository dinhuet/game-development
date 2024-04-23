
#ifndef GAME_H
#define GAME_H
#include "SDL.h"

#include <iostream>
#include <vector>
#include<string>
#include <SDL_mixer.h>
#include "khunglong.h"
#include "monster.h"
#include "bat.h"
#include "meteor.h"
#include "heart.h"
class Game
{
public:
    static Game* Instance()
    {
        if (s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void renderforText();
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
    void checkcollisionboxmeteor(SDLGameObject* monster, SDLGameObject* khunglong);
    void restartgame();
    void loadmenu();
    void rendermenu();
    void rendermenubutton1();
    void rendermenubutton2();
    void rendermenubutton0();
    void rendermenubutton3();
    void rendermenubutton4();
    void drawtext();
    void loadtoplay(int n);
    void soundeffect(std::string s, int n);
    void stopallsoundeffect();
protected:


private:

    Game();
    static Game* s_pInstance;

    int m_currentFrame;
    std::vector<SDL_Texture*> vectorTexture;
    std::vector<SDL_Texture*> vectorTextureMenu;
    std::vector<SDL_Texture*> vectorTextureText;
    SDL_Texture* pmenu;

    std::vector<std::string> vectorfilename;
    std::vector<std::string> vectormenu;
    SDLGameObject* m_khunglong = 0;
    SDLGameObject* m_meteor = 0;
    SDLGameObject* m_monster = 0;
    SDLGameObject* m_bat;
    SDLGameObject* m_heart = 0;
    SDLGameObject* scoreheart = 0;

    std::vector<SDLGameObject*> vectormonster;
    std::vector<SDLGameObject*> vectorbat;
    std::vector<SDLGameObject*> vectormeteor;
    std::vector<SDLGameObject*> vectorheart;

    SDL_Window* m_pWindow = 0;
    SDL_Renderer* m_pRenderer = 0;
    SDL_Renderer* textRenderer = 0;
    int backgroundX;
    int backgroundY;
    float backgroundvelocity;
    float backgroundacceleration;
    int backgroundwidth;
    int backgroundheight;

    unsigned int currentTime = SDL_GetTicks();
    unsigned int Time;
    unsigned int lastMonsterSpawnTime;
    unsigned int lastBatSpawnTime;
    unsigned int Time1;
    unsigned int Timemeteor;
    unsigned int lastMeteorSpawnTime;
    unsigned int lastheartTime = 0;
    unsigned int Point;
    unsigned int checkPoint;
    unsigned int highscore;
    int statekhunglong = 0;
    int countheart = 3;
    const Uint8* keystates1 = SDL_GetKeyboardState(0);
    bool checkcontinue;
    bool checkheart = true; 
};

#endif // GAME_H



