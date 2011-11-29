
#import <Availability.h>
#import <Foundation/Foundation.h>

#include <string.h>
#include <vector>
#include <string>
#include <sstream>

#include "CCFileUtils.h"

#include "CCPlatformMacros.h"
#include "CCImage.h"
#include "CCStdC.h"
#include "ccUtils.h"
#include "CCTexture2D.h"

NS_CC_BEGIN;

typedef struct
{
    unsigned int height;
    unsigned int width;
    int         bitsPerComponent;
    bool        hasAlpha;
    bool        isPremultipliedAlpha;
    unsigned char*  data;
} tImageInfo;

bool CCImage::initWithString(
                             const char * pText,
                             int nWidth/* = 0*/,
                             int nHeight/* = 0*/,
                             ETextAlign eAlignMask/* = kAlignCenter*/,
                             const char * pFontName/* = nil*/,
                             int nSize/* = 0*/)
{
    NSString *stringval = [NSString stringWithUTF8String:pText]; 
    NSString *fontname = [NSString stringWithUTF8String:pFontName]; 
    NSFont *font = [[NSFontManager sharedFontManager]
                    fontWithFamily:fontname
                    traits:NSUnboldFontMask | NSUnitalicFontMask
                    weight:0
                    size:nSize];
    
    NSDictionary *dict = [NSDictionary dictionaryWithObject:font forKey:NSFontAttributeName];	
    
    NSAttributedString *stringWithAttributes = [[[NSAttributedString alloc] initWithString:stringval attributes:dict] autorelease];
    
    CGSize dim = NSSizeToCGSize( [stringWithAttributes size] );
    
	NSUInteger POTWide = ccNextPOT(dim.width);
	NSUInteger POTHigh = ccNextPOT(dim.height);
	unsigned char*			data;
	
	NSSize realDimensions = [stringWithAttributes size];
    
	//Alignment
	float xPadding = 0;
	
	// Mac crashes if the width or height is 0
	if( realDimensions.width > 0 && realDimensions.height > 0 ) {
		switch (eAlignMask) {
			case cocos2d::CCImage::kAlignLeft: xPadding = 0; break;
			case cocos2d::CCImage::kAlignCenter: xPadding = (POTWide-realDimensions.width)/2.0f; break;
			case cocos2d::CCImage::kAlignRight: xPadding = POTWide-realDimensions.width; break;
			default: break;
		}
		
		//Disable antialias
		[[NSGraphicsContext currentContext] setShouldAntialias:NO];	
		
		NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
		[image lockFocus];	
		
		[stringWithAttributes drawAtPoint:NSMakePoint(xPadding, POTHigh-dim.height)]; // draw at offset position	
		
		NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
		[image unlockFocus];
		
		data = (unsigned char*) [bitmap bitmapData];  //Use the same buffer to improve the performance.
		
    
        _initWithRawData(data, POTHigh*POTWide, POTWide, POTHigh, 8);
        [bitmap release];
		[image release]; 
		return true;
	} else {
		return false;
	}
}

NS_CC_END;