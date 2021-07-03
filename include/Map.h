#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include <BATTLE_SCENE.h>
#include <Selection_Button.h>
#include <Change_scene.h>
#include <iostream>
#include "definition.h"
#include "music.h"
#include<TUTORIAL.h>
using namespace std;

const string music_name[MUSIC]={
        "music/maple.mp3",
        "music/village.wav",
        "music/Warfare.mp3",
        "music/sao.mp3",
        "music/battle3.mp3",
        "music/bar.mp3",
        "music/teacher3.wav",
        "music/sorrow.mp3",
};
const string sound_n[SOUND1]={
        "music/teacher3.wav",
};
enum music_enum{
    maple=0,
    village=1,
    battle1=2,
    battle2=3,
    battle3=4,
    bar=5,
    teacher1=6,
    sorrow=7,
};


const string Menu_Button_Image[menu_num]={
        "image/menu/story.png",
        "image/menu/tutorial.png",
        "image/menu/about.png",
        "image/menu/conti1.png",
        "image/menu/end.png",
};
const string scene_image[scene_num]={//menu background(scroll)
        "image/menu/main41.png",
        "image/change/say3.png",
};
const string map_image[map_num]={
        "image/map/land.png",
        "image/menu/title4.png",
        "image/change/black.png",
        "image/change/brand1.png",
        "image/menu/version.png",
        "image/menu/final.png",
};

const string about_image[about_num]={
        "image/menu/about3.png",
};
const string Map_Button_Image[icon_n]={
        "image/map/icon1.png",
        "image/map/icon2.png",
        "image/map/icon3.png",
        "image/map/icon4.png",
        "image/map/icon5.png",
        "image/map/icon6.png",
        "image/map/icon7.png",
        "image/map/icon8.png",
        "image/map/icon9.png",
        "image/map/icon10.png",
        "image/map/icon11.png",
        "image/map/icon12.png",
        "image/map/skip1.png",
        "image/map/return1.png",
        "image/change/teacher.png",
};
enum Mode_Name{
    MAIN_MENU_MODE           =0,
    BIG_MAP_MODE             =1,
    BATTLE_SCENARIO_MODE     =2,
    TUTORIAL_MODE            =11,
    GAME_INFORMATION_MODE    =12,
    START_SCENE_MODE         =13,
    BACKGROUND_INTRO_MODE    =14,
    FINISH_SCENE_MODE        =15,
    QUIT_GAME_MODE           =16,
};
enum chan_name{

};
enum map_name{
    bigmap=0,
    title=1,
    black=2,
    brand=3,
    version=4,
    finish=5,
};
enum Selection_Button_Name{
    icon1=0,
    icon2=1,
    icon3=2,
    icon4=3,
    icon5=4,
    icon6=5,
    icon7=6,
    icon8=7,
    icon9=8,
    icon10=9,
    icon11=10,
    icon12=11,
    skip  =12,
    gomenu=13,
    teacher=14,
};

const int Map_Button_x[icon_n]={160,140,300,410,610,800,900,1040,1130,1025,920,610,SCREEN_WIDTH-203,0,1079};
const int Map_Button_y[icon_n]={110,220,480,390,420,450,350,300,200,100,150,165,590,0,388};
const int Menu_Button_x[menu_num]={440,440,440,440,440};
const int Menu_Button_y[menu_num]={300,400,500,400,500};
const int Map_Button_Mode[icon_n]={2,2,2,2,2,2,2,2,2,2,2,2,1,0,1};
const int Menu_Button_Mode[menu_num]={14,11,12,1,16};

class Map
{

    public:

        Map();
        virtual ~Map();
        bool quit_game;
        friend class Selection_Button;
        friend int get_mode();
        void Map_init();
        void Map_mode(SDL_Event &e,BATTLE_SCENE **b,bool &quit_game);

        bool Into_Battle=false;
        
        int Scenario_Num=0;

    private:
        //Background Image (BGI) Object
        LTexture BGI_object[map_num];

        //Selection Button
        Selection_Button Map_Button[icon_n];
        Selection_Button Menu_Button[menu_num];

        //Scrolling Background
        Change_scene Scrolling_BG[scene_num];
        Change_scene Game_Info[about_num];

        //Background Music
        music BGM[MUSIC];

        //Tutorial Class
        TUTORIAL *tutorial_guide;

        //Others
        void Load_BGI();
        void Load_BGM();
        

        void Set_BGI();
        void Set_BGM();
        void Change_Mode(const int mode_in,const int mode_present,const int bgm_name,Change_scene* Scene);
        void Enter_Battle_Scenario(const int mode_in,BATTLE_SCENE **b, const int scenario_num);
        void Leave_Battle_Scenario(const bool into_battle,int& mode_in, int& scenario_num);
        void Back_to_Main_Menu(const int mode_in);
        
        bool played[12]={0,0,0,0,0,0,0,0,0,0,0,0};
        
        
        
        bool Enforce_Battle_Deletion=false;
        int  mode=13;



};

#endif // MAP_H
