#pragma once
#include "cocos2d.h"
#include "CommonValue.h"
#include "BulletSprite.h"

USING_NS_CC;

class  MapLayer;
typedef enum 
{
	kBorn=1,
	kPlusStarOne,
	kPlusStarTwo,
	kPlusStarThree,
}TankKind;

typedef enum 
{
	kUp=1,
	kDown,
	kLeft,
	kRight,
	kFire,
	kStay,
	kPause,
}TankAction;

class TankSprite:public cocos2d::CCNode
{
public:
	TankSprite();
	virtual ~TankSprite();
public:
	void bindSprite(Sprite* sprite);
	Sprite* getSprite();
	static TankSprite* initWithDelegate(int numLife, int tKind, Size mSize, MapLayer* maplayer);

	bool command(enumOrder order);
	void autoChangeDirection();
	void onFire();
	void fire(Sprite* buttle, TankAction buttleOrientation);
	bool checkPoint(Vec2 pon);
	void makeCanFire();
	TankAction getTankDirection();
	void move();
	void update(float delta, enumOrder order);

	int  nextRotation(int rotation);
	enumOrder rotationToEnumOrder(int rotation);
	void test();
	
	void tankBoom();
	void setBlock(bool bvaule);
	bool getBlock();
	//void setBulletDelta(float delta);
	//float getBulletDelta();

	//初始化 action 集合
	static void initActionSet();
	void boomDone(Node* pNode);

private:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();


public:
	CC_SYNTHESIZE(float, mBulletDelta, BulletDelta);
	//CC_SYNTHESIZE(bool, IsBlock, Block);
	CC_SYNTHESIZE(CCRect, mMovedRect, MovedRect);
private:
	int _speed;
	int _life;
	TankKind		_kind;
	Size		_mapSize;
	TankAction	_kaction;
	bool		_isCanFire;
	int			_buttleOrientation;
	Vec2		_nectPos;
	bool		_IsBlock;
	float		_mBulletDelta;
	
	
	


public:
	bool		_isEnemy;
	Sprite*			_sprite;
	MapLayer*		_mapLayer;
	cocos2d::TMXTiledMap* _gameMap;
	BulletSprite*		_bullet;
};

