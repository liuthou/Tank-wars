#include "BulletSprite.h"
#include "VisibleRect.h"
#include "MapLayer.h"
#include "TankSprite.h"



BulletSprite::BulletSprite()
{
	_isFlying = false;
}
BulletSprite::~BulletSprite()
{

}


BulletSprite* BulletSprite::createBulletWithTank(TankSprite* tank)
{
	BulletSprite* bullet = new BulletSprite();
	bullet->initBulletWithTank(tank);
	bullet->autorelease();
	return bullet;
}

void BulletSprite::initBulletWithTank(TankSprite* tank)
{
	_tank = tank;
	_mapLayer = _tank->_mapLayer;
	initWithSpriteFrameName("bullet.png");
	_mapLayer->_gameMap->addChild(this,-1);
	setVisible(false);
}

bool BulletSprite::fire()
{
	if (!_isFlying)
	{
		_isFlying = true;
		setVisible(true);
		setPosition(_tank->getPosition());
		TankAction tankdirection = _tank->getTankDirection();
		switch (tankdirection)
		{
		case kDown:
			_stepX = 0.0f, _stepY = -2.0f;
			break;
		case kUp:
			_stepX = 0.0f, _stepY = 2.0f;
			break;
		case kRight:
			_stepX = 2.0f, _stepY = 0.0f;
			break;
		case kLeft:
			_stepX = -2.0f, _stepY = 0.0f;
			break;
		default:
			break;
		}
		this->scheduleUpdate();
	}
	return true;
}

void BulletSprite::update(float delta)
{
	Sprite::update(delta);
	setPosition(Vec2(this->getPosition().x+this->_stepX,this->getPosition().y+this->_stepY));

	if (this->collisonTest())
	{
		this->unscheduleUpdate();
		setVisible(false);
		_isFlying = false;
		bulletBoom();
	}

}

void BulletSprite::bulletBoom()
{
	CCRect rect = boundingBox();
	CCSize mapSize = _mapLayer->_gameMap->getContentSize();

	if (rect.getMinX() < 0 || rect.getMaxX() >= mapSize.width ||
		rect.getMinY() < 0 || rect.getMaxY() >= mapSize.height)
		return;

	CCTMXLayer* tmxLayer = _mapLayer->_gameMap->layerNamed("bg1");
	CCSize tileSize = tmxLayer->getMapTileSize();

	//调整Y轴位tmx地图中的Y轴  
	float MinY = mapSize.height - rect.getMinY();
	float MaxY = mapSize.height - rect.getMaxY();

	//将与子弹碰撞的墙壁tileWall图块删除  
	CCPoint pt = ccp((int)rect.getMinX() / tileSize.width, (int)(MinY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);

	pt = ccp((int)rect.getMinX() / tileSize.width, (int)(MaxY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);

	pt = ccp((int)rect.getMaxX() / tileSize.width, (int)(MinY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);

	pt = ccp((int)rect.getMaxX() / tileSize.width, (int)(MaxY / tileSize.height));
	if (gidToTileType[tmxLayer->tileGIDAt(pt)] == tileWall)
		tmxLayer->setTileGID(gidToTileType[tileNone], pt);
}

bool BulletSprite::collisonTest()
{

	Rect rect = this->boundingBox();
	int gid = 0;
	CCSize mapSize = _mapLayer->_gameMap->getContentSize();
	CCSize tileSize = _mapLayer->_gameMap->getTileSize();

	//超出地图外面直接返回
	if (rect.getMinX() <= 0.1 || rect.getMaxX() >= mapSize.width ||
		rect.getMinY() <= 0.1 || rect.getMaxY() >= mapSize.height)
		return true;


	//敌机子弹
	if (_tank->_isEnemy)
	{
		if (IsRectIntersect(_mapLayer->_tankSprite->boundingBox(),rect))
		{
			_mapLayer->_tankSprite->tankBoom();
			return true;
		}
	}
	else
	{
		Ref* pObj;
		CCARRAY_FOREACH(_mapLayer->_enemyAi->_mEnemyTanks, pObj)
		{
			TankSprite* enemyTank = (TankSprite*)pObj;
			if (IsRectIntersect(rect, enemyTank->boundingBox()))
			{
				enemyTank->tankBoom();
				return true;
			}
		}
	}






	//将坦克Y坐标转换为地图上的Y坐标
	float MinY = mapSize.height - rect.getMinY();
	float MaxY = mapSize.height - rect.getMaxY();
	//对坦克四个顶点进行碰撞检测
	gid = _mapLayer->_bg1Layer->tileGIDAt(_mapLayer->tileCoordinateFromPosition(this->getPosition()));
	//gid = _mapLayer->_bg1Layer->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width), (int)(MinY / tileSize.height)));
	if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
		&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
		&&gidToTileType[gid] != tileKingDeath)
		return true;
	//gid = _mapLayer->_bg1Layer->tileGIDAt(ccp((int)(rect.getMinX() / tileSize.width), (int)(MaxY / tileSize.height)));
	//if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
	//	&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
	//	&&gidToTileType[gid] != tileKingDeath)
	//	return true;
	//gid = _mapLayer->_bg1Layer->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width), (int)(MaxY / tileSize.height)));
	//if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
	//	&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
	//	&&gidToTileType[gid] != tileKingDeath)
	//	return true;
	//gid = _mapLayer->_bg1Layer->tileGIDAt(ccp((int)(rect.getMaxX() / tileSize.width), (int)(MinY / tileSize.height)));
	//if (gidToTileType[gid] != tileNone && gidToTileType[gid] != tileGrass
	//	&&gidToTileType[gid] != tileRiver&&gidToTileType[gid] != tileRiver2
	//	&&gidToTileType[gid] != tileKingDeath)
	//	return true;
	return false;
}

bool BulletSprite::IsRectIntersect(CCRect rectA, CCRect rectB)
{
	float left = max(rectA.getMinX(), rectB.getMinX());
	float right = min(rectA.getMaxX(), rectB.getMaxX());
	if (left > right)
		return false;

	float top = min(rectA.getMaxY(), rectB.getMaxY());
	float bottom = max(rectA.getMinY(), rectB.getMinY());
	if (top < bottom)
		return false;

	return true;
}


