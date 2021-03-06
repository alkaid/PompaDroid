#include "Utils.h"

USING_NS_CC;

NS_AK_BEGIN

CCSize Utils::getVisualSize(){
	return CCDirector::sharedDirector()->getWinSize();
}

CCPoint Utils::getCenter(){
	CCSize size=getVisualSize();
	return ccp(size.width/2,size.height/2);
}

float Utils::currentTime(){
	timeval time;
	gettimeofday(&time,NULL);
	unsigned long millsecs=time.tv_sec*1000+time.tv_usec/1000;
	return (float)millsecs;
}

int Utils::random_range(int low,int high){
	return rand()%(high-low+1) + low;
}

float Utils::frandom(){
	return (float)rand()/UINT64_C(0x100000000);
}

float Utils::frandom_range( float low,float high )
{
	return (high-low)*frandom() + low;
}

NS_AK_END