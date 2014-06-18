/* Some of the code are originally written by LazyFoo Production. */
//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <SDLU.h>
#include "text.h"
#include "texture.h"
#include "global.h"
#include "player.h"
#include "skillwaterpulse.h"
using namespace std;
using namespace xx;

//Class to manage asset objects
class Assets {
    TTF_Font *mDefFont;

    public:

    TTF_Font *defFont() { return mDefFont; }

    Assets(): mDefFont(NULL)
    {
    }

    bool load()
    {
        //Open the font
        mDefFont = TTF_OpenFont( "NovaSquare.ttf", 20 );
        if( mDefFont == NULL )
        {
            printf( "Failed to load thefont! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }

        return true;
    }

    void teardown()
    {
        printf("Shut down assets.\n");
        TTF_CloseFont( mDefFont );
        mDefFont = NULL;
    }
};



class Application {
    //The window we'll be rendering to
    SDL_Window* mWindow;

    //The window renderer
    SDL_Renderer* mRenderer;

    SDL_Event e;

    Assets assets;
    public:
    Application(): mWindow(NULL), mRenderer(NULL)
    {
    }

    ~Application()
    {
        teardown();
    }

    int start() {

        bool quit = false;
        Player player(50,50,"princess.png",mRenderer);
        //Player archer(200,200,"archer.png",mRenderer);

        player.standing();
        //archer.standing();
        //Handle events on queue
        while (!quit) {
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //User presses a key
            else
            {
                if( e.type == SDL_KEYDOWN )
                {
                //Select surfaces based on key press
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP:
                    player.moving(UP);
                    break;

                    case SDLK_DOWN:
                    player.moving(DOWN);
                    break;

                    case SDLK_LEFT:
                    player.moving(LEFT);
                    break;

                    case SDLK_RIGHT:
                    player.moving(RIGHT);
                    break;

                    /*case SDLK_q:
                        checkfroze = true;
                        Waterpulse froze(player.posx,player.posy,DOWN,mRenderer);
                        break;*/
                    }
                }
                player.show();
                //archer.show();
                SDL_RenderPresent(mRenderer);
                SDL_RenderClear(mRenderer);
            }
        }
        }
    }
    bool loadExtensions()
    {
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            return false;
        }

         //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            return false;
        }

        return true;
    }

    bool init()
    {
        //Load media
        if( !loadExtensions() )
        {
            printf( "Failed to load extensions!\n" );
            return false;
        }

        //Load media
        if( !assets.load() )
        {
            printf( "Failed to load assets!\n" );
            return false;
        }

        SDL_SetHintWithPriority("SDL_RENDER_DRIVER", "opengl", SDL_HINT_OVERRIDE);

        //Initialize SDL
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
            return false;
        }

        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create mWindow
        mWindow = SDL_CreateWindow( "Scalar Heart", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( mWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            return false;
        }

        //Create vsynced renderer for mWindow
        mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( mRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            return false;
        }

        //Initialize renderer color
        SDL_SetRenderDrawColor( mRenderer, 55, 55, 55, 0xFF );
        //SDL_RenderClear(mRenderer);

        return true;
    }

    void teardown()
    {
        printf("shut down app.\n");
        SDL_DestroyRenderer( mRenderer );
        SDL_DestroyWindow( mWindow );
        mWindow = NULL;
        mRenderer = NULL;

        assets.teardown();
    	//Quit SDL subsystems
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }
};


int main(int argc, char* args[])
{
    Application app;

	//Start up SDL and create window
	if( !app.init() )
	{
		printf( "Failed to initialize!\n" );
		return 1;
	}

    return app.start();
}


