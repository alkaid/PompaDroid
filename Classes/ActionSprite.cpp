#include "ActionSprite.h"
#include "Utils.h"
#include "SimpleAudioEngine.h"

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
		//play music effect
		int randomSound = Utils:: random_range(0, 1);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(CCString::createWithFormat("Sounds/pd_hit%d.wav", randomSound)->getCString());

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

alkaid::BoundingBox ActionSprite::createBoundingBox( CCPoint origin,CCSize size )
{
	BoundingBox boundingBox;
	boundingBox.original.origin=origin;
	boundingBox.original.size=size;
	boundingBox.actual.origin=ccpAdd(this->getPosition(),origin);
	boundingBox.actual.size=size;
	return boundingBox;
}

void ActionSprite::transformBoxes()
{
	_hitBox.actual.origin=ccpAdd(this->getPosition(),_hitBox.original.origin);
	_attackBox.actual.origin=ccpAdd(this->getPosition(),ccp(_attackBox.original.origin.x+ (this->isFlipX()?(-_attackBox.original.size.width-_hitBox.original.size.width):0) ,_attackBox.original.origin.y));
	//TODO ccDrawRect方法只有重载CCNode的draw()里有效，那么如何画矩形？
	//glLineWidth(10);
	//ccDrawColor4B(255,0,0,255);
	//ccDrawRect(_hitBox.actual.origin,ccp(_hitBox.actual.getMaxX(),_hitBox.actual.getMaxY()));
	//ccDrawRect(_attackBox.actual.origin,ccp(_attackBox.actual.getMaxX(),_attackBox.actual.getMaxY()));
}

void ActionSprite::setPosition( const CCPoint& pos )
{
	CCSprite::setPosition(pos);
	this->transformBoxes();
}




