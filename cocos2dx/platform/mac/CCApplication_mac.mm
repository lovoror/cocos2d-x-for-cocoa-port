
#import "CCDirector.h"
#import "CCApplication_mac.h"
#import "CCGeometry.h"
#import "CCDirectorCaller.h"

NS_CC_BEGIN;

CCApplication* CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = 0;
}

int CCApplication::run()
{
    if (initInstance() && applicationDidFinishLaunching()) 
    {
        [[CCDirectorCaller sharedDirectorCaller] startMainLoop];
    }
    return 0;
}

void CCApplication::setAnimationInterval(double interval)
{
    [[CCDirectorCaller sharedDirectorCaller] setAnimationInterval: interval ];
}

CCApplication::Orientation CCApplication::setOrientation(Orientation eOritation)
{
	CCEGLView * pView = CCDirector::sharedDirector()->getOpenGLView();
  if (pView)
  {
    return (Orientation)pView->setDeviceOrientation(eOritation);
	}
  return (Orientation)CCDirector::sharedDirector()->getDeviceOrientation();

}

void CCApplication::statusBarFrame(cocos2d::CCRect* rect)
{
	if (rect)
    {
		*rect = CCRectMake(0, 0, 0, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////////////////////////////

CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];
    
    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    
    ccLanguageType ret = kLanguageEnglish;
    if ([languageCode isEqualToString:@"zh"])
    {
        ret = kLanguageChinese;
    }
    else if ([languageCode isEqualToString:@"en"])
    {
        ret = kLanguageEnglish;
    }
    
    return ret;
}


NS_CC_END;
