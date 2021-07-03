#define _GLIBCXX_USE_CXX11_ABI 0 //Must define when using string
#ifndef SELECTION_BUTTON_H
#define SELECTION_BUTTON_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "definition.h"
#include <string>
#include<LTexture.h>
#include<LButton.h>
#include "music.h"



const string sound_name[SOUND]={
        "music/click2.wav",
       "music/nc.wav",
        "music/wan.wav"
};

enum sound_enum{
    click2=0,
    swipe=1,
};

class Selection_Button :public LTexture,public LButton
{
    public:
        //friend class Map;
        Selection_Button();
        virtual ~Selection_Button();
        //friend class Map;
        void Initialize(const int x,const int y,const int mode, string image_filename);
        void Initialize(const int x,const int y,const int mode1_in,const int mode2_in, string image_filename);
        void Initialize(const int x,const int y, const int width, const int height,const int mode, string image_filename);
                
        void map_button_reaction(SDL_Event &a,int &mode);
        void menu_button_reaction(SDL_Event &a,int &mode);

        void map_button_showup(bool played);

        bool character_button_reaction(SDL_Event &e,int &mode_in);
        bool action_move_button_reaction(SDL_Event &e,int &mode_in);
        bool action_attack_button_reaction(SDL_Event &e,int &mode_in);
        bool next_turn_button_reaction(SDL_Event &e,int &mode_in);

        void playsound(int a){
            if(a<=2)sound[a].playsound();
        }
    protected:

    private:
        music sound[SOUND];
        int l_x,l_y,mode;
        int mode1,mode2;
        void set_value(int,int,int);
        void set_value(int,int,int,int);
        void load_soundtrack();

        //Physical Parameter
        bool clicked=false;
};

#endif // SELECTION_BUTTON_H
