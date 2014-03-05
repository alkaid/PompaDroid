#ifndef __ACTION_SPRITE_H
#define __ACTION_SPRITE_H

#include "cocos2d.h"

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
	//CC_SYNTHESIZE(ActionState,_actionState,ActionState);
	//attr
	CC_SYNTHESIZE(float,_walkSpeed,WalkSpeed);
	CC_SYNTHESIZE(float,_hitPoints,HitPoints);
	CC_SYNTHESIZE(float,_damage,Damage);
	//movment

public:
	//struct
	ActionSprite(void);
	~ActionSprite(void);
	//action method
	void idle();
	void attack();
	void hurtWithDamage(float damage);
	void walkWithDirection(cocos2d::CCPoint direction);
	void knockedOut();
	//scheduler
	void update(float dt);
};

#endif