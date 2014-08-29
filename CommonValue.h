#pragma once

#define ROUNDS   20

enum enumObjectType
{
	PlayerTank, EnemyTank, 
	PlayerBullet, EnemyBullet
};
enum enumOrder
{
	cmdNothing,
	cmdGoUP,
	cmdGoRight,
	cmdGoDown,
	cmdGoLeft,
	cmdFire
};



#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
