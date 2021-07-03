#include "Battle_Scenario.h"
Battle_Scenario::Battle_Scenario()
{

}
Battle_Scenario::~Battle_Scenario()
{

}

void Battle_Scenario::initialize(int category){
    //Load BGI
    Battle_Ground_Image.loadFromFile(Battle_Ground_Image_Filename[category%3]);
    White_Hexagonal.loadFromFile("image/whiteloop.png");
    Major_Camp.loadFromFile("image/king.png");
    Victory_Sign.loadFromFile("image/victory.png");
    Defeat_Sign.loadFromFile("image/defeat.png");

    //Initialize Buttons
    Next_Turn_Button.Initialize(X_NEXT,Y_NEXT,MY_MODE_DEFAULT,FOE_MODE_DEFAULT,"image/next_turn.png");
    Exit_Button.Initialize(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-25,true,"image/exit.png");

    int count=0;
    int SHIFT_X = (X_DIS-X_UNIT)/2,SHIFT_Y = (Y_DIS-Y_UNIT)/2;
	for(int a=0;a<x_num;a++){
        for(int b=0;b<y_num-(a+1)%2;b++){
            Human_Character_Button[count].Initialize(a*X_DIS+X_INIT +SHIFT_X, b*Y_DIS+Y_INIT+Y_DIS*((a+1)%2)/2 +SHIFT_Y,MY_MODE_ACTION,"image/whiteloop.png");
            Human_Action_Button[count].Initialize(a*X_DIS+X_INIT +SHIFT_X, b*Y_DIS+Y_INIT+Y_DIS*((a+1)%2)/2 +SHIFT_Y,MY_MODE_DEFAULT,"image/whiteloop.png");

            Duck_Character_Button[count].Initialize(a*X_DIS+X_INIT +SHIFT_X, b*Y_DIS+Y_INIT+Y_DIS*((a+1)%2)/2 +SHIFT_Y,FOE_MODE_ACTION,"image/whiteloop.png");
            Duck_Action_Button[count].Initialize(a*X_DIS+X_INIT +SHIFT_X, b*Y_DIS+Y_INIT+Y_DIS*((a+1)%2)/2 +SHIFT_Y,FOE_MODE_DEFAULT,"image/whiteloop.png");
            count++;
        }//for(int b=0;b<y_num-(a+1)%2;b++)
	}//for(int a=0;a<x_num;a++)

    //Initialize Soldiers
    #ifdef DEBUG
    human_num = 6;
    duck_num = 6;

    const int pos_list_human[human_num]={28,29,36,27,24,25};
    const int move_ab_list_human[human_num] = {1,1,1,1,1,1};
    const int health_list_human[human_num] = {100,100,100,100,100,100};
    const int attack_list_human[human_num] = {30,30,30,20,50,50};
    const int type_list_human[human_num] = {MELEE,MELEE,ARCHER,ARCHER,AIRFORCE,AIRFORCE};
    const int range_list_human[human_num] = {0,0,2,2,0,0};
    const string human_pic[human_num]= {"image/human/human1.png","image/human/human1.png","image/human/shooter.png",
                                        "image/human/shooter.png","image/human/fly.png","image/human/fly.png"};
    

    const int pos_list_duck[duck_num]={30,31,32,35,34,37};
    const int move_ab_list_duck[duck_num] = {1,1,1,1,1,1};
    const int health_list_duck[duck_num] = {100,100,100,100,100,100};
    const int attack_list_duck[duck_num] = {30,30,30,20,20,20};
    const int type_list_duck[duck_num] = {MELEE,MELEE,MELEE,ARCHER,ARCHER,ARCHER};
    const int range_list_duck[duck_num] = {0,0,0,2,2,2};
    const string duck_pic[duck_num]= {"image/character/black_swan.png","image/character/black_swan.png","image/character/black_swan.png",
                                        "image/character/swan.png","image/character/swan.png","image/character/swan.png",};
    
    Human_Army = new Soldier*[human_num];
    Duck_Army = new Soldier*[duck_num];

    for(int i=0;i<human_num;i++){
        Human_Army[i] = new Soldier;
        Human_Army[i]->Initialize(i,MINE_ID,pos_list_human[i],move_ab_list_human[i],health_list_human[i],attack_list_human[i],type_list_human[i],range_list_human[i],human_pic[i]);
    }//for(int i=0;i<human_num;i++)

    for(int i=0;i<duck_num;i++){
        Duck_Army[i] = new Soldier;
        Duck_Army[i]->Initialize(i,FOE_ID,pos_list_duck[i],move_ab_list_duck[i],health_list_duck[i],attack_list_duck[i],type_list_duck[i],range_list_duck[i], duck_pic[i]);
    }//for(int i=0;i<human_num;i++)
    cout<<"safe"<<endl;
    #endif

    //Initialize tile information //Must be put behind initialize soldiers
    initialize_map_info(Human_Army,Duck_Army,human_num,duck_num);

}//Function: void Battle_Scenario::initialize

void Battle_Scenario::battle(SDL_Event &e,bool &quit){
    Battle_Ground_Image.render(0,0);
    int count = 0;
    for(int a=0;a<x_num;a++){
        for(int b=0;b<y_num-(a+1)%2;b++){
            if(info.allow_pass[count]) White_Hexagonal.render(a*X_DIS+X_INIT, b*Y_DIS+Y_INIT+Y_DIS*((a+1)%2)/2);
            count++;
        }//for(int b=0;b<y_num-(a+1)%2;b++)
	}//for(int a=0;a<x_num;a++)

    for(int i=0;i<human_num;i++){
        if(Human_Army[i]!=NULL) Human_Army[i]->render();
    }//for(int i=0;i<human_num;i++)

    for(int i=0;i<duck_num;i++){
        if(Duck_Army[i]!=NULL) Duck_Army[i]->render();
    }//for(int i=0;i<human_num;i++)

    //Major_Camp.loadFromFile("image/whiteloop.png");
    //Victory_Sign.loadFromFile("image/victory.png");
    //Defeat_Sign.loadFromFile("image/defeat.png");



    switch(mode){
        case MY_MODE_DEFAULT:
        {
            // Initialize Per Turn
            Initiate_New_Turn(Change_Turn,Human_Army,human_num);

            // Activate Button Reaction
            bool activated = false;

            // Scan each character
            for(int k=0;k<tiles_num;k++){
                if(info.side_id[k]==MINE_ID) activated = Human_Character_Button[k].character_button_reaction(e,mode);
                character_action(mode,k,action_character_pos_id,info);
                if(activated)break;
            }//for(int k=0;k<tiles_num;k++)

            Change_Turn = Next_Turn_Button.next_turn_button_reaction(e,mode);
            break;
        }//case MY_MODE_DEFAULT
        case MY_MODE_ACTION:
        {   
            
            bool activated=false;
            
            Action Behavior;
            for(int k=0;k<tiles_num;k++){
                if(info.action_move[k]) activated = Human_Action_Button[k].action_move_button_reaction(e,mode);
                if(info.action_attack[k]) activated = Human_Action_Button[k].action_attack_button_reaction(e,mode);
                if(activated){
                    Behavior.target_pos_id = k;
                    if(info.action_move[k]) Behavior.action_type = MOVE_TO_NEIGHBOR;
                    if(info.action_attack[k]) Behavior.action_type = ATTACK_TARGET;
                    clear_map_action(info);
                    break;
                }//if(activated)
                if(k==tiles_num-1 and !activated){
                    clear_action(activated,e,mode,info);
                }
            }//for(int k=0;k<tiles_num;k++)
            
            Act(activated,info,action_character_pos_id,Behavior,Human_Army,Duck_Army);
            break;
        }//case MY_MODE_ACTION
        case FOE_MODE_DEFAULT:
        {
            Initiate_New_Turn(Change_Turn,Duck_Army,duck_num);

            // Initialize Per Turn
            

            // Activate Button Reaction
            bool activated = false;

            // Scan each character
            for(int k=0;k<tiles_num;k++){
                if(info.side_id[k]==FOE_ID) activated = Duck_Character_Button[k].character_button_reaction(e,mode);
                character_action(mode,k,action_character_pos_id,info);
                if(activated)break;
            }//for(int k=0;k<tiles_num;k++)

            Change_Turn = Next_Turn_Button.next_turn_button_reaction(e,mode);
            break;
        }//case FOE_MODE_DEFAULT
        case FOE_MODE_ACTION:
        {   
            
            bool activated=false;
            
            Action Behavior;
            for(int k=0;k<tiles_num;k++){
                if(info.action_move[k]) activated = Duck_Action_Button[k].action_move_button_reaction(e,mode);
                if(info.action_attack[k]) activated = Duck_Action_Button[k].action_attack_button_reaction(e,mode);
                if(activated){
                    Behavior.target_pos_id = k;
                    if(info.action_move[k]) Behavior.action_type = MOVE_TO_NEIGHBOR;
                    if(info.action_attack[k]) Behavior.action_type = ATTACK_TARGET;
                    clear_map_action(info);
                    break;
                }//if(activated)
                if(k==tiles_num-1 and !activated){
                    clear_action(activated,e,mode,info);
                }
            }//for(int k=0;k<tiles_num;k++)
            
            Act(activated,info,action_character_pos_id,Behavior,Duck_Army,Human_Army);
            break;
        }//case FOE_MODE_ACTION
    }//switch(mode)


}//Function: void Battle_Scenario::battle

int Battle_Scenario::adjacent_value(const int k, const int l,const map A){
    
    int return_val;
    if(l==0) return_val = k-1;
    if(l==3) return_val = k+1;
    if(l==1) return_val = k+4;
    if(l==4) return_val = k-4;
    if(l==2) return_val = k+5;
    if(l==5) return_val = k-5;

            //Boundary Issue
    if(k==0 or k==1 or k==2 or k==3){
        if(l==4) return_val = NONE_ADJACENT_ID;
        if(l==5) return_val = NONE_ADJACENT_ID;
    }
    if(k==tiles_num-1 or k==tiles_num-2 or k==tiles_num-3 or k==tiles_num-4){
        if(l==1) return_val = NONE_ADJACENT_ID;
        if(l==2) return_val = NONE_ADJACENT_ID;
    }
    if(k%9==0 and l==0) return_val = NONE_ADJACENT_ID;
    if(k%9==3 and l==3) return_val = NONE_ADJACENT_ID;
    if(k%9==4){
        if(l==0) return_val = NONE_ADJACENT_ID;
        if(l==1) return_val = NONE_ADJACENT_ID;
        if(l==5) return_val = NONE_ADJACENT_ID;
    }
    if(k%9==8){
        if(l==2) return_val = NONE_ADJACENT_ID;
        if(l==3) return_val = NONE_ADJACENT_ID;
        if(l==4) return_val = NONE_ADJACENT_ID;
    }
    return return_val;
}
void Battle_Scenario::assign_adj(const int k, map& A){
    for(int l=0;l<6;l++){
        A.adjacent_tile_id[k][l] = adjacent_value(k,l,A);
    }//for(int l=0;l<6;l++)
}
void Battle_Scenario::assign_adj2(const int k, map& A){
    for(int l=0;l<6;l++){
        const int neighbor_id = adjacent_value(k,l,A);
        if(neighbor_id>=0){
            A.adjacent2_tile_id[k][2*l]   = adjacent_value(neighbor_id,l,A);
            A.adjacent2_tile_id[k][2*l+1] = adjacent_value(neighbor_id,(l+1)%6,A);
        }
        else{
            A.adjacent2_tile_id[k][2*l]   = NONE_ADJACENT_ID;
            A.adjacent2_tile_id[k][2*l+1] = NONE_ADJACENT_ID;
        }
    }
}
void Battle_Scenario::initialize_map_info(Soldier**mine, Soldier**foes,const int h_num,const int d_num){
    //Mind the order of the loops
    for(int k=0;k<tiles_num;k++)
    {
        info.side_id[k] = NONE_ID;
        info.personal_id[k] = NONE_ID;
        info.allow_pass[k] = true;

        info.action_move[k] = false;
        info.action_attack[k] = false;

    }
    for(int k=0;k<tiles_num;k++)
    {
        //Adjacent Tiles ID
        assign_adj(k,info);
        assign_adj2(k,info);
    }
    for(int k=0;k<tiles_num;k++)
    {
        //Map Specific Setting
        #ifdef DEBUG
        if(k==tiles_num-1) info.allow_pass[k] = false;

        for(int i=0;i<h_num;i++){
            if(mine[i]!=NULL){
                if(k==mine[i]->get_pos()){
                    info.side_id[k] = MINE_ID;
                    info.personal_id[k] = i;
                }//if(k==mine[i]->get_pos())
            }//if(mine[i]!=NULL)
        }//for(int i=0;i<h_num;i++)
        for(int i=0;i<d_num;i++){
            if(foes[i]!=NULL){
                if(k==foes[i]->get_pos()){
                    info.side_id[k] = FOE_ID;
                    info.personal_id[k] = i;
                }//if(k==foes[i]->get_pos())
            }//if(foes[i]!=NULL)
        }//for(int i=0;i<d_num;i++)
        
        #endif
    }
    erase_prohibited_area(info);
    
}


void Battle_Scenario::character_action(const int mode_in,const int id_in,int& character_pos_id,map& A){
    if(mode_in==MY_MODE_ACTION or mode_in==FOE_MODE_ACTION){
        character_pos_id = id_in;
        action_advisor(id_in,A);
    }
    return;
}//FUNCTION: void Battle_Scenario::character_action

void Battle_Scenario::action_advisor(const int pos_id,map& A){
    
    for(int l=0;l<6;l++){
        const int self_id = A.personal_id[pos_id];
        const int self_side = A.side_id[pos_id];
        int target_pos = A.adjacent_tile_id[pos_id][l];

        bool actionable;
        Soldier* one;
        if(self_side==MINE_ID) one = Human_Army[self_id];
        else if(self_side==FOE_ID) one = Duck_Army[self_id];
        actionable = one->actionable();

        //Any Type of Soldiers
        if(target_pos>=0 and actionable){
            if(A.side_id[target_pos] == NONE_ID)A.action_move[target_pos] = true;
            else if(self_side==MINE_ID and A.side_id[target_pos] == FOE_ID)A.action_attack[target_pos] = true;
            else if(self_side==FOE_ID and A.side_id[target_pos] == MINE_ID)A.action_attack[target_pos] = true;
        }//if(target_pos>=0 and actionable)

        //Archer
        if(actionable and one->get_range()>=2){
            if(A.adjacent2_tile_id[pos_id][2*l] >= 0){
                target_pos = A.adjacent2_tile_id[pos_id][2*l];
                if(self_side==MINE_ID and A.side_id[target_pos] == FOE_ID)A.action_attack[target_pos] = true;
                else if(self_side==FOE_ID and A.side_id[target_pos] == MINE_ID)A.action_attack[target_pos] = true;
            }
            if(A.adjacent2_tile_id[pos_id][2*l+1] >= 0){
                target_pos = A.adjacent2_tile_id[pos_id][2*l+1];
                if(self_side==MINE_ID and A.side_id[target_pos] == FOE_ID)A.action_attack[target_pos] = true;
                else if(self_side==FOE_ID and A.side_id[target_pos] == MINE_ID)A.action_attack[target_pos] = true;
            }
        }//if(target_pos>=0 and actionable)

        //Airforce
        if(actionable and one->get_type()==AIRFORCE){
            for (int pos=0;pos<tiles_num;pos++){
                if(self_side==MINE_ID and A.side_id[pos] == FOE_ID)A.action_attack[pos] = true;
                else if(self_side==FOE_ID and A.side_id[pos] == MINE_ID)A.action_attack[pos] = true;

                // Airforce cannot move by foot
                if(A.side_id[pos] == NONE_ID)A.action_move[target_pos] = false;
            }
            
        }//if(target_pos>=0 and actionable)

    }//for(int l=0;l<6;l++)
    return;
}//FUNCTION: void Battle_Scenario::action_advisor

void Battle_Scenario::clear_map_action(map& A){
    for(int k=0;k<tiles_num;k++){
        A.action_move[k] = false;
        A.action_attack[k] = false;
    }
}//FUNCTION: void Battle_Scenario::clear_map_action

void Battle_Scenario::erase_prohibited_area(map& A){
    for(int k=0;k<tiles_num;k++){
        for(int l=0;l<6;l++){
            const int adj_idx = A.adjacent_tile_id[k][l];
            if(!A.allow_pass[adj_idx])A.adjacent_tile_id[k][l] = NONE_ADJACENT_ID;
        }//for(int l=0;l<6;l++)
        for(int l=0;l<12;l++){
            const int adj2_idx = A.adjacent2_tile_id[k][l];
            if(!A.allow_pass[adj2_idx])A.adjacent2_tile_id[k][l] = NONE_ADJACENT_ID;
        }//for(int l=0;l<12;l++){
    }//for(int k=0;k<tiles_num;k++)
}//FUNCTION: void Battle_Scenario::clear_map_action

void Battle_Scenario::clear_action(const bool activated, SDL_Event &e, int& mode_in,map& A){
    if(e.type ==SDL_MOUSEBUTTONDOWN){
        clicked_once = true;
    }
    if(e.type ==SDL_MOUSEBUTTONUP and clicked_once){
        clicked_once_done = true;
        clicked_once = false;
    }
    if(e.type ==SDL_MOUSEBUTTONDOWN and clicked_once_done){
        clicked_twice = true;
        clicked_once_done = false;
    }
    if(!activated and e.type ==SDL_MOUSEBUTTONUP and clicked_twice){
        clicked_twice = false;
        cout<<"Clear!"<<endl;
        clear_map_action(A);
        if(mode_in == MY_MODE_ACTION) mode_in = MY_MODE_DEFAULT;
        else if(mode_in == FOE_MODE_ACTION) mode_in = FOE_MODE_DEFAULT;
    }
    
}//FUNCTION: void Battle_Scenario::clear_action

void Battle_Scenario::Act(const bool activated,map& A,const int character_pos_id,const Action action,Soldier** mine,Soldier** foes){
    if(activated){
        
        int mine_id = A.personal_id[character_pos_id];
        int foe_id = A.personal_id[action.target_pos_id];

        // Move Case
        if(action.action_type==MOVE_TO_NEIGHBOR){
            if(mine[mine_id]!=NULL)mine[mine_id]->move(action.target_pos_id,A);
            cout<<"Move"<<endl;
        } 

        // Attack Case
        else if(action.action_type==ATTACK_TARGET){
            if(mine[mine_id]!=NULL){
                mine[mine_id]->attack(action.target_pos_id,A,foes);
                if(mine[mine_id]->get_side()==MINE_ID) Human_Action_Button[character_pos_id].playsound(1);
                else if(mine[mine_id]->get_side()==FOE_ID) Human_Action_Button[character_pos_id].playsound(2);
            }
            cout<<"Chicken Attack"<<endl;
        } 
        
        // Post Process
        clicked_once = false;
        clicked_once_done = false;
        clicked_twice = false;
        if(mode == MY_MODE_ACTION) mode = MY_MODE_DEFAULT;
        else if(mode == FOE_MODE_ACTION) mode = FOE_MODE_DEFAULT;
    }
}//FUNCTION: void Battle_Scenario::Act

void Battle_Scenario::Initiate_New_Turn(bool& change,Soldier** army,const int num){
    if(change){
        change = false;

        for(int i=0;i<num;i++){
            cout<<"id:"<<i<<endl;
            if(army[i]!=NULL)army[i]->initialize_perturn();
        }
    }
}//FUNCTION: void Battle_Scenario::Initiate_New_Turn