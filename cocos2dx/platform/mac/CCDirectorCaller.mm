#import <Foundation/Foundation.h>
#import "CCDirectorCaller.h"
#import "CCDirector.h"
#import "MacGLView.h"

static id s_sharedDirectorCaller;

@implementation CCDirectorCaller

@synthesize interval;

+(id) sharedDirectorCaller
{
	if (s_sharedDirectorCaller == nil)
	{
		s_sharedDirectorCaller = [CCDirectorCaller new];
	} 
	return s_sharedDirectorCaller;
}

+(void) destroy
{
    [s_sharedDirectorCaller release];
}

-(void) alloc
{
	interval = 1;
}

-(void) dealloc
{
	[_timer invalidate];
    [_timer release];
	[super dealloc];
}

-(void) startMainLoop
{
	_timer=[[NSTimer scheduledTimerWithTimeInterval:self.interval target:self selector:@selector(doCaller:) userInfo:nil repeats:YES] retain];	
}

-(void) setAnimationInterval:(double)intervalNew
{
  self.interval =  intervalNew;
	if(_timer){
		[_timer invalidate];
		[_timer release];
	}
	_timer=[[NSTimer scheduledTimerWithTimeInterval:self.interval target:self selector:@selector(doCaller:) userInfo:nil repeats:YES] retain];	
}

-(void) doCaller:(NSTimer *)timer
{
	cocos2d::CCDirector::sharedDirector()->mainLoop();
}

@end
