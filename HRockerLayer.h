#pragma once

#include "cocos2d.h"
#include "CommonValue.h"
USING_NS_CC;

class HRockerLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(HRockerLayer);
	static HRockerLayer* HRockerWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole);
	void Active();
	void Inactive();
	enumOrder getRetation();
	void  update(float delta);
private:
	float getVelocity();
	Vec2 getDirection();
	enumOrder CalculateRetation();
	HRockerLayer* initWithCenter(Vec2 aPoint, float aRadius, Sprite* aJsSprite, Sprite* aJsBg, bool _isFollowRole);
	void AddEventTouch();
	bool TouchBegan(Touch *pTouch, Event *pEvent);
	void TouchMoved(Touch *pTouch, Event *pEvent);
	void TouchEnded(Touch *pTouch, Event *pEvent);

	
private:
	Vec2		_centerPoint;
	Vec2		_currentPoint;
	bool		_active;
	float		_radius;
	Sprite*		_jsSprite;
	bool		_isFollowRole;
	enumOrder	_order;

};