#include "game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Game* Game::s_pInstance = 0;

Game::Game() {
    backgroundX = 0;
    backgroundY = 0;
    backgroundvelocity = -3;
    backgroundwidth = 1000;
    backgroundheight = 600;
    lastMonsterSpawnTime = 0;
    lastBatSpawnTime = 0;
    lastMeteorSpawnTime = 0;
    Time = 0;
    Time1 = 0;
    Timemeteor = 0;
    checkcontinue = true;
    Point = 0;
    highscore = 0;

}

void Game::drawtext()
{


    TTF_Init();
    // Mở phông chữ (nên làm điều này một lần trong quá trình khởi tạo và sử dụng lại)
    TTF_Font* font = TTF_OpenFont("ttf/pixel_font.ttf", 20);
    if (!font) {
        std::cout << "fail to load font\n";
        return;
    }

    // Định nghĩa màu cho văn bản
    SDL_Color color = { 0, 0, 0 }; // Màu đen
    std::string point = "score: " + std::to_string(Point);
    std::string highpoint = "highscore: " + std::to_string(highscore);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, point.c_str(), color);

    if (!textSurface) {
        std::cout << "fail to create surface\n";
        TTF_CloseFont(font);
        return;
    }

    // Tạo kết cấu từ bề mặt
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
    if (!textureText) {
        std::cout << "fail to create texture\n";
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Tạo hình chữ nhật để chứa văn bản
    SDL_Rect Message_rect;
    Message_rect.x = 20;  // tọa độ x của hình chữ nhật
    Message_rect.y = 0; // tọa độ y của hình chữ nhật
    Message_rect.w = textSurface->w; // chiều rộng của hình chữ nhật phù hợp với bề mặt
    Message_rect.h = textSurface->h; // chiều cao của hình chữ nhật phù hợp với bề mặt

    // Vẽ kết cấu văn bản lên màn hình
    SDL_RenderCopy(m_pRenderer, textureText, NULL, &Message_rect);


    // Giải phóng bề mặt và kết cấu để tránh rò rỉ bộ nhớ
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textureText);


    SDL_Surface* textsurface = TTF_RenderText_Solid(font, highpoint.c_str(), color);
    SDL_Texture* texturetext = SDL_CreateTextureFromSurface(m_pRenderer, textsurface);
    Message_rect.y = 20;
    Message_rect.w = textsurface->w; // chiều rộng của hình chữ nhật phù hợp với bề mặt
    Message_rect.h = textsurface->h;
    SDL_RenderCopy(m_pRenderer, texturetext, NULL, &Message_rect);
    SDL_FreeSurface(textsurface);
    SDL_DestroyTexture(texturetext);
    // Đóng phông chữ để giải phóng tài nguyên
    TTF_CloseFont(font);
}

void Game::loadtoplay(int n)
{
    Game::Instance()->renderforText();
    TTF_Init();
    // Mở phông chữ (nên làm điều này một lần trong quá trình khởi tạo và sử dụng lại)
    TTF_Font* font = TTF_OpenFont("ttf/pixel_font.ttf", 300);
    if (!font) {
        std::cout << "fail to load font\n";
        return;
    }

    // Định nghĩa màu cho văn bản
    SDL_Color color = { 255, 255, 255 }; // Màu đen
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(n).c_str(), color);

    if (!textSurface) {
        std::cout << "fail to create surface\n";
        TTF_CloseFont(font);
        return;
    }

    // Tạo kết cấu từ bề mặt
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(m_pRenderer, textSurface);
    if (!textureText) {
        std::cout << "fail to create texture\n";
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Tạo hình chữ nhật để chứa văn bản
    SDL_Rect Message_rect;
    Message_rect.x = 410;  // tọa độ x của hình chữ nhật
    Message_rect.y = 100; // tọa độ y của hình chữ nhật
    Message_rect.w = textSurface->w; // chiều rộng của hình chữ nhật phù hợp với bề mặt
    Message_rect.h = textSurface->h; // chiều cao của hình chữ nhật phù hợp với bề mặt

    // Vẽ kết cấu văn bản lên màn hình

    SDL_RenderCopy(m_pRenderer, textureText, NULL, &Message_rect);
    SDL_RenderPresent(m_pRenderer);
    SDL_Delay(1000);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(textureText);
    SDL_RenderClear(m_pRenderer);
}

void Game::renderforText()
{
    SDL_RenderClear(m_pRenderer);

    Game::Instance()->middlerenderbackground();
    //Game::Instance()->movebackground();
    Game::Instance()->renderbackground();
    Game::Instance()->rendernextbackground();
    m_khunglong->draw();

    for (int i = 0; i < vectormonster.size(); i++)
    {
        vectormonster[i]->draw();
    }

    for (int i = 0; i < vectorbat.size(); i++)
    {
        vectorbat[i]->draw();
    }
    Game::Instance()->drawtext();
    SDL_RenderPresent(m_pRenderer);
}
void Game::soundeffect(std::string s, int n)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "fail to load mix_openaudio" << Mix_GetError();
        return;
    }
    Mix_Chunk* soundeffect = Mix_LoadWAV(s.c_str());
    if (!soundeffect)
    {
        std::cout << "fail to load soundeffect\n";
    }
    Mix_PlayChannel(-1, soundeffect, n);

}

void Game::stopallsoundeffect()
{
    Mix_HaltChannel(-1);
}
void Game::loadmedia()
{
    vectorfilename.push_back("img/layer01.png");
    vectorfilename.push_back("img/layer02.png");
    vectorfilename.push_back("img/layer03.png");
    vectorfilename.push_back("img/layer04.png");
    vectorfilename.push_back("img/layer05.png");
    vectorfilename.push_back("img/layer06.png");
    vectorfilename.push_back("img/layer07.png");
    vectorfilename.push_back("img/layer08.png");
    vectorfilename.push_back("img/layer09.png");
    vectorfilename.push_back("img/layer11.png");
    for (int i = 0; i < vectorfilename.size(); i++)
    {
        SDL_Surface* pSurFace = IMG_Load(vectorfilename[i].c_str());
        if (pSurFace == 0)
        {
            std::cout << "fail to load background\n";
            return;
        }
        SDL_Texture* gBackground = SDL_CreateTextureFromSurface(m_pRenderer, pSurFace);
        if (gBackground == 0)
        {
            std::cout << "fail to create texture\n";
            SDL_FreeSurface(pSurFace);
            return;
        }
        vectorTexture.push_back(gBackground);
        SDL_FreeSurface(pSurFace);
    }

}
void Game::loadmenu()
{

    vectormenu.push_back("img/menu0.png");
    vectormenu.push_back("img/menu1.png");
    vectormenu.push_back("img/menu2.png");
    vectormenu.push_back("img/instruction.png");
    vectormenu.push_back("img/instruction1.png");
    SDL_Surface* gmenu = IMG_Load("img/menu.png");
    for (int i = 0; i < 5; i++)
    {
        SDL_Surface* gSurface = IMG_Load(vectormenu[i].c_str());
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, gSurface);
        vectorTextureMenu.push_back(pTexture);
        SDL_FreeSurface(gSurface);
    }
    if (gmenu == 0)
    {
        std::cout << "fail to load menu";
        return;
    }
    pmenu = SDL_CreateTextureFromSurface(m_pRenderer, gmenu);
    SDL_FreeSurface(gmenu);

}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow == 0)
    {
        std::cout << "fail create window\n";
        return false;
    }
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == 0)
    {
        std::cout << "fail to create renderer\n";
        return false;
    }
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

    TextureManager::Instance()->load("img/final-Photoroom.png-Photoroom.png", "animate", m_pRenderer);
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

    for (int i = 0; i < vectormonster.size(); i++)
    {
        vectormonster[i]->draw();
    }
    for (int i = 0; i < vectormeteor.size(); i++)
    {
        vectormeteor[i]->draw();
    }

    for (int i = 0; i < vectorbat.size(); i++)
    {
        vectorbat[i]->draw();
    }
    Game::Instance()->drawtext();
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    if (i == 0)
    {
        if (Point >= 1000)
        {
            if (m_khunglong->getpositionY() == 500)
            {
                TextureManager::Instance()->load("img/yellowkhunglong.png", "yellowkhunglong", m_pRenderer);
                m_khunglong = new Khunglong(new LoaderParams(m_khunglong->getpositionX(), m_khunglong->getpositionY(), 60, 60, "yellowkhunglong"));

                i = 1;
            }
        }
    }
    else if (i == 1)
    {
        if (Point >= 5000)
        {
            if (m_khunglong->getpositionY() == 500)
            {
                TextureManager::Instance()->load("img/redkhunglong.png", "redkhunglong", m_pRenderer);
                m_khunglong = new Khunglong(new LoaderParams(m_khunglong->getpositionX(), m_khunglong->getpositionY(), 60, 60, "redkhunglong"));

                i = 2;
            }
        }
    }
    else
    {
        if (Point >= 10000)
        {
            if (m_khunglong->getpositionY() == 500)
            {
                TextureManager::Instance()->load("img/bluekhunglong.png", "bluekhunglong", m_pRenderer);
                m_khunglong = new Khunglong(new LoaderParams(m_khunglong->getpositionX(), m_khunglong->getpositionY(), 60, 60, "bluekhunglong"));
                i = -1;
            }
        }
    }

    unsigned int currentTime = SDL_GetTicks();


    if (currentTime - lastMonsterSpawnTime >= Time) // Thời gian giữa mỗi lần tạo monster là 5000ms
    {

        TextureManager::Instance()->load("img/cactus.png", "monster", m_pRenderer);
        m_monster = new Monster(new LoaderParams(1000, 500, 37, 57, "monster"));

        m_monster->update();
        vectormonster.push_back(m_monster);
        lastMonsterSpawnTime = currentTime;
        Time = rand() % 5000 + 500;
    }

    unsigned int currentTime1 = SDL_GetTicks();
    if (Point >= 1000)
    {
        if (currentTime1 - lastBatSpawnTime >= Time1) // Thời gian giữa mỗi lần tạo monster là 5000ms
        {

            TextureManager::Instance()->load("img/bat.png", "bat", m_pRenderer);
            m_bat = new Bat(new LoaderParams(1000, 500, 43, 60, "bat"));

            m_bat->update();
            vectorbat.push_back(m_bat);
            lastBatSpawnTime = currentTime;
            Time1 = rand() % 7000 + 2500;
        }
    }
    if (Point >= 20)
    {
        if (currentTime - lastMeteorSpawnTime >= Timemeteor)
        {
            int ran = rand() % 300 + 700;
            TextureManager::Instance()->load("img/meteor.png", "meteor", m_pRenderer);
            m_meteor = new Meteor(new LoaderParams(ran, 0, 160, 211, "meteor"));

            m_meteor->update();
            vectormeteor.push_back(m_meteor);
            lastMeteorSpawnTime = currentTime;
            if (Point < 10000)
            {
                Timemeteor = rand() % 5000 + 10000;
            }
            else Timemeteor = rand() % 5000 + 1000;
        }
    }
    m_khunglong->update();
    for (int i = 0; i < vectormonster.size(); i++)
    {
        if (vectormonster[i]->getpositionX() <= -5)
        {
            delete vectormonster[i];
            vectormonster.erase(vectormonster.begin() + i);
            continue;
        }
        if (vectormonster[i]->getpositionX() < m_khunglong->getpositionX())
        {
            Point += 1;
        }
        vectormonster[i]->update();
    }

    for (int i = 0; i < vectorbat.size(); i++)
    {
        if (vectorbat[i]->getpositionX() <= -5)
        {
            delete vectorbat[i];
            vectorbat.erase(vectorbat.begin() + i);
            continue;
        }
        if (vectorbat[i]->getpositionX() < m_khunglong->getpositionX())
        {
            Point += 1;
        }
        vectorbat[i]->update();
    }

    for (int i = 0; i < vectormeteor.size(); i++)
    {
        if (vectormeteor[i]->getpositionY() >= 700)
        {
            delete vectormeteor[i];
            vectormeteor.erase(vectormeteor.begin() + i);
            continue;
        }
        vectormeteor[i]->update();
    }



    for (int i = 0; i < vectormonster.size(); i++)
    {

        checkcollisionbox(vectormonster[i], m_khunglong);
    }

    for (int i = 0; i < vectorbat.size(); i++)
    {

        checkcollisionbox(vectorbat[i], m_khunglong);
    }

    for (int i = 0; i < vectormeteor.size(); i++)
    {

        checkcollisionboxmeteor(vectormeteor[i], m_khunglong);
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

void Game::rendermenu()
{
    if (backgroundX == -backgroundwidth) backgroundX = 0;
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, pmenu, 0, &destRect);
    SDL_RenderPresent(m_pRenderer);

}
void Game::rendermenubutton0()
{

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, vectorTextureMenu[0], 0, &destRect);
    // Xử lý các sự kiện khác ở đây (nếu cần)
    SDL_RenderPresent(m_pRenderer);
}
void Game::rendermenubutton1()
{

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, vectorTextureMenu[1], 0, &destRect);
    // Xử lý các sự kiện khác ở đây (nếu cần)
    SDL_RenderPresent(m_pRenderer);
}
void Game::rendermenubutton2()
{

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, vectorTextureMenu[2], 0, &destRect);
    // Xử lý các sự kiện khác ở đây (nếu cần)
    SDL_RenderPresent(m_pRenderer);
}
void Game::rendermenubutton3()
{

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, vectorTextureMenu[3], 0, &destRect);
    // Xử lý các sự kiện khác ở đây (nếu cần)
    SDL_RenderPresent(m_pRenderer);
}
void Game::rendermenubutton4()
{

    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1000;
    destRect.h = 600;

    SDL_RenderCopy(m_pRenderer, vectorTextureMenu[4], 0, &destRect);
    // Xử lý các sự kiện khác ở đây (nếu cần)
    SDL_RenderPresent(m_pRenderer);
}
void Game::movebackground()
{
    //if (backgroundvelocity <= -1000) backgroundvelocity += 1000;
    backgroundX += backgroundvelocity;

    //backgroundvelocity += backgroundacceleration;
}
void Game::renderbackground()
{

    if (backgroundX == -backgroundwidth) backgroundX = 0;
    SDL_Rect destRect;
    destRect.x = backgroundX;
    destRect.y = backgroundY;
    destRect.w = backgroundwidth;
    destRect.h = backgroundheight;
    for (int i = 0; i < vectorTexture.size(); i++)
    {
        SDL_RenderCopy(m_pRenderer, vectorTexture[i], 0, &destRect);
    }
}
void Game::rendernextbackground()
{
    int backgroundXcontinue;
    if (backgroundX <= -backgroundwidth) backgroundX = 0;
    backgroundXcontinue = backgroundX + backgroundwidth;


    for (int i = 0; i < vectorTexture.size(); i++)
    {
        SDL_Rect destRect;
        destRect.x = backgroundXcontinue;
        destRect.y = backgroundY;
        destRect.w = backgroundwidth;
        destRect.h = backgroundheight;
        SDL_RenderCopy(m_pRenderer, vectorTexture[i], 0, &destRect);
    }
}
void Game::middlerenderbackground()
{
    int backgroundXcontinue = 0;



    SDL_Rect destRect;
    destRect.x = backgroundXcontinue;
    destRect.y = backgroundY;
    destRect.w = backgroundwidth;
    destRect.h = backgroundheight;
    for (int i = 0; i < vectorTexture.size(); i++)
    {

        SDL_RenderCopy(m_pRenderer, vectorTexture[i], 0, &destRect);

    }
}

void Game::checkcollisionbox(SDLGameObject* monster, SDLGameObject* khunglong) {
    SDL_Rect monsterRect = monster->getcollisionbox();
    SDL_Rect khunglongRect = khunglong->getcollisionbox();

    if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
        // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
        // Trong ví dụ này, tôi chỉ sử dụng SDL_Quit() để thoát khỏi trò chơi
        TextureManager::Instance()->load("img/lose.png", "lose", m_pRenderer);
        TextureManager::Instance()->draw("lose", 0, 0, 928, 522, m_pRenderer);
        Game::Instance()->soundeffect("sound/jump_sound.wav", 0);
        SDL_RenderPresent(m_pRenderer);
        bool check = false;
        while (!check)
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
                    if (event.type = SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_SPACE)
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

void Game::checkcollisionboxmeteor(SDLGameObject* monster, SDLGameObject* khunglong) {
    SDL_Rect monsterRect = monster->getcollisionboxmeteor();
    SDL_Rect khunglongRect = khunglong->getcollisionbox();

    if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
        // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
        // Trong ví dụ này, tôi chỉ sử dụng SDL_Quit() để thoát khỏi trò chơi
        TextureManager::Instance()->load("img/lose.png", "lose", m_pRenderer);
        TextureManager::Instance()->draw("lose", 0, 0, 928, 522, m_pRenderer);
        Game::Instance()->soundeffect("sound/jump_sound.wav", 0);
        SDL_RenderPresent(m_pRenderer);
        bool check = false;
        while (!check)
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
                    if (event.type = SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_SPACE)
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
void Game::restartgame()
{
    backgroundX = 0;
    backgroundY = 0;
    backgroundvelocity = -3;
    backgroundwidth = 1000;
    backgroundheight = 600;
    lastMonsterSpawnTime = 0;
    lastBatSpawnTime = 0;
    lastBatSpawnTime = 0;
    Time = 0;
    Time1 = 0;
    Timemeteor = 0;
    checkcontinue = true;
    i = 0;
    m_khunglong = new Khunglong(new LoaderParams(0, 500, 60, 60, "animate"));
    if (Point > highscore) highscore = Point;
    Point = 0;

    for (SDLGameObject* x : vectormonster)
    {
        delete x;
    }
    for (SDLGameObject* x : vectorbat)
    {
        delete x;
    }
    for (SDLGameObject* x : vectormeteor)
    {
        delete x;
    }
    vectorbat.clear();
    vectormonster.clear();
    vectormeteor.clear();
    m_khunglong->setpositionX(0);
}
