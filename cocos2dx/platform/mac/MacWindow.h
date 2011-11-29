#ifndef __CC_MACWINDOW_H
#define __CC_MACWINDOW_H

#import <Foundation/foundation.h>

@interface MacWindow : NSWindow
{
}
- (id) initWithFrame:(NSRect)frame fullscreen:(BOOL)fullscreen;

@end


#endif