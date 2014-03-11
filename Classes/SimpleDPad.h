#pragma once

#include "cocos2d.h"

USING_NS_CC;
class SimpleDPad;
class SimpleDPadDelegate
{
public:
	virtual void onHoldingDirection(SimpleDPad* simpleDPad,CCPoint direction)=0;
	virtual void onDirectionChanged(SimpleDPad* simpleDPad,CCPoint direction)=0;
	virtual void onTouchEnded(SimpleDPad* simpleDPad)=0;
};

class SimpleDPad : public CCSprite, public CCTargetedTouchDelegate
{
private:
	void updateDirection(CCPoint touchLocation);
protected:
	bool _isHold;
	float _radius;
	CCPoint _direction;
	CC_SYNTHESIZE(SimpleDPadDelegate*,_delegate,Delegate);

public:
	SimpleDPad();
	virtual ~SimpleDPad();
	virtual bool initWithFile(CCString* fileName,float radius);
	static SimpleDPad* dPadWithFile(CCString* fileName,float radius);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void update(float delta);
	
};