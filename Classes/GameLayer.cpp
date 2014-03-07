#include "GameLayer.h"

USING_NS_CC;

bool GameLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		//test
		_updateCount=0;
		_testNode=NULL;

		this->setTouchEnabled(true);
		this->initTilemap();
		_actors=CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors,-5);
		initHero();
		//_testNode=TestNode::create();
		//this->addChild(_testNode);
		this->scheduleUpdate();
		bRet=true;
	} while (0);
	return bRet;
}

void GameLayer::initTilemap(){
	_tiledMap=CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject* pObj=NULL;
	CCARRAY_FOREACH(_tiledMap->getChildren(),pObj){
		CCTMXLayer *child=(CCTMXLayer*)pObj;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tiledMap,-6);
}

void GameLayer::initHero()
{
	_hero=Hero::create();
	_actors->addChild(_hero);
	_hero->setPosition(ccp(_hero->getCenter2Sides(),_hero->getCenter2Bottom()+10));
	_hero->setDesiredPosition(_hero->getPosition());
	_hero->idle();
	
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	_hero->attack();
}

void GameLayer::update( float dt )
{
	//++_updateCount;
	//if(_updateCount<12)
	//CCLOG("frame %d ....",_updateCount);
	//if (_updateCount==2)
	//{
	//	//CCTextureCache::sharedTextureCache()->dumpCachedTextureInfo();
	//	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	//}
	//if (_updateCount==10)
	//{
	//	CCLOG("remove hero",_updateCount);
	//	_actors->removeChild(_hero,true);
	//	//this->removeChild(_testNode);
	//}
}
