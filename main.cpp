#define _GLIBCXX_USE_CXX11_ABI 0
#include <stdio.h>
#include <SDL2/SDL.h>
#include "definition.h"
#include "initial.h"
#include "Map.h"

#include <MULTI_PLAYER.h>
Map m;
initial i;//initialize window and music

void Battle(SDL_Event &e,bool& quit){
	BATTLE_SCENE *Duck=new BATTLE_SCENE(0);
	int LEAVE_BATTLE=2;
	while( !quit && LEAVE_BATTLE!=1)
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}
		
        Duck->battle(e,LEAVE_BATTLE);
		SDL_RenderPresent( gRenderer );
    	SDL_RenderClear( gRenderer );
	}
}
int main( int argc, char* args[] )
{
	if( !i.init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
			//Main loop flag
			static bool quit = false;
            m.Map_init();
			//Event handler
			SDL_Event e;
            //initialization
            BATTLE_SCENE **DUCK=new BATTLE_SCENE* [12];

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
                m.Map_mode(e,DUCK,quit);
				if(m.Into_Battle){
					Battle(e,quit);
					m.Into_Battle=false;
				}
			}


        //Free resources and close SDL
        i.close();
	}
	return 0;
}

