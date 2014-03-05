#include "HudLayer.h"

USING_NS_CC;

bool HudLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		bRet=true;
	} while (0);
	return bRet;
}