#ifndef _MAIN_H
#define _MAIN_H

enum eStaSystem {  //系统运行状态枚举
    E_NORMAL, E_SET_SPEED, E_SET_ANGLE,E_SET_P,E_SET_I,E_SET_D
};


extern enum eStaSystem staSystem;


#endif

