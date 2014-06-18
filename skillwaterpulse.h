#ifndef __waterpulse_h__
#define __waterpulse_h__
#include "texture.h"
#include <SDL.h>
using namespace std;
namespace xx{
class Waterpulse {
    public:
    Waterpulse(int,int,int,SDL_Renderer*);
    ~Waterpulse();
    SDL_Renderer* mRenderer;
    Texture txtr;
    SDL_Rect sprite[20];
    void show();
    int dir;
    int x;
    int y;
    int current;
};
}
#endif

