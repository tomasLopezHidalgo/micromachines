#ifndef MICROMACHINES_TILE_H
#define MICROMACHINES_TILE_H

#include "Texture.h"
#include "Camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

class Tile {
    private:
        SDL_Rect box;
        Texture& texture;

    public:
        Tile(Window& window,
             const std::string& img,
             int x, int y, int h, int w);

        Tile(Tile&& other);

        void render(Camera& cam);

};

#endif
