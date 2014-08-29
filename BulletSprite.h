#pragma once

#include "cocos2d.h"
USING_NS_CC;

class TankSprite;
class MapLayer;

class BulletSprite :public Sprite
{
public:	 
	BulletSprite();
	virtual ~BulletSprite();
public:
	static BulletSprite* createBulletWithTank(TankSprite* tank);
	void initBulletWithTank(TankSprite* tank);
	bool fire();
	virtual void update(float delta);
	void bulletBoom();
	bool collisonTest();
	bool IsRectIntersect(CCRect rectA, CCRect rectB);


public:
	bool			_isFlying;
	TankSprite*		_tank;
	MapLayer*		_mapLayer;
	float			_stepX;
	float			_stepY;
public:
	CC_SYNTHESIZE(CCRect, _mMoveRect, MoveRect);
	
};

