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
    // cài đặt các thông số cho background
    lastMonsterSpawnTime = 0;
    lastBatSpawnTime = 0;
    lastMeteorSpawnTime = 0;
    // biến thời gian xác định thời gian cuối cùng tạo ra đối tượng để tính toán tạo ra đối tượng trong lần tiếp theo
    Time = 0;
    Time1 = 0;
    Timemeteor = 0;
   // biến tính thời gian từ khi chơi game
    Point = 0;
    highscore = 0;
    // tính điểm cho game
}

// hàm vẽ text lên màn hình ( ở đây là score + highscore)
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

// hàm vẽ text thời gian trước khi vào game
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

// gần giống hàm render nhưng được sử dụng khi đợi chạy thời gian vào game
void Game::renderforText()
{
    SDL_RenderClear(m_pRenderer);

    Game::Instance()->middlerenderbackground();
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
    for (int i = 0; i < vectormeteor.size(); i++)
    {
        vectormeteor[i]->draw();
    }
    if (m_heart) m_heart->drawmonster();
    Game::Instance()->drawtext();
    SDL_RenderPresent(m_pRenderer);
}

// hàm tạo âm thanh cho game
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

// dừng tất cả âm thanh
void Game::stopallsoundeffect()
{
    Mix_HaltChannel(-1);
}

// hàm load phong cảnh cho game 
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

// hàm load menu cho game
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

// tạo cửa sổ, khủng long và trái tim
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
    TextureManager::Instance()->load("img/heart (1).png", "heart", m_pRenderer);
    scoreheart = new Heart(new LoaderParams(3, 40, 50, 40, "heart"));
    vectorheart.push_back(scoreheart);
    scoreheart = new Heart(new LoaderParams(24, 40, 50, 40, "heart"));
    vectorheart.push_back(scoreheart);
    scoreheart = new Heart(new LoaderParams(45, 40, 50, 40, "heart"));
    vectorheart.push_back(scoreheart);
    return true;
}

// render lên màn hình
void Game::render()
{

    SDL_RenderClear(m_pRenderer);

    Game::Instance()->middlerenderbackground();
    Game::Instance()->movebackground();
    Game::Instance()->renderbackground();
    Game::Instance()->rendernextbackground();
    m_khunglong->draw();
    if (m_heart)
    {
        std::cout << "ok\n";
        m_heart->drawmonster();
    }
    for (int i = 0; i < countheart; i++)
    {
        vectorheart[i]->drawmonster();
    }
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

// trong hàm này gồm: 
// dựa vào Point tạo nhiều trạng thái của khủng long, tạo trái tim khi ăn sẽ tăng mạng; 
// dựa vào thời gian + Point tạo bat, monster (xương rồng) , thiên thạch (meteor) 
// update các trạng thái di chuyển cũng như xuất hiện hoặc không của khủng long, thiên thạch, bat, xương rồng
// check va chạm 
void Game::update()
{
    
    if (m_heart) m_heart->update();
    if (statekhunglong == 0)
    {
        if (Point >= 1000)
        {
            if (m_khunglong->getpositionY() == 500)
            {
                TextureManager::Instance()->load("img/yellowkhunglong.png", "yellowkhunglong", m_pRenderer);
                m_khunglong = new Khunglong(new LoaderParams(m_khunglong->getpositionX(), m_khunglong->getpositionY(), 60, 60, "yellowkhunglong"));

                statekhunglong = 1;
            }
        }
    }
    else if (statekhunglong == 1)
    {
        if (Point >= 5000)
        {
            if (m_khunglong->getpositionY() == 500)
            {
                TextureManager::Instance()->load("img/redkhunglong.png", "redkhunglong", m_pRenderer);
                m_khunglong = new Khunglong(new LoaderParams(m_khunglong->getpositionX(), m_khunglong->getpositionY(), 60, 60, "redkhunglong"));

                statekhunglong = 2;
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
            }
        }
    }
    m_khunglong->update();
    if (Point % 2500 == 0 && Point != 0)
    {
        TextureManager::Instance()->load("img/heart (1).png", "heart", m_pRenderer);
        m_heart = new Heart(new LoaderParams(1000, 440, 60, 50, "heart"));
        if (!m_heart)
        {
            std::cout << "fail to load heart";
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
        if(Point < 3000) Time = rand() % 5000 + 500;
        else if (Point < 5000)  Time = rand() % 4000 + 500;
        else Time = rand() % 3000 + 500;
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
            lastBatSpawnTime = currentTime1;
            if(Point < 4000)    Time1 = rand() % 7000 + 2500; 
            else if (Point < 10000) Time1 = rand() % 6000 + 2500;
            else Time1 = rand() % 4500 + 2500;
        }
    }
    if (Point >= 3000)
    {
        if (currentTime - lastMeteorSpawnTime >= Timemeteor)
        {
            int ran = rand() % 600 + 500;
            TextureManager::Instance()->load("img/meteor.png", "meteor", m_pRenderer);
            m_meteor = new Meteor(new LoaderParams(ran, 0, 160, 211, "meteor"));

            m_meteor->update();
            vectormeteor.push_back(m_meteor);
            lastMeteorSpawnTime = currentTime;
            if (Point < 5000)
            {
                Timemeteor = rand() % 5000 + 10000;
            }
            else if (Point < 10000) Timemeteor = rand() % 5000 + 5000;
            else Timemeteor = rand() % 3000 + 1000;
        }
    }
    
    for (int i = 0; i < vectormonster.size(); i++)
    {
        if (vectormonster[i]->getpositionX() <= -20)
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
        if (vectorbat[i]->getpositionX() <= -20)
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

    if (m_heart) {
        SDL_Rect monsterRect = m_heart->getcollisionbox();
        SDL_Rect khunglongRect = m_khunglong->getcollisionbox();
        if (m_heart->getpositionX() <= 0) delete m_heart;
        if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
            // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
            Point += 500;
            Game::Instance()->soundeffect("sound/heart_sound.wav", 0);
           if(countheart < 3)  countheart++;
            m_heart = 0;
            
        }
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

// render menu mặc định lên màn hình 
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

// render menu với nút play trắng
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
// render menu với nút help trắng
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
// render menu với nút exit trắng
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
// render instruction mặc định
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
// render instruction nút thoát trắng
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
// di chuyển background dựa vào tốc độ đã cài đặt
void Game::movebackground()
{
    backgroundX += backgroundvelocity;
}
// render background hiện tại
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
//render background tiếp theo
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
// render 1 background giữa background hiện tạo và nextbackground để đè mất đi khoảng trắng
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

// check va chạm khủng long với bat, xương rồng
void Game::checkcollisionbox(SDLGameObject* monster, SDLGameObject* khunglong) {
    SDL_Rect monsterRect = monster->getcollisionbox();
    SDL_Rect khunglongRect = khunglong->getcollisionbox();
    unsigned int Timeheart = SDL_GetTicks();
    if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
        // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
        // Trong ví dụ này, tôi chỉ sử dụng SDL_Quit() để thoát khỏi trò chơi
        if (Timeheart - lastheartTime >= 300) {
            countheart--;
            lastheartTime = Timeheart;
            Game::Instance()->soundeffect("sound/lose_sound.wav", 0);
        }

        if (countheart == 0)
        {
            TextureManager::Instance()->load("img/lose.png", "lose", m_pRenderer);
            TextureManager::Instance()->draw("lose", 0, 0, 928, 522, m_pRenderer);
            Game::Instance()->soundeffect("sound/lose_sound.wav", 0);
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
   
}

// check va chạm với thiên thạch
void Game::checkcollisionboxmeteor(SDLGameObject* monster, SDLGameObject* khunglong) {
    SDL_Rect monsterRect = monster->getcollisionboxmeteor();
    SDL_Rect khunglongRect = khunglong->getcollisionbox();

    if (SDL_HasIntersection(&monsterRect, &khunglongRect)) {
        // Xử lý va chạm ở đây, ví dụ: kết thúc trò chơi, giảm máu, ...
        // Trong ví dụ này, tôi chỉ sử dụng SDL_Quit() để thoát khỏi trò chơi
        TextureManager::Instance()->load("img/lose.png", "lose", m_pRenderer);
        TextureManager::Instance()->draw("lose", 0, 0, 928, 522, m_pRenderer);
        Game::Instance()->soundeffect("sound/lose_sound.wav", 0);
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

// cài lại cài đặt mặc định để bắt đầu lại game
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
    statekhunglong = 0;
    countheart = 3;
    m_heart = 0;
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
