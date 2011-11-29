#import "HelloWordAppDelegate.h"
#import "CCEGLView_mac.h"
#import "CCGeometry.h"
#import "AppDelegate.h"

@implementation HelloWordAppDelegate

@synthesize window=window_, glView=glView_;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    AppDelegate app;
    cocos2d::CCApplication::sharedApplication().run();
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *) theApplication
{
	return YES;
}

@end
