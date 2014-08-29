#ifndef __ENEMY__AI__H__
#define __ENEMY__AI__H__

#include "cocos2d.h"
using namespace cocos2d;
#include "TankSprite.h"


class MapLayer;

static const char* enemyTankType[] = 
{
	"normalU.png", "speedU.png", "armor1U.png"
};

class EnemyAI
{
public:
	EnemyAI();
	~EnemyAI();

	static EnemyAI* createEnemyAIWithTank(Layer* maplayer);
	void initEnemyAIWithTank(Layer* maplayer);
	void update(float delta);

	void collisionTest();
	bool IsRectIntersect(CCRect rectA, CCRect rectB);





private:
	void addTank(float delta);
	void tankAction(float delta);

public:
	CCArray* _mEnemyTanks;
	TankSprite* _mTank;
	MapLayer* _mapLayer;

	//出现地点
	CCPoint _bornPoint[3];
};

#endif