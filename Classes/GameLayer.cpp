#include "GameLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_AK;

GameLayer::GameLayer(){
	_robots=NULL;
	_hudLayer=NULL;
}
GameLayer::~GameLayer(){
	this->unscheduleUpdate();
	this->setRobots(NULL);
	this->setHudLayer(NULL);
}

bool GameLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		//LoadAudio
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);//设置音量0.0-1.0
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/latin_industries.aifc");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sounds/latin_industries.aifc");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/pd_hit0.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/pd_hit1.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/pd_herodeath.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/pd_botdeath.wav");
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
	if(_hero->getActionState()==kActionStateAttack){
		CCObject *pobj=NULL;
		CCARRAY_FOREACH(_robots,pobj){
			Robot *robot=(Robot*)pobj;
			if(robot->getActionState()!=kActionStateKnockOut){
				//hero与enemy y轴上是否在可攻击范围(同一行)
				if(fabs(_hero->getPositionY()-robot->getPositionY())<10){
					if(_hero->getAttackBox().actual.intersectsRect(robot->getHitBox().actual)){
						robot->hurtWithDamage(_hero->getDamage());
					}
				}
			}
		}
	}
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
	this->updateRobots(dt);
	this->updatePositions();
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
		int minX=Utils::getVisualSize().width;
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

void GameLayer::updatePositions()
{
	float posY=MIN(MAX(_hero->getCenter2Bottom(),_hero->getDesiredPosition().y),_tileMap->getTileSize().height*3+_hero->getCenter2Bottom());
	float posX=MIN(MAX(_hero->getCenter2Sides(),_hero->getDesiredPosition().x),_tileMap->getTileSize().width*_tileMap->getMapSize().width-_hero->getCenter2Sides());
	_hero->setPosition(ccp(posX, posY));
	CCObject* pobj=NULL;
	CCARRAY_FOREACH(_robots,pobj){
		Robot* robot=(Robot*)pobj;
		float posY=MIN(MAX(robot->getCenter2Bottom(),robot->getDesiredPosition().y),_tileMap->getTileSize().height*3+robot->getCenter2Bottom());
		float posX=MIN(MAX(robot->getCenter2Sides(),robot->getDesiredPosition().x),_tileMap->getTileSize().width*_tileMap->getMapSize().width-robot->getCenter2Sides());
		robot->setPosition(ccp(posX, posY));
	}
}

void GameLayer::updateRobots(float dt)
{
	int alive=0;
	int randomChoice=0;
	CCObject* pobj=NULL;
	CCARRAY_FOREACH(_robots,pobj){
		Robot* robot=(Robot*)pobj;
		robot->update(dt);
		if(robot->getActionState()!=kActionStateKnockOut){
			//1  alive enemy计数
			++alive;
			//2  
			if(Utils::currentTime()>robot->getNextDecisionTime()){
				robot->setNextDecisionTime(Utils::frandom_range(0.1,0.5)*1000+Utils::currentTime());
				float distanceSQ=ccpDistanceSQ(_hero->getPosition(),robot->getPosition());
				//hero 和robot的距离在robot攻击范围内 策略1 attack  策略2 idel
				if(distanceSQ<50*50){
					randomChoice=Utils::random_range(0,1);
					switch(randomChoice){
					case 1:
						robot->setFlipX(_hero->getPositionX()<robot->getPositionX());
						robot->setNextDecisionTime(Utils::frandom_range(0.1,0.5)*2000+Utils::currentTime());
						robot->attack();
						if(robot->getActionState()==kActionStateAttack){
							if(fabs(robot->getPositionY()-_hero->getPositionY())<10){
								if(robot->getAttackBox().actual.intersectsRect(_hero->getHitBox().actual)){
									_hero->hurtWithDamage(robot->getDamage());
								}
							}
						}

						break;
					default:
						robot->idle();
						break;
					}
				}else if(distanceSQ<Utils::getVisualSize().width*Utils::getVisualSize().width){
					robot->setNextDecisionTime(Utils::frandom_range(0.1,0.5)*4000+Utils::currentTime());
					randomChoice=Utils::random_range(0,1);
					if(randomChoice==1){
						CCPoint direction=ccpNormalize(ccpSub(_hero->getPosition(),robot->getPosition()));
						robot->walkWithDirection(direction);
					}else{
						robot->idle();
					}
				}
			}


		}
	}
	//check end game
	if(_hudLayer->getChildByTag(5)==NULL && ( alive<=0||_hero->getActionState()==kActionStateKnockOut )){
		endGame();
	}
}

void GameLayer::endGame()
{
	CCLabelTTF *restartLabel = CCLabelTTF::create("RESTART", "Arial", 30);
	CCMenuItemLabel *restartItem = CCMenuItemLabel::create(restartLabel, this, menu_selector(GameLayer::restartGame));
	CCMenu *menu = CCMenu::create(restartItem, NULL);
	menu->setPosition(Utils::getCenter());
	menu->setTag(5);
	_hudLayer->addChild(menu, 5);
}

void GameLayer::restartGame(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(GameScene::create());
}
