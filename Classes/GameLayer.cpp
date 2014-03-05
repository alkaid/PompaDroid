#include "GameLayer.h"

USING_NS_CC;

bool GameLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		this->initTilemap();
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