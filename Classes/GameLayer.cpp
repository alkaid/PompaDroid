#include "GameLayer.h"

USING_NS_CC;
USING_NS_AK;

GameLayer::GameLayer(){
	_robots=NULL;
}
GameLayer::~GameLayer(){
	this->unscheduleUpdate();
	this->setRobots(NULL);
}

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
		initRobots();
		//_testNode=TestNode::create();
		//this->addChild(_testNode);
		this->scheduleUpdate();
		bRet=true;
	} while (0);
	return bRet;
}

void GameLayer::initTilemap(){
	_tileMap=CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject* pObj=NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(),pObj){
		CCTMXLayer *child=(CCTMXLayer*)pObj;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap,-6);
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
	_hero->update(dt);
	float posY=MIN(MAX(_hero->getCenter2Bottom(),_hero->getDesiredPosition().y),_tileMap->getTileSize().height*3+_hero->getCenter2Bottom());
	float posX=MIN(MAX(_hero->getCenter2Sides(),_hero->getDesiredPosition().x),_tileMap->getTileSize().width*_tileMap->getMapSize().width-_hero->getCenter2Sides());
	_hero->setPosition(ccp(posX, posY));
	this->reorderActors();
	this->setViewpointCenter(_hero->getPosition());
}

void GameLayer::onDirectionChanged( SimpleDPad* simpleDPad,cocos2d::CCPoint direction )
{
	_hero->walkWithDirection(direction);
}

void GameLayer::onHoldingDirection( SimpleDPad* simpleDPad,cocos2d::CCPoint direction )
{
	_hero->walkWithDirection(direction);
}

void GameLayer::onTouchEnded( SimpleDPad* simpleDPad )
{
	if (_hero->getActionState()==alkaid::kActionStateWalk)
	{
		_hero->idle();
	}
}

void GameLayer::setViewpointCenter( cocos2d::CCPoint center )
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	float centerX=MIN(MAX(winSize.width/2,center.x),_tileMap->getMapSize().width*_tileMap->getTileSize().width-winSize.width/2);
	float centerY=MIN(MAX(winSize.height/2,center.y),_tileMap->getMapSize().height*_tileMap->getTileSize().height-winSize.height/2);
	CCPoint acturalPoint=ccp(centerX,centerY);
	CCPoint centerOfView=ccp(winSize.width/2,winSize.height/2);
	CCPoint viewPoint=ccpSub(centerOfView,acturalPoint);
	this->setPosition(viewPoint);
}

void GameLayer::initRobots()
{
	this->setRobots(CCArray::createWithCapacity(50));
	for(int i=0;i<50;i++){
		Robot* robot=Robot::create();
		_actors->addChild(robot);
		int minX=robot->getCenter2Sides();
		int maxX=_tileMap->getTileSize().width*_tileMap->getMapSize().width-robot->getCenter2Sides();
		int minY=robot->getCenter2Bottom();
		int maxY=_tileMap->getTileSize().height*3+robot->getCenter2Bottom();
		robot->setPosition(ccp(Utils::random_range(minX,maxX),Utils::random_range(minY,maxY)));
		robot->setDesiredPosition(robot->getPosition());
		robot->setFlipX(true);
		robot->idle();
		_robots->addObject(robot);
	}
}

void GameLayer::reorderActors()
{
	CCObject* pObj=NULL;
	CCARRAY_FOREACH(_actors->getChildren(),pObj){
		CCSprite* sprite=(CCSprite*)pObj;
		_actors->reorderChild(sprite,-sprite->getPositionY());
	}
}
