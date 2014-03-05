#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"

class GameScene : public cocos2d::CCScene
{
protected:
	CC_SYNTHESIZE_RETAIN(GameLayer*,gameLayer,GameLayer);
	CC_SYNTHESIZE_RETAIN(HudLayer*,hudLayer,HudLayer);
public:
	GameScene(void);
	virtual ~GameScene(void);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	//static cocos2d::CCScene* scene();

	//// a selector callback
	//void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
