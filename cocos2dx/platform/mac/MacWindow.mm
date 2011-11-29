
#import "MacWindow.h"


@implementation MacWindow

- (id) initWithFrame:(NSRect)frame fullscreen:(BOOL)fullscreen
{
	int styleMask = fullscreen ? NSBackingStoreBuffered : ( NSTitledWindowMask | NSClosableWindowMask );
	self = [self initWithContentRect:frame
						   styleMask:styleMask
							 backing:NSBackingStoreBuffered
							   defer:YES];
	
	if (self != nil)
	{
		if(fullscreen)
		{
			[self setLevel:NSMainMenuWindowLevel+1];
			[self setHidesOnDeactivate:YES];
			[self setHasShadow:NO];
		}
		
		[self setAcceptsMouseMovedEvents:NO];
		[self setOpaque:YES];
	}
	return self;
}

- (BOOL) canBecomeKeyWindow
{
	return YES;
}

- (BOOL) canBecomeMainWindow
{
	return YES;
}
@end

