
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include<string>
#include<map>
#include <SDL.h>
class TextureManager {
public:

    static TextureManager* Instance()
{
 if(s_pInstance == 0)
 {
 s_pInstance = new TextureManager();
 return s_pInstance;
 }
 return s_pInstance;
}


bool load(std::string fileName,std::string id,
SDL_Renderer* pRenderer);
void draw(std::string id, int x, int y, int width, int
height, SDL_Renderer* pRenderer, SDL_RendererFlip flip =
SDL_FLIP_NONE);
// drawframe
void drawFrame(std::string id, int x, int y, int width, int
height, int currentRow, int currentFrame, SDL_Renderer*
pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

void clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}
protected:
private:

    TextureManager(){}
    static TextureManager* s_pInstance;
    std::map<std::string, SDL_Texture*> m_textureMap;
    // Declare but do not define the default constructor

};

// Initialize the static member outside the class definition


#endif // TEXTUREMANAGER_H

