#import "TestAppDelegate.h"
#import "CCEGLView_mac.h"
#import "CCGeometry.h"
#import "AppDelegate.h"
static 
AppDelegate app;
@implementation TestAppDelegate

@synthesize window=window_, glView=glView_;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    cocos2d::CCApplication::sharedApplication().run();
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *) theApplication
{
	return YES;
}

@end
