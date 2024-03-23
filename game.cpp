#include "game.h"
#include "SDL_image.h"
Game* Game::s_pInstance = 0;

Game::Game() {
    backgroundX = 0;
    backgroundY = 0;
    backgroundvelocity = -3;
    backgroundwidth = 1000;
    backgroundheight = 600;
    lastMonsterSpawnTime = 0;
    lastBatSpawnTime = 0;
    Time = 0;
    Time1 = 0;
    checkcontinue = true;
}

void Game::loadmedia()
{
    vectorfilename.push_back("layer01.png");
    vectorfilename.push_back("layer02.png");
    vectorfilename.push_back("layer03.png");
    vectorfilename.push_back("layer04.png");
    vectorfilename.push_back("layer05.png");
    vectorfilename.push_back("layer06.png");
    vectorfilename.push_back("layer07.png");
    vectorfilename.push_back("layer08.png");
    vectorfilename.push_back("layer09.png");
    vectorfilename.push_back("layer11.png");
    for(int i = 0; i < vectorfilename.size(); i++)
    {
        SDL_Surface* pSurFace = IMG_Load(vectorfilename[i].c_str());
        if(pSurFace == 0)
    {
        std :: cout << "fail to load background\n";
        return ;
    }
    SDL_Texture* gBackground = SDL_CreateTextureFromSurface(m_pRenderer, pSurFace);
    if(gBackground == 0)
    {
        std :: cout <<"fail to create texture\n";
        SDL_FreeSurface(pSurFace);
        return ;
    }
    vectorTexture.push_back(gBackground);
    SDL_FreeSurface(pSurFace);
    }

}


bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    //Time = SDL_GetTicks();
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(m_pWindow == 0)
    {
        std::cout << "fail create window\n";
        return false;
    }
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == 0)
    {
        std::cout << "fail to create renderer\n";
        return false;
    }
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    TextureManager::Instance()->load("final-Photoroom.png-Photoroom.png", "animate", m_pRenderer);
    m_khunglong = new Khunglong(new LoaderParams(0, 500, 60, 60, "animate"));

return true;
}

void Game::render()
{

    SDL_RenderClear(m_pRenderer);
    Game::Instance()->middlerenderbackground();
    Game::Instance()->movebackground();
    Game::Instance()->renderbackground();
    Game::Instance()->rendernextbackground();
    m_khunglong->draw();
for(int i = 0; i < vectormonster.size(); i++)
{
    vectormonster[i]->draw();
}

for(int i = 0; i < vectorbat.size(); i++)
{
    vectorbat[i]->draw();
}
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{

unsigned int currentTime = SDL_GetTicks();

    m_khunglong->update();
if (currentTime - lastMonsterSpawnTime >= Time) // Thời gian giữa mỗi lần tạo monster là 5000ms
    {

        TextureManager::Instance()->load("cactus.png", "monster", m_pRenderer);
        m_monster = new Monster(new LoaderParams(1000, 500, 37, 57, "monster"));

        m_monster->update();
        vectormonster.push_back(m_monster);
        lastMonsterSpawnTime = currentTime;
        Time = rand() % 5000 + 500 ;
    }

    for(int i = 0; i < vectormonster.size(); i++)
    {
        if(vectormonster[i] -> getpositionX() <= 0)
        {
            delete vectormonster[i];
            vectormonster.erase(vectormonster.begin() + i);
            continue;
        }
        vectormonster[i]->update();
    }
unsigned int currentTime1 = SDL_GetTicks();
    if (currentTime1 - lastBatSpawnTime >= Time1) // Thời gian giữa mỗi lần tạo monster là 5000ms
    {

        TextureManager::Instance()->load("bat.png", "bat", m_pRenderer);
        m_bat = new Bat(new LoaderParams(1000, 500, 43, 60, "bat"));

        m_bat->update();
        vectorbat.push_back(m_bat);
        lastBatSpawnTime = currentTime;
        Time1 = rand() % 7000 + 2500;
    }
    for(int i = 0; i < vectorbat.size(); i++)
    {
        if(vectorbat[i]->getpositionX() <= 0)
        {
            delete vectorbat[i];
            vectorbat.erase(vectorbat.begin() + i);
            continue;
        }
        vectorbat[i]->update();
    }
    for(int i = 0; i < vectormonster.size(); i++)
    {
        checkcollisionbox(vectormonster[i], m_khunglong);
    }

for(int i = 0; i < vectorbat.size(); i++)
    {
        checkcollisionbox(vectorbat[i], m_khunglong);
    }

}
void Game::quit()
{
    SDL_Quit();
}
void Game::clean()
{
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);

}
void Game::movebackground()
{
    if(backgroundvelocity <= -1000) backgroundvelocity += 1000;
    backgroundX += backgroundvelocity ;
    //backgroundvelocity += backgroundacceleration;
}
void Game :: renderbackground()
{
    if(backgroundX == -backgroundwidth) backgroundX = 0;
    SDL_Rect destRect;
    destRect.x = backgroundX;
    destRect.y = backgroundY;
    destRect.w = backgroundwidth;
    destRect.h = backgroundheight;
    for(int i = 0; i < vectorTexture.size(); i++)
    {
        SDL_RenderCopy(m_pRenderer, vectorTexture[i],0, &destRect);
    }
}
void Game::rendernextbackground()
{   int backgroundXcontinue;
    if(backgroundX <= -backgroundwidth) backgroundX =0 ;
    backgroundXcontinue = backgroundX  + backgroundwidth;


    for(int i = 0; i < vectorTexture.size(); i++)
    {
        SDL_Rect destRect;
    destRect.x = backgroundXcontinue ;
    destRect.y = backgroundY;
    destRect.w = backgroundwidth;
    destRect.h = backgroundheight;
        SDL_RenderCopy(m_pRenderer, vectorTexture[i],0, &destRect);
    }
}
void Game::middlerenderbackground()
{
    int backgroundXcontinue = 0;



    SDL_Rect destRect;
    destRect.x = backgroundXcontinue ;
    destRect.y = backgroundY;
    destRect.w = backgroundwidth;
    destRect.h = backgroundheight;
    for(int i = 0; i < vectorTexture.size(); i++)
    {

        SDL_RenderCopy(m_pRenderer, vectorTexture[i],0, &destRect);

    }
}

void Game::checkcollisionbox(SDLGameObject* monster, SDLGameObject* khunglong) {
    SDL_Rect monsterRect = monster->getcollisionbox();
    SDL_Rect khunglongRect = khunglong->getcollisionbox();

    if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
        // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
        // Trong ví dụ này, tôi chỉ sử dụng SDL_Quit() để thoát khỏi trò chơi
        TextureManager::Instance()->load("lose.png", "lose", m_pRenderer);
        TextureManager::Instance()->draw("lose", 0, 0, 928, 522, m_pRenderer);
         SDL_RenderPresent(m_pRenderer);
         bool check = false;
         while(!check)
         {
             SDL_Event event;
        while (!check) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        clean();
                        quit();
                    }
                }
                if(event.type = SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == SDLK_SPACE)
                    {
                        check = true;
                        restartgame();
                    }
                }
            }
         }

    }
}
}

void Game :: restartgame()
{
    backgroundX = 0;
    backgroundY = 0;
    backgroundvelocity = -3;
    backgroundwidth = 1000;
    backgroundheight = 600;
    lastMonsterSpawnTime = 0;
    lastBatSpawnTime = 0;
    Time = 0;
    Time1 = 0;
    checkcontinue = true;

    for(SDLGameObject* x : vectormonster)
    {
        delete x;
    }
    for(SDLGameObject* x : vectorbat)
    {
        delete x;
    }
    vectorbat.clear();
    vectormonster.clear();
    m_khunglong->setpositionX(0);
}
