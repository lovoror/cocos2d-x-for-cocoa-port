#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"

using namespace cocos2d;
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
class TestController : public CCLayerColor
#else
class TestController : public CCLayer
#endif
{
public:
    TestController();
    ~TestController();

    void menuCallback(CCObject * pSender);
    void closeCallback(CCObject * pSender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItmeMenu;
};

#endif
