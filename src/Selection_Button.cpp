#include "Selection_Button.h"
#include "iostream"

Selection_Button::Selection_Button()
{

}

Selection_Button::~Selection_Button()
{
    //dtor
}

void Selection_Button::set_value(int x,int y,int z){
    l_x=x;l_y=y;k=z;
}

void Selection_Button::map_button_reaction(SDL_Event &a,int &mode){
    if(clean){
        handleEvent(&a);
        setPosition(l_x,l_y);
        setdim(mWidth,mHeight);
        if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            render(l_x,l_y);
        }
        else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            sound[0].playsound();
            mode=k;
            return;
        }
        else render(l_x,l_y,0.9,0.9);
    }else {setColor(100,100,100);render(l_x,l_y);}
return;
}

void Selection_Button::menu_button_reaction(SDL_Event &a,int &mode){
    handleEvent(&a);
    setPosition(l_x,l_y);
    setdim(mWidth,mHeight);
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        setColor(255,255,100);
        render(l_x,l_y);
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        sound[0].playsound();
        mode=k;
        return;
    }
    else {setColor(255,255,255);render(l_x,l_y);}
    return;
}

void Selection_Button::map_button_showup(bool played){

    if(!played){
        
        setPosition(l_x,l_y);
        setdim(mWidth,mHeight);
        render(l_x,l_y,0.9,0.9);
    }
    else{
        setColor(100,100,100);
        setPosition(l_x,l_y);
        setdim(mWidth,mHeight);
        render(l_x,l_y,0.9,0.9);
    }
return;
}

void Selection_Button::load_soundtrack(){
    for(int i=0;i<SOUND;i++)sound[i].loadsound(sound_name[i]);
}
