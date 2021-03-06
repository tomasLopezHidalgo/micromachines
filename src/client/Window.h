#ifndef MICROMACHINES_WINDOW_H
#define MICROMACHINES_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

class Texture;

class Window {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int h;
        int w;

    public:
        explicit Window(const std::string& title);
        Window(const std::string& title, int w, int h);
        Texture& createTextureFrom(const std::string& img);
        void render(SDL_Texture *texture,
                    SDL_Rect& textureInfo,
                    SDL_Rect& dstTexture,
                    int angle);
        int getHeight();
        int getWidth();
        SDL_Renderer* getRenderer();
        void setTarget(SDL_Texture* target);
        void update();
        void clear();
        ~Window();
};
#endif
