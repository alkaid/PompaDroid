#ifndef __Hud_LAYER_H
#define __Hud_LAYER_H

#include "cocos2d.h"
#include "SimpleDPad.h"

class HudLayer : public cocos2d::CCLayer
{
public:
	HudLayer();
	virtual ~HudLayer();
	bool init();
	CREATE_FUNC(HudLayer);
protected:
	CC_SYNTHESIZE_RETAIN(SimpleDPad*,_pad,Pad);
private:
};

#endif