#pragma once

#include "cocos2d.h"
/************************************************************************/
/* ���������ڴ����������                                                                     */
/************************************************************************/
class TestNode:public cocos2d::CCNode{
public:
	TestNode(void);
	virtual ~TestNode(void);
	bool init();
	CREATE_FUNC(TestNode);
};