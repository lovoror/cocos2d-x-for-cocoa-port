#ifndef __CC_MACGLVIEW_H
#define __CC_MACGLVIEW_H

#import "CCSet.h"
#import "CCTouch.h"
#import "ccConfig.h"

@interface MacGLView : NSOpenGLView {
		cocos2d::CCSet* m_pSet;
		cocos2d::CCTouch* m_pTouch;	
}
- (id) initWithFrame:(NSRect)frameRect;

- (id) initWithFrame:(NSRect)frameRect shareContext:(NSOpenGLContext*)context;

- (void) changeDeviceOrientation;

+ (id) sharedMacGLView;

@end

#endif
