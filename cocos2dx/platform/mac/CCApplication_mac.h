#ifndef __CC_APPLICATION_MAC_H
#define __CC_APPLICATION_MAC_H

#import "CCCommon.h"

NS_CC_BEGIN;

class CCRect;

class CC_DLL CCApplication
{
public:
    CCApplication();
    virtual ~CCApplication();

    virtual bool initInstance() = 0;

    virtual bool applicationDidFinishLaunching() = 0;

    virtual void applicationDidEnterBackground() = 0;

    virtual void applicationWillEnterForeground() = 0;

    void setAnimationInterval(double interval);
    
    typedef enum
    {
        kOrientationPortrait = 0,
        kOrientationPortraitUpsideDown = 1,
        kOrientationLandscapeLeft = 2,
        kOrientationLandscapeRight = 3,
    } Orientation;

    Orientation setOrientation(Orientation orientation);

    void statusBarFrame(CCRect * rect);

    int run();

    static CCApplication& sharedApplication();

    static ccLanguageType getCurrentLanguage();
    
protected:
    static CCApplication * sm_pSharedApplication;
};

NS_CC_END;
#endif
