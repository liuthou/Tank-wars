#pragma once
#include "cocos2d.h"
#include "EnemyAI.h"

USING_NS_CC;


//tile类型，草地，钢铁，河流等
enum enumTileType
{
	tileNone, tileWall,
	tileSteel, tileGrass,
	tileRiver, tileRiver2,
	tileKing,tileKingDeath,
};

//根据地图中gid获取对应tile的类型
static enumTileType gidToTileType[] =
{
	tileNone,
	//1-28
	tileWall, tileWall, tileWall, tileWall, 
	tileSteel, tileSteel,tileSteel, tileSteel,
	tileGrass, tileGrass, tileGrass, tileGrass,
	tileRiver, tileRiver, tileRiver, tileRiver, 
	tileRiver2, tileRiver2, tileRiver2, tileRiver2,
	tileKing, tileKing, tileKing, tileKing,
	tileKingDeath, tileKingDeath, tileKingDeath, tileKingDeath,

	//29-56
	tileWall, tileWall, tileWall, tileWall,
	tileSteel, tileSteel, tileSteel, tileSteel,
	tileGrass, tileGrass, tileGrass, tileGrass,
	tileRiver, tileRiver, tileRiver, tileRiver,
	tileRiver2, tileRiver2, tileRiver2, tileRiver2,
	tileKing, tileKing, tileKing, tileKing,
	tileKingDeath, tileKingDeath, tileKingDeath, tileKingDeath,
	//57-84
	tileWall, tileWall, tileWall, tileWall,
	tileSteel, tileSteel, tileSteel, tileSteel,
	tileGrass, tileGrass, tileGrass, tileGrass,
	tileRiver, tileRiver, tileRiver, tileRiver,
	tileRiver2, tileRiver2, tileRiver2, tileRiver2,
	tileKing, tileKing, tileKing, tileKing,
	tileKingDeath, tileKingDeath, tileKingDeath, tileKingDeath,

	//85-112
	tileWall, tileWall, tileWall, tileWall,
	tileSteel, tileSteel, tileSteel, tileSteel,
	tileGrass, tileGrass, tileGrass, tileGrass,
	tileRiver, tileRiver, tileRiver, tileRiver,
	tileRiver2, tileRiver2, tileRiver2, tileRiver2,
	tileKing, tileKing, tileKing, tileKing,
	tileKingDeath, tileKingDeath, tileKingDeath, tileKingDeath,

};


class TankSprite;
class MapLayer:public cocos2d::LayerColor
{
public:
	MapLayer();
	~MapLayer();
public:
	//static MapLayer* getInstance();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MapLayer);

	void initWithMap(int level, int tKind, int numLife);

	void initCreate();
	void update(float delta,enumOrder order);

	cocos2d::Vec2 tileCoordinateFromPosition(cocos2d::Vec2 pos);

	int tileDFromPosition(cocos2d::Vec2 pos);
	void test();
	bool collisionTest(Rect rect);
	cocos2d::Vec2 objectPositon(const char *object);

public:
	int							_level;

	cocos2d::TMXLayer*			_bg1Layer;
	cocos2d::TMXLayer*			_bg2Layer;
	cocos2d::TMXLayer*			_bg3Layer;

	EnemyAI*					_enemyAi;
	TankSprite*					_tankSprite;

	cocos2d::TMXTiledMap*		_gameMap;
	cocos2d::TMXObjectGroup*	_objectsgroup;

	
};

