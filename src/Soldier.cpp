#include "Soldier.h"
Soldier::Soldier()
{

}
Soldier::~Soldier()
{

}

void Soldier::Initialize(const int pers_id,const int side_id,const int pos_id_init,const int move_ab ,const int health ,const int attack,const int type_in,const int range_in,const string pic_filename){
    personal_id = pers_id;
    personal_side = side_id;
    position_id = pos_id_init;

    move_ability = move_ab;
    move_points = move_ability;

    health_tot = health;
    health_pts = health;
    attack_pts = attack;

    type = type_in;
    range = range_in;

    Figure_Image.loadFromFile(pic_filename);
    Health_Top_Bar_Image.loadFromFile("image/bar_top.png");
    Health_Bottom_Bar_Image.loadFromFile("image/bar_bottom.png");
}//FUNCTION: void Soldier::Initialize

void Soldier::render(){
    int x_id = int(position_id/x_num)*2+int((position_id%x_num)>=4);;
    int y_id = position_id%x_num -(x_id%2)*4;
    int SHIFT_X = (X_DIS-X_UNIT)/2+20,SHIFT_Y =10;
    Figure_Image.render(x_id*X_DIS+X_INIT +SHIFT_X, y_id*Y_DIS+Y_INIT+Y_DIS*((x_id+1)%2)/2 +SHIFT_Y);
    
    // Show Health
    Health_Bottom_Bar_Image.render(x_id*X_DIS+X_INIT +SHIFT_X, y_id*Y_DIS+Y_INIT+Y_DIS*((x_id+1)%2)/2 +SHIFT_Y+100);
    double health_ratio = double(health_pts+0.0)/(health_tot+0.0);
    Health_Top_Bar_Image.render(x_id*X_DIS+X_INIT +SHIFT_X, y_id*Y_DIS+Y_INIT+Y_DIS*((x_id+1)%2)/2 +SHIFT_Y+100,health_ratio,1.0);
}//FUNCTION: void Soldier::render

void Soldier::move(const int target_pos_id,map& A){
    A.side_id[target_pos_id] = personal_side;
    A.side_id[position_id] = NONE_ID;
    
    A.personal_id[target_pos_id] = personal_id;
    A.personal_id[position_id] = NONE_ID;
    
    position_id = target_pos_id;
    move_points --;
    
}//FUNCTION: void Soldier::move

void Soldier::attack(const int target_pos_id,map& A,Soldier** Enemy){
    const int foe_id = A.personal_id[target_pos_id];
    Enemy[foe_id]->health_pts -= this->attack_pts;
    move_points =0;
    if(Enemy[foe_id]->health_pts<=0){
        delete Enemy[foe_id];
        Enemy[foe_id] = NULL;
        A.side_id[target_pos_id] = NONE_ID;
        A.personal_id[target_pos_id] = NONE_ID;
        if(type==MELEE or type ==AIRFORCE)move(target_pos_id,A);
    }
   
}//FUNCTION: void Soldier::attack

bool Soldier::actionable(){
    if(move_points>0)return true;
    else return false;
    
}//FUNCTION: bool Soldier::actionable

void Soldier::initialize_perturn(){
    move_points = move_ability;
}//FUNCTION: void Soldier::initialize_perturn