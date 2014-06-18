#include "texture.h"
#include <SDL_image.h>
#include <SDL.h>
#include <cassert>
#include <stdio.h>
#include <SDL.h>
#include "global.h"
#include "player.h"
#include <stdio.h>

using namespace std;

namespace xx {
    Player::Player (int x,
                    int y,
                    std::string img,
                    SDL_Renderer *renderer) {
        mPlayerBox = { x, y, 32, 48};
        mRenderer = renderer;
        mPlayerTexture.loadFromFile(mRenderer,img);
        dis = -1;
        movx = 0;
        movy = 0;
        direction = DOWN;
    }
    Player::~Player (){
        mPlayerTexture.free();
        }
   void Player::moving ( int direct) {
        int x[2],y[2];
        x[0]=32,x[1]=96;
        direction = direct;
        movx  = 0;
        movy = 0;
        switch (direction) {
            case LEFT :
                y[0] = 48;
                y[1] = y[0];
                movx = -1;
                break;
            case RIGHT :
                y[0] = 96;
                y[1] = y[0];
                movx = 1;
                break;
            case UP :
                y[0] = 144;
                y[1] = y[0];
                movy = -1;
                break;
            case DOWN :
                y[0] = 0;
                y[1] = y[0];
                movy = 1;
                break;
        }
        moveClip[0] = {x[0],y[0],32,48};
        moveClip[1] = {x[1],y[1],32,48};
        dis = 0;
        printf("Begin Walk\n");
        printf("%d\n",movx);
    }
    void Player::show() {
        if (dis!=-1) {
            mPlayerBox.x+=movx;
            mPlayerBox.y+=movy;
            posx = mPlayerBox.x;
            posy = mPlayerBox.y;
            dis++;
            mPlayerTexture.render(mRenderer,mPlayerBox.x,mPlayerBox.y,&moveClip[(dis-1)/16]);
            printf("%d  :   %d\n",movx,movy);
            if (dis == 32) printf("End Step\n");
            if (dis == 32) dis = -1;
        } else standing();
    }
    void Player::standing(){
        int x = 0 , y;
        switch (direction) {
            case LEFT :
                y = 48;
                break;
            case RIGHT :
                y = 96;
                break;
            case UP :
                y = 144;
                break;
            case DOWN :
                y = 0;
                break;
        }
            SDL_Rect standBox = { x, y, 32, 48};
            mPlayerTexture.render(mRenderer,mPlayerBox.x,mPlayerBox.y,&standBox);
    }

}
