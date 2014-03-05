#pragma once
#include "AppMacros.h"
#include "cocos2d.h"

NS_AK_BEGIN

class Utils
{
public:
	//convenience measurement
	static cocos2d::CCSize getVisualSize();
	static cocos2d::CCPoint getCenter();
	static float currentTime();
	//convenience functions
	static int random_range(int low,int high);
protected:
private:
};

NS_AK_END