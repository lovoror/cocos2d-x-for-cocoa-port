#import <Foundation/Foundation.h>

@interface CCDirectorCaller : NSObject {
	int interval;
	NSTimer *_timer;
}

@property (readwrite) int interval;

-(void) startMainLoop;
-(void) doCaller: (id) sender;
-(void) setAnimationInterval:(double)interval;
+(id) sharedDirectorCaller;
+(void) destroy;
@end

