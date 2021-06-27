#include "Map.h"
Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

//--------------------------------------------------------------------------------
// Function    : Map::Map_init
// Description : Load pictures and background music(bgm) of map
// Note        :
// Input       : None
// Output      : None
//--------------------------------------------------------------------------------
void Map::Map_init(){
    //load all map pictures
    load();

    //set icon's position
    for(int i=0;i<icon_n;i++){
        Map_Button[i].set_value(Map_Button_x[i],Map_Button_y[i],iconm[i]);
        Map_Button[i].load_soundtrack();
    }//for(int i=0;i<icon_n;i++)

    for(int i=0;i<menu_num;i++){
        Menu_Button[i].set_value(Menu_Button_x[i],Menu_Button_y[i],menum[i]);
        Menu_Button[i].load_soundtrack();
    }//for(int i=0;i<menu_num;i++)

    //load music
    for(int i=0;i<MUSIC;i++)bgm[i].loadmusic(music_name[i]);

    //new tutorial
    tutorial_guide=new TUTORIAL;
}// FUNCTION : Map::Map_init

//--------------------------------------------------------------------------------
// Function    : Map::load
// Description : Load images of different private class members
// Note        :
// Input       : None
// Output      : None
//--------------------------------------------------------------------------------
void Map::load(){//load LTexture&Change
    for(int k=0;k<menu_num;k++)     Menu_Button[k].loadFromFile(menu_image[k]);
    for(int k=0;k<scene_num;k++)    scene[k].loadFromFile(scene_image[k]);
    for(int k=0;k<map_num;k++)      _map[k].loadFromFile(map_image[k]);
    for(int k=0;k<about_num;k++)    about[k].loadFromFile(about_image[k]);
    for(int k=0;k<icon_n;k++)       Map_Button[k].loadFromFile(Map_Button_Image[k]);
}// FUNCTION : Map::load

//--------------------------------------------------------------------------------
// Function    : Map::Map_mode
// Description : Main running function of Map of different modes in SDL loop
//               For example, mode 0 is the story background introduciton, and mode 1 is the main menu.
//               In each mode, you will need to specify the bgm, _map(background image), and icons(game characters).
//               Function render(x,y) of each private class member will place the image at position(x,y).
//               Finally, use SDL_RenderPresent( gRenderer ) to render the image to the window.                 
// Note        : mode 0 : Main Menu
//               mode 1 : Big Map to Choose Battle Scenarios
//               mode 2 : Different Battle Scenarios
//               mode 11: Tutorial
//               mode 12: Game Information
//               mode 13: Start Scene
//               mode 14: Background Introduction
//               mode 15: Game Finish Scene
//               mode 16: Quit Game
// Input       : SDL_Event &e       : User Input
//               BATTLE_SCENE **b   : Battle Scenarios
//               bool &quit         : Whether to Quit
// Output      : None
//--------------------------------------------------------------------------------
void Map::Map_mode(SDL_Event &e,BATTLE_SCENE **b,bool &quit){
    switch(mode){

        //mode MAIN_MENU_MODE : Main Menu
        case MAIN_MENU_MODE:
            bgm[maple].playmusic();
            scene[0].scroll(1,0,1);
            _map[title].render(340,25);
            _map[version].render(1138,613);

            for(int i=0;i<menu_num-2;i++){
                Menu_Button[i].menu_button_reaction(e,mode);
                if(mode!=MAIN_MENU_MODE){
                    bgm[maple].stopmusic();
                    SDL_Delay(200);
                    break;
                }//if(mode)
            }//for(int i=0;i<menu_num-2;i++)
            SDL_RenderPresent( gRenderer );
        break;//case MAIN_MENU_MODE

        //mode BIG_MAP_MODE : Big Map to Choose Battle Scenarios
        case BIG_MAP_MODE:
            bgm[village].playmusic();
            _map[bigmap].render(0,0);
            Map_Button[gomenu].map_button_reaction(e,mode);

            for(int i=0;i<icon_n-3;i++){
                if(i==Scenario_Num){
                    //press button to select battle scenario
                    Map_Button[i].map_button_reaction(e,mode);

                    if(mode!=BIG_MAP_MODE){
                        played[i] = 1;
                        b[Scenario_Num]=new BATTLE_SCENE(Scenario_Num%3);
                        bgm[village].stopmusic();
                        SDL_Delay(200);break;
                    }//if(mode!=BIG_MAP_MODE)
                }//if(played[i])

                else if(played[i]){
                    Map_Button[i].map_button_showup(played[i]);
                }

                else{
                    //do nothing
                }
            }//for(int i=0;i<icon_n;i++)
            SDL_RenderPresent( gRenderer );
        break;//case BIG_MAP_MODE

        //mode BATTLE_SCENARIO_MODE : Different Battle Scenarios
        case BATTLE_SCENARIO_MODE:
            bgm[(Scenario_Num)%3+2].playmusic();
            b[Scenario_Num][0].battle(e,mode);
            if(Scenario_Num>=3)Map_Button[skip].map_button_reaction(e,mode);
            if(mode==BIG_MAP_MODE){

                Map_Button[Scenario_Num].clean=0;
                Scenario_Num++;
                bgm[(Scenario_Num)%3+2].stopmusic();
                SDL_Delay(200);
                if(Scenario_Num==3){
                    mode = FINISH_SCENE_MODE;
                    break;
                }//if(Scenario_Num==3)
                if(Scenario_Num==12){
                    quit=true;
                    break;
                }//if(Scenario_Num==12)
            }//if(mode==BIG_MAP_MODE)
            SDL_RenderPresent( gRenderer );
        break;//case BATTLE_SCENARIO_MODE

        //mode TUTORIAL_MODE: Tutorial
        case TUTORIAL_MODE:
            bgm[bar].playmusic();
            tutorial_guide->teach(&e);
            Map_Button[gomenu].map_button_reaction(e,mode);

            if(mode!=TUTORIAL_MODE){
                bgm[bar].stopmusic();
                SDL_Delay(200);
                break;
            }//if(mode!=TUTORIAL_MODE)
            SDL_RenderPresent( gRenderer );
        break;//case TUTORIAL_MODE

        //mode GAME_INFORMATION_MODE: Game Information
        case GAME_INFORMATION_MODE:
            about[0].scroll(0,1,0);
            Map_Button[gomenu].map_button_reaction(e,mode);

            if(mode==MAIN_MENU_MODE){
                about[0].offsety=0;
                SDL_Delay(200);
            }//if(mode==MAIN_MENU_MODE)
            SDL_RenderPresent( gRenderer );
        break;//case GAME_INFORMATION_MODE
                
        //mode START_SCENE_MODE: Start Scene
        case START_SCENE_MODE:
            for(int t=0;t<256;t++){
                _map[black].render(0,0);
                _map[brand].setAlpha(t);
                _map[brand].render(206,270);
                t++;
                SDL_RenderPresent( gRenderer );
            }//for(int t=0;t<256;t++)
            for(int t=255;t>0;t--){
                _map[black].render(0,0);
                _map[brand].setAlpha(t);
                _map[brand].render(206,270);
                t--;
                SDL_RenderPresent( gRenderer );
            }//for(int t=255;t>0;t--)
            mode=MAIN_MENU_MODE;
        break;//case START_SCENE_MODE

        //mode BACKGROUND_INTRO_MODE: Background Introduction
        case BACKGROUND_INTRO_MODE://
            scene[1].scroll(0,1,0);
            bgm[teacher1].playmusic();
            Map_Button[teacher].map_button_reaction(e,mode);

            if(mode!=BACKGROUND_INTRO_MODE){
                bgm[teacher1].stopmusic();
                SDL_Delay(200);
                scene[1].offsety=0;
            }//if(mode!=BACKGROUND_INTRO_MODE)
            SDL_RenderPresent( gRenderer );
        break;//case BACKGROUND_INTRO_MODE
        
        //mode FINISH_SCENE_MODE: Game Finish Scene
        case FINISH_SCENE_MODE:
            bgm[sorrow].playmusic();
            scene[0].scroll(1,0,1);
            _map[finish].render(340,25);
            
            for(int i=3;i<menu_num;i++){
                Menu_Button[i].menu_button_reaction(e,mode);
                        
                if(mode!=FINISH_SCENE_MODE){
                    bgm[sorrow].stopmusic();
                    SDL_Delay(200);
                    break;
                }//if(mode!=FINISH_SCENE_MODE)
            }//for(int i=3;i<menu_num;i++)
            SDL_RenderPresent( gRenderer );
        break;//case FINISH_SCENE_MODE
        
        //mode QUIT_GAME_MODE: Quit Game
        case QUIT_GAME_MODE:
            quit=true;
        break;//case QUIT_GAME_MODE

    }//switch(mode)
    return;
}//// FUNCTION : Map::Map_mode