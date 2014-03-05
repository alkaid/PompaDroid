#ifndef __GAME_LAYER_H
#define __GAME_LAYER_H

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(GameLayer);
	bool init();
	void initTilemap();
protected:
private:
	cocos2d::CCTMXTiledMap* _tiledMap;
};

#endif