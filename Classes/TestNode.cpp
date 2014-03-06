#include "TestNode.h"

USING_NS_CC;

TestNode::TestNode( void )
{
	CCLOG("TestNode alloc");
}

TestNode::~TestNode( void )
{
	CCLOG("TestNode delloc");
}

bool TestNode::init()
{
	return CCNode::init();
}

