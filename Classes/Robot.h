#pragma once
#include "ActionSprite.h"
#include "cocos2d.h"

class Robot: public ActionSprite
{
private:
protected:
public:
	bool init();
	CREATE_FUNC(Robot);
};