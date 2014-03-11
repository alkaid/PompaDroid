#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void){
	_gameLayer=NULL;
	_hudLayer=NULL;
}

GameScene::~GameScene(void){
	setGameLayer(NULL);
	setHudLayer(NULL);
}

bool GameScene::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		_gameLayer=GameLayer::create();
		_hudLayer=HudLayer::create();
		this->addChild(_gameLayer,0);
		this->addChild(_hudLayer,1);
		_hudLayer->getPad()->setDelegate(_gameLayer);
		bRet=true;
	} while (0);
	return bRet;
}