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
    l_x=x;l_y=y;mode=z;
}
void Selection_Button::set_value(int x,int y,int m1,int m2){
    l_x=x;l_y=y;mode1=m1;mode2=m2;
}

void Selection_Button::map_button_reaction(SDL_Event &a,int &mode_in){
    
    handleEvent(&a);
    setPosition(l_x,l_y);
    setdim(mWidth,mHeight);
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        render(l_x,l_y);
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        sound[0].playsound();
        mode_in=mode;
        return;
    }
    else render(l_x,l_y,0.9,0.9);
    return;
}

void Selection_Button::menu_button_reaction(SDL_Event &a,int &mode_in){
    handleEvent(&a);
    setPosition(l_x,l_y);
    setdim(mWidth,mHeight);
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        setColor(255,255,100);
        render(l_x,l_y);
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        sound[0].playsound();
        mode_in=mode;
        return;
    }
    else {setColor(255,255,255);render(l_x,l_y);}
    return;
}
//setColor(255,255,0); //light yellow
bool Selection_Button::character_button_reaction(SDL_Event &e,int &mode_in){
    setdim(X_UNIT,Y_UNIT);
    handleEvent(&e);

    setPosition(l_x,l_y);
    setdim(X_DIS,Y_DIS);
    
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(255,255,0); //light yellow
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(255,255,0); //light yellow
        clicked = true;
        
    }
    else if(clicked and get_sprite()==BUTTON_SPRITE_MOUSE_UP){
        clicked = false;
        sound[0].playsound();
        mode_in=mode;
        return true;
    }
    else{
        clicked = false;
    }
    return false;
}

bool Selection_Button::action_move_button_reaction(SDL_Event &e,int &mode_in){
    setdim(X_UNIT,Y_UNIT);
    handleEvent(&e);

    setPosition(l_x,l_y);
    setdim(X_DIS,Y_DIS);
    
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(0,255,255); //light blue
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(0,255,255); //light blue
        clicked = true;
        
    }
    else if(clicked and get_sprite()==BUTTON_SPRITE_MOUSE_UP){
        clicked = false;
        sound[0].playsound();
        mode_in=mode;
        return true;
    }
    else{
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(0,255,0); //light green
    }
    return false;
}

bool Selection_Button::action_attack_button_reaction(SDL_Event &e,int &mode_in){
    setdim(X_UNIT,Y_UNIT);
    handleEvent(&e);

    setPosition(l_x,l_y);
    setdim(X_DIS,Y_DIS);
    
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(0,255,255); //light blue
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(0,255,255); //light blue
        clicked = true;
        
    }
    else if(clicked and get_sprite()==BUTTON_SPRITE_MOUSE_UP){
        clicked = false;
        sound[0].playsound();
        mode_in=mode;
        return true;
    }
    else{
        clicked = false;
        int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
        render(l_x-SHIFT_X,l_y-SHIFT_Y);
        setColor(255,0,0); //light red
    }
    return false;
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

bool Selection_Button::next_turn_button_reaction(SDL_Event &e,int &mode_in){
    
    handleEvent(&e);
    setPosition(l_x,l_y);
    setdim(mWidth,mHeight);

    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        clicked = false;
        render(l_x,l_y);

    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        render(l_x,l_y);
        clicked = true;
        
    }
    else if(clicked and get_sprite()==BUTTON_SPRITE_MOUSE_UP){
        clicked = false;
        render(l_x,l_y);
        sound[0].playsound();
        SDL_Delay(200);
        if(mode_in==mode1) mode_in=mode2;
        else if(mode_in==mode2) mode_in=mode1;
        return true;
    }
    else{
        clicked = false;
        render(l_x,l_y);
    }
    return false;
}

void Selection_Button::Initialize(const int x,const int y,const int mode, string image_filename){
    this->set_value(x,y,mode);
    this->load_soundtrack();
    this->loadFromFile(image_filename); 
}// FUNCTION : Selection_Button::Initialize_Selection_Button

void Selection_Button::Initialize(const int x,const int y,const int mode1_in,const int mode2_in, string image_filename){
    this->set_value(x,y,mode1_in,mode2_in);
    this->load_soundtrack();
    this->loadFromFile(image_filename); 
}// FUNCTION : Selection_Button::Initialize_Selection_Button

void Selection_Button::Initialize(const int x,const int y, const int width, const int height,const int mode, string image_filename){
    this->set_value(x,y,mode);
    this->load_soundtrack();
    this->loadFromFile(image_filename); 
    this->mWidth = width;
    this->mHeight = height;
}// FUNCTION : Selection_Button::Initialize_Selection_Button

void Selection_Button::load_soundtrack(){
    for(int i=0;i<SOUND;i++)sound[i].loadsound(sound_name[i]);
}
