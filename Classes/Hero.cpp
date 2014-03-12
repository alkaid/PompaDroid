#include "Hero.h"
#include "TestNode.h"

USING_NS_CC;

Hero::Hero(void){
	_testNode=NULL;
	CCLOG("Hero alloc");
}
Hero::~Hero(void){
	setTestNode(NULL);
	CCLOG("Hero dealloc");
}

bool Hero::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("hero_idle_00.png"));
		//idle action
		CCArray* idelFrmaes=CCArray::createWithCapacity(6);
		for (int i=0;i<6;i++)
		{
			CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_idle_%02d.png",i)->getCString());
			idelFrmaes->addObject(frame);
		}
		CCAnimation *idelAnimation=CCAnimation::createWithSpriteFrames(idelFrmaes,1.0/12.0);
		//TODO 持有CCAction的引用后，Hero对象无法自动回收 点解？::其实是由于CCCallFunc引用了Hero对象造成循环引用
		this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idelAnimation)));
		//attack action
		CCArray *attackFrames=CCArray::createWithCapacity(3);
		for(int i=0;i<3;i++){
			attackFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_attack_00_%02d.png",i)->getCString()));
		}
		this->setAttackAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(attackFrames,1.0/24.0)),CCCallFunc::create(this,callfunc_selector(Hero::idle)),NULL));
		//Walk action
		CCArray* walkFrams=CCArray::createWithCapacity(8);
		for(int i=0;i<8;i++){
			walkFrams->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_walk_%02d.png",i)->getCString()));
		}
		this->setWalkAction(CCRepeatForever::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(walkFrams,1.0/12.0))));
		//hurt action
		CCArray *hurtFrames=CCArray::createWithCapacity(3);
		for(int i=0;i<3;i++){
			hurtFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_hurt_%02d.png",i)->getCString()));
		}
		this->setHurtAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(hurtFrames,1.0/12.0)),CCCallFunc::create(this,callfunc_selector(Hero::idle)),NULL));
		//knockedout action
		CCArray *knockedOutFrames=CCArray::createWithCapacity(3);
		for(int i=0;i<3;i++){
			knockedOutFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("hero_knockout_%02d.png",i)->getCString()));
		}
		this->setKnockedOutAction(CCSequence::create(CCAnimate::create(CCAnimation::createWithSpriteFrames(knockedOutFrames,1.0/12.0)),CCBlink::create(2,10),NULL));

		this->setCenter2Bottom(39.0);
		this->setCenter2Sides(29.0);
		this->setHitPoints(100.0);
		this->setDamage(20.0);
		this->setWalkSpeed(80.0);

		this->setTestNode(TestNode::create());
		bRet=true;
	} while (0);
	return bRet;
}

void Hero::update( float dt )
{
	ActionSprite::update(dt);
}