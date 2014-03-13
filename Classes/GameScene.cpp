#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void){
	_gameLayer=NULL;
	_hudLayer=NULL;
}

GameScene::~GameScene(void){
	
}

bool GameScene::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		_gameLayer=GameLayer::create();
		_hudLayer=HudLayer::create();
		_gameLayer->setHudLayer(_hudLayer);
		this->addChild(_gameLayer,0);
		this->addChild(_hudLayer,1);
		_hudLayer->getPad()->setDelegate(_gameLayer);
		bRet=true;
	} while (0);
	return bRet;
}