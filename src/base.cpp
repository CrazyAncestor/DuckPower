#include "base.h"



base::base()
{
    //ctor
}

base::~base()
{
    //dtor
}
void base::set_xy(int a,int b){
            x=a;y=b;
}
void base::setpos(int a){pos=a;}
int base::getsoldier_num(){return soldier_num;}
void base::setsoldier_num(int a){soldier_num=a;}
void base::set_Monte(int a){
            Monte=a;
}
