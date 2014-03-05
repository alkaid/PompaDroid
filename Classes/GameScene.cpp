#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene(void){
	gameLayer=NULL;
	hudLayer=NULL;
}

GameScene::~GameScene(void){
	
}

bool GameScene::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		gameLayer=GameLayer::create();
		hudLayer=HudLayer::create();
		this->addChild(gameLayer,0);
		this->addChild(hudLayer,1);
		bRet=true;
	} while (0);
	return bRet;
}