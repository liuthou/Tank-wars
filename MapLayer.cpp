#include "MapLayer.h"
#include "VisibleRect.h"
#include "TankSprite.h"

//MapLayer* MapLayer::_static_maplayer = NULL;
MapLayer::MapLayer()
{
}


MapLayer::~MapLayer()
{
	//CC_SAFE_RELEASE(_tankSprite);
}

cocos2d::Scene* MapLayer::createScene()
{
	auto theScene = cocos2d::Scene::create();
	auto theLayer = MapLayer::create();
	theScene->addChild(theLayer);
	//_static_maplayer = theLayer;
	return theScene;
}

bool MapLayer::init()
{
	do 
	{
		CC_BREAK_IF(!cocos2d::LayerColor::initWithColor(cocos2d::Color4B(0,0,0,255),VisibleRect::getVisibleRect().size.height,VisibleRect::getVisibleRect().size.width));
		initCreate();
		return true;
	} while (0);
	return false;
}

void MapLayer::initCreate()
{

}

void MapLayer::initWithMap(int level, int tKind, int numLife)
{
	_level = level;

	_gameMap = TMXTiledMap::create(__String::createWithFormat("map%d.tmx", level)->getCString());
	auto scale = VisibleRect::getVisibleRect().size.height / _gameMap->getContentSize().height;
	_gameMap->setScale(scale);
	_gameMap->setPosition(0, 0);
	this->addChild(_gameMap);
	_bg1Layer = _gameMap->layerNamed("bg1");
	_bg2Layer = _gameMap->layerNamed("bg2");
	_bg3Layer = _gameMap->layerNamed("bg3");
	_bg2Layer->setVisible(false);
	_bg3Layer->setVisible(false);


	_objectsgroup = _gameMap->objectGroupNamed("objects");

	
	_tankSprite = TankSprite::initWithDelegate(numLife, tKind, _bg1Layer->getContentSize(),this);
	//_tankSprite->makeCanFire();
	//////tank 出生地
	Vec2 tankpoint =  this->objectPositon( "pl1");//Vec2(128.0,0.0);
	_tankSprite->setPosition(Vec2(tankpoint.x + _tankSprite->boundingBox().size.width / 2.0, tankpoint.y + _tankSprite->boundingBox().size.height / 2.0));
	_gameMap->addChild(_tankSprite,-1);

	//this->retain();
	_enemyAi = EnemyAI::createEnemyAIWithTank(this);


	//

	//this->scheduleUpdate();


}

cocos2d::Vec2 MapLayer::tileCoordinateFromPosition(cocos2d::Vec2 pos)
{
	int cox, coy;

	CCSize szLayer = _bg1Layer->getLayerSize();

	CCSize szTile = _gameMap->getTileSize();

	cox = pos.x / szTile.width;
	//与地图坐标相反，所以减  
	coy = szLayer.height - pos.y / szTile.height;

	if ((cox >= 0) && (cox < szLayer.width) && (coy >= 0) && (coy < szLayer.height)) {


		return  ccp(cox, coy);
	}
	else {

		return ccp(-1, -1);
	}

}

int MapLayer::tileDFromPosition(cocos2d::Vec2 pos)
{
	CCPoint cpt = this->tileCoordinateFromPosition(pos);
	if (cpt.x < 0) return  -1;
	if (cpt.y < 0) return -1;
	if (cpt.x >= _bg1Layer->getLayerSize().width) return -1;
	if (cpt.y >= _bg1Layer->getLayerSize().height) return -1;
	return _bg1Layer->tileGIDAt(cpt);


}

cocos2d::Vec2 MapLayer::objectPositon( const char *object)
{

	CCPoint point;

	ValueMap dic = _objectsgroup->objectNamed(object);
	Value x = dic["x"];
	Value y = dic["y"];

	point.x = x.asFloat();
	point.y = y.asFloat();

	//point.x = dic->valueForKey("x")->intValue();

	//point.y = dic->valueForKey("y")->intValue();


	return point;

	//Vec2 point;
	//auto dic = group->objectNamed(object);
	//point.x = 136.0;
	//point.y = 8.0;
	//return point;
}

void MapLayer::update(float delta,enumOrder order)
{
	//_enemyAi->update(delta);
	_tankSprite->update(delta, order);
	_enemyAi->update(delta);
}

void MapLayer::test()
{

}

bool MapLayer::collisionTest(Rect rect)
{
	int gid = 0;
	CCSize mapSize =_gameMap->getContentSize();
	CCSize tileSize = _gameMap->getTileSize();

	//超出地图外面直接返回
	if (rect.getMinX() <= 0.1 || rect.getMaxX() >= mapSize.width ||
		rect.getMinY() <= 0.1 || rect.getMaxY() >= mapSize.height)
		return true;

	//将坦克Y坐标转换为地图上的Y坐标
	float MinY = mapSize.height - rect.getMinY();
	float MaxY = mapSize.height - rect.getMaxY();
	//对坦克四个顶点进行碰撞检测
	gid = _bg1Layer->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),(int)(MinY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
		&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
		&&gidToTileType[gid] != tileKingDeath)
		return true;
	gid = _bg1Layer->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width),(int)(MaxY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
		&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
		&&gidToTileType[gid] != tileKingDeath)
		return true;
	gid = _bg1Layer->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),(int)(MaxY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
		&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
		&&gidToTileType[gid] != tileKingDeath)
		return true;
	gid = _bg1Layer->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width),(int)(MinY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
		&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
		&&gidToTileType[gid] != tileKingDeath)
		return true;






	return false;

}

//
//MapLayer* MapLayer::getInstance()
//{
//	return _static_maplayer;
//}
