#ifndef __GAME_LAYER_H
#define __GAME_LAYER_H

#include "cocos2d.h"
#include "Hero.h"
#include "TestNode.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameLayer);
	bool init();
	void initTilemap();
	void initHero();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//scheduler
	void update(float dt);
protected:

private:
	cocos2d::CCTMXTiledMap* _tiledMap;
	cocos2d::CCSpriteBatchNode* _actors;
	Hero *_hero;
	int _updateCount;
	TestNode* _testNode;
	cocos2d::CCAction* _testAction;
};

#endif