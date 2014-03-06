#include "ActionSprite.h"

USING_NS_CC;
USING_NS_AK;

ActionSprite::ActionSprite(void){
	_idleAction=NULL;
	_walkAction=NULL;
	_knockedOutAction=NULL;
	_attackAction=NULL;
	_hurtAction=NULL;
}

ActionSprite::~ActionSprite( void ){
	setAttackAction(NULL);
	setIdleAction(NULL);
	setWalkAction(NULL);
	setKnockedOutAction(NULL);
	setHurtAction(NULL);
}

void ActionSprite::idle()
{
	if(_actionState!=kActionStateIdle){
		this->stopAllActions();
		this->runAction(_idleAction);
		this->setVelocity(CCPointZero);
		this->setActionState(kActionStateIdle);
	}
}

void ActionSprite::update( float dt )
{
	
}

void ActionSprite::attack()
{
	switch(_actionState){
	case kActionStateAttack:
	case kActionStateIdle:
	case kActionStateWalk:
		this->stopAllActions();
		this->runAction(_attackAction);
		this->setActionState(kActionStateAttack);
		break;
	default:
		break;
	}
}

void ActionSprite::hurtWithDamage( float damage )
{

}

void ActionSprite::walkWithDirection( cocos2d::CCPoint direction )
{

}

void ActionSprite::knockedOut()
{

}




