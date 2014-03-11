#include "HudLayer.h"

USING_NS_CC;

bool HudLayer::init(){
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		_pad=SimpleDPad::dPadWithFile(CCString::create("pd_dpad.png"),64);
		_pad->setOpacity(100);
		_pad->setPosition(ccp(64,64));
		this->addChild(_pad);
		bRet=true;
	} while (0);
	return bRet;
}

HudLayer::HudLayer()
{
	_pad=NULL;
}

HudLayer::~HudLayer()
{
	CC_SAFE_RELEASE_NULL(_pad);
}
