#ifndef DEFINITION_H
#define DEFINITION_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
/*****main*****/
#define N 40
#define sol_num 6
#define tar_num 60

/*****Map.h*****/
#define menu_num 5
#define scene_num 2
#define map_num 6
#define tutor_num 1
#define about_num 1
#define icon_n 15
#define MUSIC 8
#define SOUND 3
#define SOUND1 1


/*****BATTLE_SCENE.h*****/
#define character_num 27
#define property_num 5
#define cha_image 1
#define num_battle_image 1
#define image_num 21
#define icon_num 6
#define field_num 12

#define sacred_left 6
#define sacred_right 33

#define x_num 9
#define y_num 5
#define tiles_num 40
#define tar_num 60
#define sol_num 6

//AI
#define sacredmonte 100
#define degenerate_rate 5
#define foe_enhance 50
#define foe_health_incr 1

#define DEBUG
//include
#include <iostream>
using namespace std;
const double X_DIS=108.0;
const double Y_DIS=120.0;
const double X_INIT=136.0;
const double Y_INIT=36.0;
const int X_NEXT=1020;
const int Y_NEXT=20;
const int X_UNIT=80;
const int Y_UNIT=80;
const int X_ADJ=20;
const int Y_ADJ=40;



#endif // DEFINITION_H
