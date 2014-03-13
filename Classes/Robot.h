#pragma once
#include "ActionSprite.h"
#include "cocos2d.h"

class Robot: public ActionSprite
{
private:
protected:
	CC_SYNTHESIZE(float,_nextDecisionTime,NextDecisionTime);
public:
	bool init();
	CREATE_FUNC(Robot);
};