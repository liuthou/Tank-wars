#pragma once
#include "cocos2d.h"
#include "MapLayer.h"
#include "HRockerLayer.h"
#include "TankSprite.h"
#include "EnemyAI.h"

USING_NS_CC;

const int	MaxLevel = 2;


class GameLayer:public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);
public:
	void initCreate();
	void loadMap();
	void CreateMapLayer();
	void CreateHRockerLayer();
	void CreateFireButton();
	void CreateOtherItem();
	void preLoadMusic();

	void showLife();
	void showLeve();
	void showEnemyCount();
	

	void menuCallback_PlayerFire(cocos2d::Ref* pSender);
	void menuCallback_NextLevel(cocos2d::Ref* pSender);
	void menuCallback_Pause(cocos2d::Ref* pSender);
	void update(float delta);


	void NextLevel();
	void GameOver();
	void ClearPreLevel();
	void GamePause();

public:

	cocos2d::LabelTTF *_iplifeString;
	cocos2d::LabelTTF* _leveString;
	cocos2d::LabelTTF* _enemyString;

	MapLayer *		_mapLayer;
	HRockerLayer*	_HRockerLayer;
	int				_gameLevel;
	int				_tankLifeCount;
	int				_enemyTankCount;
};

