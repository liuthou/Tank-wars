#pragma once

#include "cocos2d.h"
USING_NS_CC;

class WelcomeLayer:public cocos2d::Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(WelcomeLayer);
	virtual bool init();
	void init_Create();
	void startGame(Ref* pNode);

};

