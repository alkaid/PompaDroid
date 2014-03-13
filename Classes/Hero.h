#pragma once

#include "cocos2d.h"
#include "ActionSprite.h"
#include "TestNode.h"

class Hero:public ActionSprite
{
protected:
	CC_SYNTHESIZE_RETAIN(TestNode*,_testNode,TestNode);
public:
	Hero(void);
	virtual ~Hero(void);
	bool init();
	CREATE_FUNC(Hero);
	//scheduler
	void update(float dt);
	virtual void knockedOut();
};