#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef BATTLE_SCENARIO_H
#define BATTLE_SCENARIO_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<loop.h>
#include<LTexture.h>
#include<LButton.h>
#include<men_with_arms.h>
#include<base.h>
#include<Selection_Button.h>
#include<music.h>
#include<GO_JUDGER.h>
#include<Soldier.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include<ctime>
#include "definition.h"
#ifdef DEBUG
#include<cstdlib>
#endif


const string Battle_Ground_Image_Filename[3]={
    "image/field/field01.png",
    "image/field/field02.png",
    "image/field/field03.png"
};


enum battle_scenario_mode{
    MY_MODE_DEFAULT = 0,
    MY_MODE_ACTION = 1,
    FOE_MODE_DEFAULT = 2,
    FOE_MODE_ACTION = 3,
    LEAVE_BATTLE_MODE = 4,
};
enum action_type_name{
    DO_NOTHING = -1,
    MOVE_TO_NEIGHBOR = 0,
    ATTACK_TARGET = 1,
    
};
struct Action{
    int action_type;
    int target_pos_id;
};


class Battle_Scenario
{
    public:
        Battle_Scenario();
        Battle_Scenario(int category);
        virtual ~Battle_Scenario();

        // Main Function
        void battle(SDL_Event &e,bool &quit);
        void initialize(int);

    private:
        LTexture Battle_Ground_Image;
        LTexture White_Hexagonal;
        LTexture Major_Camp;
        LTexture Victory_Sign;
        LTexture Defeat_Sign;

        Selection_Button Next_Turn_Button;
        Selection_Button Exit_Button;

        Selection_Button Human_Character_Button[tiles_num];
        Selection_Button Human_Action_Button[tiles_num];

        Selection_Button Duck_Character_Button[tiles_num];
        Selection_Button Duck_Action_Button[tiles_num];

        map info;
        
        Soldier **Human_Army;
        Soldier **Duck_Army;

        // Modes and Button Parameters
        int mode = MY_MODE_DEFAULT;
        bool Change_Turn = false;
        int action_character_pos_id=-1;

        bool clicked_once=false;
        bool clicked_once_done=false;
        bool clicked_twice=false;
        
        // Soldier Number
        int human_num;
        int duck_num;
    
        //Private Function
        void initialize_map_info(Soldier**mine, Soldier**foes,const int h_num,const int d_num);
        void assign_adj(const int k, map& A);
        void assign_adj2(const int k, map& A);
        int  adjacent_value(const int k, const int l,const map A);

        void character_action(const int mode_in,const int id_in,int& character_pos_id,map& A);
        void action_advisor(const int pos_id,map& A);
        void Act(const bool activated,map& A,const int character_pos_id,const Action action,Soldier** mine,Soldier** foes);
        void Initiate_New_Turn(bool& change,Soldier**army,const int num);

        void clear_map_action(map& A);
        void erase_prohibited_area(map& A);
        void clear_action(const bool activated, SDL_Event &e, int& mode,map & A);
};

#endif // BATTLE_SCENARIO_H
