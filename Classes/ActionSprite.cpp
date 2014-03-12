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
	this->unscheduleUpdate();
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
	if (this->_actionState==alkaid::kActionStateWalk)
	{
		this->_desiredPosition=ccpAdd(this->getPosition(),ccpMult(_velocity,dt));
	}
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
	if(_actionState!=kActionStateKnockOut){
		stopAllActions();
		runAction(_hurtAction);
		this->setActionState(kActionStateHurt);
		_hitPoints-=damage;
		if(_hitPoints<=0){
			this->knockedOut();
		}
	}
}

void ActionSprite::walkWithDirection( cocos2d::CCPoint direction )
{
	switch(_actionState){
	case alkaid::kActionStateIdle:
		this->stopAllActions();
		this->runAction(_walkAction);
		this->setActionState(alkaid::kActionStateWalk);
		break;
	case alkaid::kActionStateWalk:
		this->_velocity=ccp(direction.x*_walkSpeed,direction.y*_walkSpeed);
		this->setActionState(alkaid::kActionStateWalk);
		this->setFlipX(_velocity.x<0);
		break;
	default:
		break;
	}
}

void ActionSprite::knockedOut()
{
	this->stopAllActions();
	this->runAction(_knockedOutAction);
	this->setActionState(kActionStateKnockOut);
	_hitPoints=0;
}

void ActionSprite::cleanup()
{
	CC_SAFE_RELEASE_NULL(_idleAction);
	CC_SAFE_RELEASE_NULL(_attackAction);
	CC_SAFE_RELEASE_NULL(_hurtAction);
	CC_SAFE_RELEASE_NULL(_walkAction);
	CC_SAFE_RELEASE_NULL(_knockedOutAction);
	CCSprite::cleanup();
}




