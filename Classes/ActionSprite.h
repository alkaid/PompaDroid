#ifndef __ACTION_SPRITE_H
#define __ACTION_SPRITE_H

#include "cocos2d.h"
#include "Utils.h"

class ActionSprite : public cocos2d::CCSprite
{
protected:
	//Action
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*,_idleAction,IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*,_walkAction,WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*,_attackAction,AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*,_hurtAction,HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*,_knockedOutAction,KnockedOutAction);
	//states
	CC_SYNTHESIZE(alkaid::ActionState,_actionState,ActionState);
	//attr
	CC_SYNTHESIZE(float,_walkSpeed,WalkSpeed);
	CC_SYNTHESIZE(float,_hitPoints,HitPoints);
	CC_SYNTHESIZE(float,_damage,Damage);
	//movment
	CC_SYNTHESIZE(cocos2d::CCPoint,_velocity,Velocity);
	CC_SYNTHESIZE(cocos2d::CCPoint,_desiredPosition,DesiredPosition);
	//measurements
	CC_SYNTHESIZE(float,_center2Sides,Center2Sides);
	CC_SYNTHESIZE(float,_center2Bottom,Center2Bottom);
public:
	//struct
	ActionSprite(void);
	virtual ~ActionSprite(void);
	//action method
	void idle();
	void attack();
	void hurtWithDamage(float damage);
	void walkWithDirection(cocos2d::CCPoint direction);
	void knockedOut();
	//scheduler
	void update(float dt);
	virtual void cleanup();
};

#endif