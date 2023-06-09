#include "../headers/Asset.hpp"

#include <iostream>

Asset::Asset(string path, int x, int y, int w, int h) {
    Asset::path = path;
    Asset::rect = new SDL_Rect();
    Asset::rect->x=x;
	Asset::rect->y=y;
    Asset::rect->w=w;
    Asset::rect->h=h;
    Asset::loaded = false;
}

bool Asset::load(SDL_Renderer* gRenderer)
{
    if(!Asset::loaded) {
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
            printf( "Unable to load image %s! SDL_image Error: %s\n", Asset::path.c_str(), IMG_GetError() );
            return false;
        }
        else
        {
            //Create texture from surface pixels
            Asset::texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
            if( Asset::texture == NULL )
            {
                printf( "Unable to create texture from %s! SDL Error: %s\n", Asset::path.c_str(), SDL_GetError() );
                return false;
            }

            //Get rid of old loaded surface
            SDL_FreeSurface( loadedSurface );
        }
        Asset::loaded = true;
    }
    return true;
}

SDL_Texture* Asset::getTexture() {
    return Asset::texture;
}

SDL_Rect* Asset::getRect() {
    return Asset::rect;
}

Asset::~Asset() {
    SDL_DestroyTexture(Asset::texture);
}