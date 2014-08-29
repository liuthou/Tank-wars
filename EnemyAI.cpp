#include "EnemyAI.h"
#include "MapLayer.h"
#include "CommonValue.h"

EnemyAI::EnemyAI()
{

}

EnemyAI::~EnemyAI()
{

}

EnemyAI* EnemyAI::createEnemyAIWithTank(Layer* maplayer)
{
	EnemyAI* enemyTank = new EnemyAI();
	enemyTank->initEnemyAIWithTank(maplayer);

	return enemyTank;
}

void EnemyAI::initEnemyAIWithTank(Layer* maplayer)
{
	
	
	_mapLayer = (MapLayer*)maplayer;
	_mTank = _mapLayer->_tankSprite;
	
	_mEnemyTanks = CCArray::createWithCapacity(4);
	_mEnemyTanks->retain();


	//��ʼ�����ֵص�
	CCSize mapSize = _mapLayer->_gameMap->getContentSize();
	CCSize tileSize = _mapLayer->_gameMap->layerNamed("bg1")->getMapTileSize();
	_bornPoint[0] = _mapLayer->objectPositon( "en1");// ccp(tileSize.width, mapSize.height - tileSize.height);
	_bornPoint[1] = _mapLayer->objectPositon( "en2");;// ccp(mapSize.width / 2, mapSize.height - tileSize.height);
	_bornPoint[2] = _mapLayer->objectPositon( "en3");;// ccp(mapSize.width - tileSize.width, mapSize.height - tileSize.height);
	
}

void EnemyAI::update(float delta)
{
	//̹�˲���4��������̹��
	addTank(delta);

	//̹����Ϊ����
	tankAction(delta);
}

void EnemyAI::addTank(float delta)
{
	static float deltaTimes = 0.0f;
	deltaTimes += delta;
	if (deltaTimes >= 1.0f)
	{
		deltaTimes = 0.0f;
		int count = _mEnemyTanks->count();
		if (count < 3)	//�ȴӹ̶�λ���������̹��
		{
			TankSprite* enemyTank = TankSprite::initWithDelegate(count+1,count+1,_mapLayer->_gameMap->getContentSize(),_mapLayer);// TankSprite::createTankWithTankType(enemyTankType[count], mTileMapInfo);
			enemyTank->setPosition(_bornPoint[count]);
			//enemyTank->setAnchorPoint(Vec2(1,1));
			enemyTank->setRotation(180.0f);
			_mEnemyTanks->addObject(enemyTank);
			enemyTank->_mapLayer = _mTank->_mapLayer;
			enemyTank->_mapLayer->_gameMap->addChild(enemyTank, -1);
			enemyTank->_isEnemy = true;
			//enemyTank->setAnchorPoint(Vec2(0,0));
			//enemyTank->setPosition(Vec2(158.0+count*30, 0));
		}
		else if (count == 3)	//���ĸ�̹��������
		{
			int tankTypeIndex = (int)(CCRANDOM_0_1() * 4) % 3;
			TankSprite* enemyTank = TankSprite::initWithDelegate(count+1, count+1, _mapLayer->_gameMap->getContentSize(),_mapLayer);
			//TankSprite* enemyTank = tankTypeIndex::createTankWithTankType(enemyTankType[tankTypeIndex], mTileMapInfo);
			enemyTank->setPosition(_bornPoint[tankTypeIndex]);
			enemyTank->setRotation(180.0f);
			_mEnemyTanks->addObject(enemyTank);
			enemyTank->_mapLayer = _mTank->_mapLayer;
			_mapLayer->_gameMap->addChild(enemyTank, -1);
			enemyTank->_isEnemy = true;
			//enemyTank->setPosition(Vec2(158.0 + count * 30, 0));
		}
	}
}

void EnemyAI::tankAction(float delta)
{
	Ref* pObj;
	CCARRAY_FOREACH(_mEnemyTanks, pObj)
	{
		TankSprite* tank = (TankSprite*)pObj;

		//̹�˰����ϴεķ���һֱ��ǰ��

		tank->command(tank->rotationToEnumOrder(tank->getRotation()));
		

		
		

		//tank->command(cmdFire);
		//̹��ÿ��һ�뿪һ�λ�
		static float firetimes = 0;
		firetimes += delta;
		if (firetimes>1.0f)
		{
			firetimes = 0;
			tank->command(cmdFire);
		}
		//tank->setBulletDelta(tank->getBulletDelta() + delta);
		//if (tank->getBulletDelta() > 1)
		//{
		//	//���������ӵ��ڷ����У������ʱ
		//	if (tank->command(cmdFire))
		//	{
		//		tank->setBulletDelta(0.0);
		//	}
		//}
		////���̹��֮�����ײ
		
		collisionTest();

		////���̹����������������
			tank->autoChangeDirection();

		
		//if (tank->getBlock())
			//tank->setRotation((int)(CCRANDOM_0_1() * 3.2) * 90);
		////���������ж���ɺ�̹�˸����Լ�������״̬�ƶ�
		//tank->move();
	}
	//
	//_mTank->move();
}

void EnemyAI::collisionTest()
{
	//̹�˺͵з�̹��֮�����ײ���
	Ref* pObj;

	CCARRAY_FOREACH(_mEnemyTanks, pObj)
	{
		if (_mTank==NULL)
		{
			break;
		}
		TankSprite* enemyTank = (TankSprite*)pObj;
		if (IsRectIntersect(_mTank->boundingBox(), enemyTank->boundingBox()))
		{
			enemyTank->setBlock(true);
			_mTank->setBlock(true);
		}
	}
	////�з�̹��֮�����ײ
	CCArray* ccTmpArray = CCArray::create();
	ccTmpArray->addObjectsFromArray(_mEnemyTanks);
	while (ccTmpArray->count())
	{
		Ref* pObj;
		TankSprite* tmpTank = (TankSprite*)ccTmpArray->lastObject();
		ccTmpArray->removeLastObject();
		CCARRAY_FOREACH(ccTmpArray, pObj)
		{
			if (IsRectIntersect(tmpTank->boundingBox(), ((TankSprite*)pObj)->boundingBox()))
			{
				tmpTank->setBlock(true);
				((TankSprite*)pObj)->setBlock(true);
				ccTmpArray->removeObject(pObj);
			}
		}
	}
}

bool EnemyAI::IsRectIntersect(CCRect rectA, CCRect rectB)
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

