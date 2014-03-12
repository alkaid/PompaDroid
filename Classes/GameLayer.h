#ifndef __GAME_LAYER_H
#define __GAME_LAYER_H

#include "cocos2d.h"
#include "Hero.h"
#include "TestNode.h"
#include "SimpleDPad.h"
#include "Robot.h"

class GameLayer : public cocos2d::CCLayer,public SimpleDPadDelegate
{
public:
	GameLayer();
	virtual ~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//scheduler
	void update(float dt);

	virtual void onDirectionChanged(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);
	virtual void onHoldingDirection(SimpleDPad* simpleDPad,cocos2d::CCPoint direction);
	virtual void onTouchEnded(SimpleDPad* simpleDPad);
protected:
	CC_SYNTHESIZE_RETAIN(CCArray*, _robots,Robots);
private:
	cocos2d::CCTMXTiledMap* _tileMap;
	cocos2d::CCSpriteBatchNode* _actors;
	Hero *_hero;
	int _updateCount;
	TestNode* _testNode;
	cocos2d::CCAction* _testAction;

	void initTilemap();
	void initHero();
	void initRobots();
	void setViewpointCenter(cocos2d::CCPoint center);
	void reorderActors();
};

#endif