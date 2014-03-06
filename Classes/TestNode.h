#pragma once

#include "cocos2d.h"
/************************************************************************/
/* 用来测试内存分配回收情况                                                                     */
/************************************************************************/
class TestNode:public cocos2d::CCNode{
public:
	TestNode(void);
	virtual ~TestNode(void);
	bool init();
	CREATE_FUNC(TestNode);
};