#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	float m_cloudAmount;
	float m_cloudSpeed;

	cocos2d::EventListenerTouchAllAtOnce* m_eventListenerTouch;

	HelloWorld() : m_eventListenerTouch(nullptr), m_cloudAmount(0.7f), m_cloudSpeed(1.0f) {}
};

#endif // __HELLOWORLD_SCENE_H__
