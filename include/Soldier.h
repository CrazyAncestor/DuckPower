#define _GLIBCXX_USE_CXX11_ABI 0 //Must define when using string
#ifndef HUMAN_ARMY_H
#define HUMAN_ARMY_H
#include<definition.h>
#include<LTexture.h>
#include <string>
using namespace std;
enum map_side_id{
    MINE_ID = 1,
    FOE_ID  = -1,
    NONE_ID = 0
};
enum map_allow_pass{
    ALLOW = true,
    PROHIBIT  = false,
};
enum map_adjacent_tile_id{
    NONE_ADJACENT_ID = -1
};
enum soldier_type{
    MELEE = 0,
    ARCHER = 1,
    AIRFORCE = 2,
};
struct map{
    bool allow_pass[tiles_num];
    int side_id[tiles_num];
    int personal_id[tiles_num];

    bool action_move[tiles_num];
    bool action_attack[tiles_num];
    
    int adjacent_tile_id[tiles_num][6];
    int adjacent2_tile_id[tiles_num][12];
};
class Soldier
{
    public:
        Soldier();
        virtual ~Soldier();
        
        void Initialize(const int pers_id,const int side_id,const int pos_id_init,const int move_ab,const int health,const int attack,const int type_in,const int range_in,const string pic_filename);
        
        void render(); //Render on the window
        void initialize_perturn();

        bool actionable();
        int get_pos(){ return position_id; }        
        int get_type(){ return type; }  
        int get_range(){ return range; }  
        
        void move(const int target_pos_id,map& A);
        void attack(const int target_pos_id,map& A,Soldier** Enemy);

        #ifdef DEBUG
        int get_side(){
            return personal_side;
        }
        #endif
    protected:

    private:
        // Figure Image
        LTexture Figure_Image;
        LTexture Health_Top_Bar_Image;
        LTexture Health_Bottom_Bar_Image;

        // Position and Identity
        int personal_id;
        int personal_side;
        int position_id;
        
        int move_ability;
        int move_points;

        // Health and Attack
        int health_tot;
        int health_pts;
        int attack_pts;

        int type;
        int range;

};
#endif // HUMAN_ARMY_H
