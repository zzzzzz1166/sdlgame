#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL.h>
#include <string>
#include "texture.h"
#include <sdl.h>
using namespace std;

namespace xx {
class Player {
    SDL_Rect mPlayerBox;
    Texture mPlayerTexture;
    SDL_Renderer* mRenderer;
    int movx;
    int movy;
    int dis;
public:
    Player(int,int,std::string,SDL_Renderer*);
    ~Player();
    void moving(int direction);
    void standing();
    SDL_Rect moveClip[1];
    void show();
    int posx;
    int posy;
    int direction;
};
}

#endif // TEXTURE_H_INCLUDED
