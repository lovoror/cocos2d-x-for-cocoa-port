#import "MacGLView.h"
#import <Availability.h>
#import <OpenGL/gl.h>
#import "CCDirector.h"
#import "CCGeometry.h"
#import "CCEGLView.h"
#import "CCKeypadDispatcher.h"
#import "CCIMEDispatcher.h"
#import "ccConfig.h"

static MacGLView *view;

static NSPoint translate(NSPoint spoint,NSRect rect)
{
    NSPoint point = NSMakePoint(spoint.x, rect.size.height-spoint.y);
    return point;
}

@implementation MacGLView

+ (id) sharedMacGLView
{
    return view;
}

- (id) initWithFrame:(NSRect)frameRect
{
	self = [self initWithFrame:frameRect shareContext:nil];
	return self;
}

- (id)initWithCoder:(NSCoder *)decoder
{
    [super initWithCoder:decoder];
    self = [self initWithFrame:[self bounds] shareContext:nil];
    return self;
}


- (id) initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format
{
    self = [self initWithFrame:frameRect shareContext:nil];
	return self;
}

- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context
{
    m_pTouch    = new cocos2d::CCTouch;
    m_pSet      = new cocos2d::CCSet;
	
    NSOpenGLPixelFormatAttribute attribs[] =
    {
		NSOpenGLPFAAccelerated,
		NSOpenGLPFANoRecovery,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		
		0
    };
	
	NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
	
	if (!pixelFormat)
		NSLog(@"No OpenGL pixel format");
	
	if( (self = [super initWithFrame:frameRect pixelFormat: pixelFormat]) ) {
		
		if( context )
			[self setOpenGLContext:context];
        
		GLint swapInt = 1;
		[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval]; 
	
	}
	view = self;
	return self;
}

- (void) changeDeviceOrientation
{
    NSRect rect = [self bounds];
	[self setBoundsSize:NSMakeSize (rect.size.height, rect.size.width) ];
    [[self window] setContentSize:NSMakeSize (rect.size.height, rect.size.width)];

}

- (void) reshape
{
	NSRect rect = [self bounds];

	cocos2d::CCDirector *director = cocos2d::CCDirector::sharedDirector();
    cocos2d::CCSize size = cocos2d::CCSizeMake(rect.size.width,rect.size.height);
	director->reshapeProjection(size);
	director->drawScene();
}

- (NSPoint) getLocalPoint: (NSEvent*)theEvent
{
    return [self convertPoint:[theEvent locationInWindow] fromView:nil];
}

- (void)mouseDown:(NSEvent *)theEvent
{
	NSPoint converted_point = translate([self getLocalPoint: theEvent], [self bounds]);
    NSLog(@"mouseDown x %f y %f ", converted_point.x, converted_point.y);
    m_pTouch->SetTouchInfo(0, (float)converted_point.x, (float)converted_point.y);
    m_pSet->addObject(m_pTouch);
    cocos2d::CCEGLView::sharedOpenGLView().touchesBegan(m_pSet);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
	NSPoint converted_point = translate([self getLocalPoint: theEvent], [self bounds]);
    NSLog(@"mouseDragged x %f y %f ", converted_point.x, converted_point.y);
    m_pTouch->SetTouchInfo(0, (float)converted_point.x, (float)converted_point.y);
    m_pSet->addObject(m_pTouch);
    cocos2d::CCEGLView::sharedOpenGLView().touchesMoved(m_pSet);
}

- (void)mouseUp:(NSEvent *)theEvent
{
	NSPoint converted_point = translate([self getLocalPoint: theEvent], [self bounds]);
    NSLog(@"mouseUp x %f y %f ", converted_point.x, converted_point.y);
    m_pTouch->SetTouchInfo(0, (float)converted_point.x, (float)converted_point.y);
    m_pSet->addObject(m_pTouch);
    cocos2d::CCEGLView::sharedOpenGLView().touchesEnded(m_pSet);
    m_pSet->removeObject(m_pTouch);
}

-(BOOL) becomeFirstResponder
{
	return YES;
}

-(BOOL) acceptsFirstResponder
{
	return YES;
}

-(BOOL) resignFirstResponder
{
	return YES;
}

- (void)keyDown:(NSEvent *)theEvent
{
	unichar chars = [[theEvent characters] characterAtIndex:0];
    NSLog(@"scrollWheel deltaX %c  ", chars);
    

    if (chars == NSDeleteCharacter || chars == NSBackspaceCharacter || chars == NSDeleteFunctionKey)
    {
        cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchDeleteBackward();
    }
    else if (chars == NSEnterCharacter)
    {
        cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchInsertText("\n", 1);
    }
    else if (chars < 128)
    {
        // ascii char
        cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchInsertText((const char *)&chars, 1);
    }
    else
    {
        //cocos2d::CCIMEDispatcher::sharedDispatcher()->dispatchInsertText(szUtf8, nLen);
    }
}

@end

