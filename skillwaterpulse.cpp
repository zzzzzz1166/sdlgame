#include "texture.h"
#include "skillwaterpulse.h"
#include <math.h>
#include <stdio.h>
namespace xx {
    Waterpulse::Waterpulse(int xx,int yy,int direct,SDL_Renderer* render) {
    txtr.loadFromFile(render,"Blizzaga.png");
    mRenderer = render;
    dir = direct;
    x = xx;
    y = yy;
    /*for (int i=1; i<=19 ; i++) {
        sprite[i].y=(ceil(i / 5.0)-1)*96;
        sprite[i].x=(i  - (ceil(i / 5.0)-1)*5 -1 )*96;
        sprite[i].w=96;
        sprite[i].h=96;

    }
    current = 0;
    show();*/
}
Waterpulse::~Waterpulse() {
    txtr.free();
}
    void Waterpulse::show() {
        txtr.render(mRenderer,x,y,&sprite[++current]);
    }
}
