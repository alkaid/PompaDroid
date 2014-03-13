#include "Robot.h"

USING_NS_CC;

bool Robot::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("robot_idle_00.png"));
		//idel Action
		CCArray* idelFrames=CCArray::createWithCapacity(5);
		for(int i=0;i<5;i++){
			idelFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_idle_%02d.png",i)->getCString()));
		}
		this->setIdleAction(CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(idelFrames,1.0/12.0))));
		//attack Action
		CCArray* attackFrames=CCArray::createWithCapacity(5);
		for(int i=0;i<5;i++){
			attackFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_attack_%02d.png",i)->getCString()));
		}
		this->setAttackAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(attackFrames,1.0/24.0)),CCCallFunc::create(this,callfunc_selector(Robot::idle)),NULL));
		//walk Action
		CCArray* walkFrames=CCArray::createWithCapacity(6);
		for (int i=0;i<6;i++)
		{
			walkFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_walk_%02d.png",i)->getCString()));
		}
		this->setWalkAction(CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(walkFrames,1.0/12.0))));
		//hurt action
		CCArray *hurtFrames=CCArray::createWithCapacity(3);
		for(int i=0;i<3;i++){
			hurtFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_hurt_%02d.png",i)->getCString()));
		}
		this->setHurtAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(hurtFrames,1.0/12.0)),CCCallFunc::create(this,callfunc_selector(Robot::idle)),NULL));
		//knockedout action
		CCArray *knockedOutFrames=CCArray::createWithCapacity(5);
		for(int i=0;i<5;i++){
			knockedOutFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("robot_knockout_%02d.png",i)->getCString()));
		}
		this->setKnockedOutAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(knockedOutFrames,1.0/12.0)),CCBlink::create(2,10),NULL));

		this->setCenter2Bottom(39.0);
		this->setCenter2Sides(29.0);
		this->setHitPoints(100.0);
		this->setDamage(10.0);
		this->setWalkSpeed(80.0);

		_hitBox=this->createBoundingBox(ccp(-_center2Sides,-_center2Bottom),CCSizeMake(_center2Sides*2,_center2Bottom*2));
		_attackBox=this->createBoundingBox(ccp(_center2Sides,-_center2Bottom+24),CCSizeMake(25,20));

		this->setNextDecisionTime(0);

		bRet=true;
	} while (0);
	return bRet;
}

