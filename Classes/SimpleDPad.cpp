#include "SimpleDPad.h"

USING_NS_CC;

SimpleDPad::SimpleDPad()
{
	_delegate=NULL;
}

SimpleDPad::~SimpleDPad()
{
}

SimpleDPad* SimpleDPad::dPadWithFile( CCString* fileName,float radius )
{
	SimpleDPad* pad=new SimpleDPad();
	if(pad && pad->initWithFile(fileName,radius))
	{
		return pad;
	}else{
		CC_SAFE_DELETE(pad);
		return NULL;
	}
	
}

bool SimpleDPad::initWithFile( CCString* fileName,float radius )
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCSprite::initWithFile(fileName->getCString()));
		_radius=radius;
		_direction=CCPointZero;
		_isHold=false;
		this->scheduleUpdate();
		bRet=true;
	} while (0);
	return bRet;
}

void SimpleDPad::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}

void SimpleDPad::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void SimpleDPad::update( float delta )
{
	if(_isHold){
		_delegate->onHoldingDirection(this,_direction);
	}
}

bool SimpleDPad::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint location = pTouch->getLocation();
	float distanceSQ=ccpDistanceSQ(location,this->getPosition());
	if(distanceSQ<_radius*_radius){
		this->updateDirection(location);
		_isHold=true;
		return true;
	}
	return false;
}

void SimpleDPad::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	this->updateDirection(pTouch->getLocation());
}

void SimpleDPad::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	_direction=CCPointZero;
	_isHold=false;
	_delegate->onTouchEnded(this);
}

void SimpleDPad::updateDirection( CCPoint touchLocation )
{
	float radians=ccpToAngle(ccpSub(touchLocation,this->getPosition()));
	float degree=-1*CC_RADIANS_TO_DEGREES(radians);
	if(degree<=22.5&&degree>-22.5){
		//右
		_direction=ccp(1,0);
	}else if(degree>=22.5&&degree<67.5){
		//右下
		_direction=ccp(1,-1);
	}else if(degree>=67.5&&degree<112.5){
		//下
		_direction=ccp(0,-1);
	}else if(degree>=112.5&&degree<157.5){
		//左下
		_direction=ccp(-1,-1);
	}else if(degree>=157.5 || degree<-157.5){
		//左
		_direction=ccp(-1,0);
	}else if(degree>=-157.5&&degree<-112.5){
		//左上
		_direction=ccp(-1,1);
	}else if(degree>=-112.5&&degree<-67.5){
		//上
		_direction=ccp(0,1);
	}else if(degree>=-67.5||degree<-22.5){
		//右上
		_direction=ccp(1,1);
	}
	_delegate->onDirectionChanged(this,_direction);
}



