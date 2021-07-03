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
    Load_BGI();

    //load music
    Load_BGM();

    //Initialize Map Buttons
    for(int i=0;i<icon_n;i++){
        //Initialize_Selection_Button(Map_Button[i],Map_Button_x[i],Map_Button_y[i],Map_Button_Mode[i],Map_Button_Image[i]);
        Map_Button[i].Initialize(Map_Button_x[i],Map_Button_y[i],Map_Button_Mode[i],Map_Button_Image[i]);
    }//for(int i=0;i<icon_n;i++)

    //Initialize Menu Buttons
    for(int i=0;i<menu_num;i++){
        //Initialize_Selection_Button(Menu_Button[i],Menu_Button_x[i],Menu_Button_y[i],Menu_Button_Mode[i],Menu_Button_Image[i]);
        Menu_Button[i].Initialize(Menu_Button_x[i],Menu_Button_y[i],Menu_Button_Mode[i],Menu_Button_Image[i]);
    }//for(int i=0;i<menu_num;i++)

    //new tutorial
    tutorial_guide=new TUTORIAL;
}// FUNCTION : Map::Map_init

//--------------------------------------------------------------------------------
// Function    : Map::Load_BGI
// Description : Load images of BGI objects and Scrolling BG
// Note        :
// Input       : None
// Output      : None
//--------------------------------------------------------------------------------
void Map::Load_BGI(){
    
    for(int k=0;k<scene_num;k++)    Scrolling_BG[k].loadFromFile(scene_image[k]);
    for(int k=0;k<map_num;k++)      BGI_object[k].loadFromFile(map_image[k]);
    for(int k=0;k<about_num;k++)    Game_Info[k].loadFromFile(about_image[k]);
}// FUNCTION : Map::Load_BGI

//--------------------------------------------------------------------------------
// Function    : Map::Load_BGM
// Description : Load BGM
// Note        :
// Input       : None
// Output      : None
//--------------------------------------------------------------------------------
void Map::Load_BGM(){
    for(int i=0;i<MUSIC;i++)BGM[i].loadmusic(music_name[i]);
}// FUNCTION : Map::Load_BGM



//--------------------------------------------------------------------------------
// Function    : Map::Map_mode
// Description : Main running function of Map of different modes in SDL loop
//               For example, mode 0 is the story background introduciton, and mode 1 is the main menu.
//               In each mode, you will need to specify the bgm, _map(background image), and icons(game characters).
//               Function render(x,y) of each private class member will place the image at position(x,y).
//               Finally, use SDL_RenderPresent( gRenderer ) to render the image to the window.                 
// Note        : 
//            1. En each mode, plese following the order of placing function:
//               private class memeber's main function-> Map's Selection_Buttons' button_reaction()->Change_Mode(or Enter_Battle_Scenario or Leave_Battle_Scenario)
//            2. mode 0 : Main Menu
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
//               bool &quit_game         : Whether to Quit
// Output      : None
//--------------------------------------------------------------------------------
void Map::Map_mode(SDL_Event &e,BATTLE_SCENE **b,bool &quit_game){
    Set_BGM();
    Set_BGI();
    switch(mode){

        //mode MAIN_MENU_MODE : Main Menu
        case MAIN_MENU_MODE:
            for(int i=0;i<menu_num-2;i++){
                Menu_Button[i].menu_button_reaction(e,mode);
                Change_Mode(mode,MAIN_MENU_MODE,maple,NULL);
            }//for(int i=0;i<menu_num-2;i++)
            
        break;//case MAIN_MENU_MODE

        //mode BIG_MAP_MODE : Big Map to Choose Battle Scenarios
        case BIG_MAP_MODE:
        
            Map_Button[gomenu].map_button_reaction(e,mode);
            Map_Button[Scenario_Num].map_button_reaction(e,mode);
            Enter_Battle_Scenario(mode,b,Scenario_Num);
            Back_to_Main_Menu(mode);
                        
        break;//case BIG_MAP_MODE

        //mode BATTLE_SCENARIO_MODE : Different Battle Scenarios
        case BATTLE_SCENARIO_MODE:
            
            //b[Scenario_Num][0].battle(e,mode);
            //if(Scenario_Num>=3)Map_Button[skip].map_button_reaction(e,mode);
            Leave_Battle_Scenario(Into_Battle,mode,Scenario_Num);
            
        break;//case BATTLE_SCENARIO_MODE

        //mode TUTORIAL_MODE: Tutorial
        case TUTORIAL_MODE:
            tutorial_guide->teach(&e);
            Map_Button[gomenu].map_button_reaction(e,mode);
            Change_Mode(mode,TUTORIAL_MODE,bar,NULL); 
            
        break;//case TUTORIAL_MODE

        //mode GAME_INFORMATION_MODE: Game Information
        case GAME_INFORMATION_MODE:
            Map_Button[gomenu].map_button_reaction(e,mode);
            Change_Mode(mode,MAIN_MENU_MODE,-1,&Game_Info[0]);             
        break;//case GAME_INFORMATION_MODE
                
        //mode START_SCENE_MODE: Start Scene
        case START_SCENE_MODE:
            mode=MAIN_MENU_MODE;
        break;//case START_SCENE_MODE

        //mode BACKGROUND_INTRO_MODE: Background Introduction
        case BACKGROUND_INTRO_MODE://
            Map_Button[teacher].map_button_reaction(e,mode);
            Change_Mode(mode,BACKGROUND_INTRO_MODE,teacher1,&Scrolling_BG[1]);             
        break;//case BACKGROUND_INTRO_MODE
        
        //mode FINISH_SCENE_MODE: Game Finish Scene
        case FINISH_SCENE_MODE:
            for(int i=3;i<menu_num;i++){
                Menu_Button[i].menu_button_reaction(e,mode);
                Change_Mode(mode,FINISH_SCENE_MODE,sorrow,NULL);        
            }//for(int i=3;i<menu_num;i++)
            
        break;//case FINISH_SCENE_MODE
        
        //mode QUIT_GAME_MODE: Quit Game
        case QUIT_GAME_MODE:
            quit_game=true;
        break;//case QUIT_GAME_MODE

    }//switch(mode)
    SDL_RenderPresent( gRenderer );
    SDL_RenderClear( gRenderer );
    
    return;
}//// FUNCTION : Map::Map_mode

void Map::Set_BGM(){
    switch(mode){

            //mode MAIN_MENU_MODE : Main Menu
        case MAIN_MENU_MODE:
            BGM[maple].playmusic();
        break;//case MAIN_MENU_MODE

        //mode BIG_MAP_MODE : Big Map to Choose Battle Scenarios
        case BIG_MAP_MODE:
            BGM[village].playmusic();
        break;//case BIG_MAP_MODE

        //mode BATTLE_SCENARIO_MODE : Different Battle Scenarios
        case BATTLE_SCENARIO_MODE:
            BGM[(Scenario_Num)%3+2].playmusic();
        break;//case BATTLE_SCENARIO_MODE

        //mode TUTORIAL_MODE: Tutorial
        case TUTORIAL_MODE:
            BGM[bar].playmusic();
        break;//case TUTORIAL_MODE

        //mode GAME_INFORMATION_MODE: Game Information
        case GAME_INFORMATION_MODE:
        break;//case GAME_INFORMATION_MODE
                
        //mode START_SCENE_MODE: Start Scene
        case START_SCENE_MODE:
        break;//case START_SCENE_MODE

        //mode BACKGROUND_INTRO_MODE: Background Introduction
        case BACKGROUND_INTRO_MODE://
            BGM[teacher1].playmusic();
        break;//case BACKGROUND_INTRO_MODE
        
        //mode FINISH_SCENE_MODE: Game Finish Scene
        case FINISH_SCENE_MODE:
            BGM[sorrow].playmusic();
        break;//case FINISH_SCENE_MODE
        
        //mode QUIT_GAME_MODE: Quit Game
        case QUIT_GAME_MODE:
        break;//case QUIT_GAME_MODE

    }//switch(mode)
    return;
}

void Map::Set_BGI(){
    switch(mode){

        //mode MAIN_MENU_MODE : Main Menu
        case MAIN_MENU_MODE:
            Scrolling_BG[0].scroll(1,0,1);
            BGI_object[title].render(340,25);
            BGI_object[version].render(1138,613);
        break;//case MAIN_MENU_MODE

        //mode BIG_MAP_MODE : Big Map to Choose Battle Scenarios
        case BIG_MAP_MODE:
            BGI_object[bigmap].render(0,0);
            for(int i=0;i<icon_n-3;i++){
                if(played[i]){
                    Map_Button[i].map_button_showup(played[i]);
                }
            }//for(int i=0;i<icon_n;i++)
        break;//case BIG_MAP_MODE

        //mode BATTLE_SCENARIO_MODE : Different Battle Scenarios
        case BATTLE_SCENARIO_MODE:
        break;//case BATTLE_SCENARIO_MODE

        //mode TUTORIAL_MODE: Tutorial
        case TUTORIAL_MODE:
        break;//case TUTORIAL_MODE

        //mode GAME_INFORMATION_MODE: Game Information
        case GAME_INFORMATION_MODE:
            Game_Info[0].scroll(0,1,0);            
        break;//case GAME_INFORMATION_MODE
                
        //mode START_SCENE_MODE: Start Scene
        case START_SCENE_MODE:
            for(int t=0;t<256;t++){
                BGI_object[black].render(0,0);
                BGI_object[brand].setAlpha(t);
                BGI_object[brand].render(206,270);
                t++;
                SDL_RenderPresent( gRenderer );
            }//for(int t=0;t<256;t++)
            for(int t=255;t>0;t--){
                BGI_object[black].render(0,0);
                BGI_object[brand].setAlpha(t);
                BGI_object[brand].render(206,270);
                t--;
                SDL_RenderPresent( gRenderer );
            }//for(int t=255;t>0;t--)
            
        break;//case START_SCENE_MODE

        //mode BACKGROUND_INTRO_MODE: Background Introduction
        case BACKGROUND_INTRO_MODE://
            Scrolling_BG[1].scroll(0,1,0);
            BGM[teacher1].playmusic();
        break;//case BACKGROUND_INTRO_MODE
        
        //mode FINISH_SCENE_MODE: Game Finish Scene
        case FINISH_SCENE_MODE:
            Scrolling_BG[0].scroll(1,0,1);
            BGI_object[finish].render(340,25);
            
        break;//case FINISH_SCENE_MODE
        
        //mode QUIT_GAME_MODE: Quit Game
        case QUIT_GAME_MODE:
            
        break;//case QUIT_GAME_MODE

    }//switch(mode)
    return;
}

void Map::Change_Mode(const int mode_in,const int mode_present,const int bgm_name,Change_scene* Scene){
    if(mode_in!=mode_present){
        if(bgm_name>=0)BGM[bgm_name].stopmusic();
        SDL_Delay(20);
        if(Scene!=NULL)Scene->offsety=0;
    }//if(mode_in!=mode_present)
}

void Map::Enter_Battle_Scenario(const int mode_in,BATTLE_SCENE **b, const int scenario_num){
    if(mode_in==BATTLE_SCENARIO_MODE){
        played[scenario_num] = 1;

        //b[scenario_num]=new BATTLE_SCENE(scenario_num%3);
        BGM[village].stopmusic();
        SDL_Delay(20);

        Into_Battle = true;
    }//if(mode_in==BATTLE_SCENARIO_MODE)
}
void Map::Back_to_Main_Menu(const int mode_in){
    if(mode_in==MAIN_MENU_MODE){
        BGM[village].stopmusic();
        SDL_Delay(20);
    }//if(mode_in==BATTLE_SCENARIO_MODE)
}

void Map::Leave_Battle_Scenario(const bool into_battle,int& mode_in, int& scenario_num){
    if(!into_battle){
        #ifdef DEBUG
        printf("%d\n",scenario_num);
        #endif
        //Map_Button[scenario_num].clean=0;
        BGM[(scenario_num)%3+2].stopmusic();
        SDL_Delay(20);
        if(scenario_num==2){
            mode_in = FINISH_SCENE_MODE;
        }//if(scenario_num==2)
        else if(scenario_num==11){
            quit_game=true;
        }//if(scenario_num==11)
        else{
            mode_in = BIG_MAP_MODE;
        }

        scenario_num++;
    }//if(!into_battle)
}



