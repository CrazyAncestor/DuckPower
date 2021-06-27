#define _GLIBCXX_USE_CXX11_ABI 0
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
        friend class Map;
    protected:

    private:
        music sound[SOUND];
        int l_x,l_y,k;
        bool clean =true;
        void set_value(int,int,int);
        void map_button_reaction(SDL_Event &a,int &mode);
        void menu_button_reaction(SDL_Event &a,int &mode);

        void map_button_showup(bool played);

        void load_soundtrack();


};

#endif // SELECTION_BUTTON_H
