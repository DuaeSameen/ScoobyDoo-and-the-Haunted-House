#include "../headers/AssetManager.hpp"

//sdl function gRenderer
AssetManager::AssetManager(SDL_Renderer* gRenderer) {
    AssetManager::gRenderer = gRenderer;
}

//populates the hash map
bool AssetManager::load(string key, Asset* asset) {
    AssetManager::map[key] = asset;
    if(!AssetManager::map[key]->load(AssetManager::gRenderer))
    {
        return false;
    }
    return true;
}

bool AssetManager::loadImage(string path, string key, int x, int y, int w, int h) {
    if(!AssetManager::load(key, new Asset(path, x, y, w, h)))
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        return false;
    }
    return true;
}

//returns asset from hash map using provided key
Asset* AssetManager::get(string key) {
    return AssetManager::map[key];
}

//renders image with original width and height (background)
void AssetManager::render(string key, int x, int y) {
    Asset* asset = AssetManager::get(key);

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = asset->getRect()->w;
    destRect.h = asset->getRect()->h;
    SDL_RenderCopy( AssetManager::gRenderer, asset->getTexture(), asset->getRect(), &destRect );
}

//renders image with modified width and height provided as parameters (all other assets)
void AssetManager::render(string key, int x, int y, int w, int h) {
    Asset* asset = AssetManager::get(key);

    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;
    destRect.w = w;
    destRect.h = h;
    SDL_RenderCopy( AssetManager::gRenderer, asset->getTexture(), asset->getRect(), &destRect );
}

//iterates over all key-asset pairs and deletes each asset
AssetManager::~AssetManager() {
    unordered_map<string, Asset*>::iterator it = AssetManager::map.begin();
    while(it != AssetManager::map.end()) {
        delete it->second; //deletes mapped value   
    }
}