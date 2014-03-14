#pragma once
#include "AppMacros.h"
#include "cocos2d.h"

NS_AK_BEGIN

#ifndef UINT64_C
//#define UINT64_C(val) val##ui64
#define UINT64_C(val) val##ull
#endif

class Utils
{
public:
	//convenience measurement
	static cocos2d::CCSize getVisualSize();
	static cocos2d::CCPoint getCenter();
	static float currentTime();
	//convenience functions
	static int random_range(int low,int high);
	static float frandom();
	static float frandom_range(float low,float high);
protected:
private:
};

typedef enum _ActionState{
	kActionStateNone=0,
	kActionStateIdle,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockOut
} ActionState;

typedef struct _BoundingBox{
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
} BoundingBox;


NS_AK_END