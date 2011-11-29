#import <Cocoa/Cocoa.h>


@interface HelloWordAppDelegate : NSObject <NSApplicationDelegate> {
    IBOutlet NSWindow	*window_;
    IBOutlet NSOpenGLView	*glView_;
}

@property (readwrite, retain)	NSWindow	*window;
@property (readwrite, retain)	NSOpenGLView	*glView;

@end
