#ifndef CONFIG_H
#define CONFIG_H
//状态栏位置
#define STATE_X 900
#define STATE_Y 520
#define STATE_DETAY 30

//子弹发射频率
#define MY_BULLET_INTERVAL 300
#define ENEMY_BULLET_INTERVAL 1500

//子弹移动速度
#define MY_BULLET_SPEED 5
#define ENEMY_BULLET_SPEED 10

//飞机移动速度
#define MY_CRAFT_SPEED 30
#define ENEMY_SPEED 50


//飞机尝试刷新频率（随机数确定是否刷新，因此未必刷新，）
#define ENEMY_GENERRATE_INTERVAL 3000
#define SPECIAL_ENEMY_GENERRATE_INTERVAL 5000
#define BLUE_ENEMY_GENERRATE_INTERVAL 7000

//起始飞机属性
#define ORIGINAL_BLOOD 120
#define ORIGINAL_SKILL 60
#define ORIGINAL_POWER 1

//敌人属性
#define ENEMY_BLOOD 1
#define ENEMY_POWER 5
#define SPECIAL_ENEMY_BLOOD 4
#define SPECIAL_ENEMY_POWER 20
#define BLUE_ENEMY_BLOOD 2

//属性更改参数
#define CRASH_HURT 4
#define BLUE_CONSUME 30
#define BLOOD_CURE 10
#define BLUE_INC 1
#define BLUE_CURE 20

//射击模式
#define SINGLE_SHOOT 1
#define MANY_SHOOT 2
#endif // CONFIG_H

//按键号
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


//技能时长5s
#define SKILLLAST 5000

//物体类型
#define ENEMY 0
#define SPECIAL_ENEMY 1
#define ME 2
#define MY_BULLET 3
#define ENEMY_BULLET 4
#define SPECIAL_ENEMY_BULLET 5
#define RED_MEDICINE 6
#define BLUE_MEDICINE 7
#define BLUE_ENEMY 8
