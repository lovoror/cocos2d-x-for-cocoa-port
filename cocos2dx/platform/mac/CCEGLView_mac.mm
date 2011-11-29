
#include "CCEGLView_mac.h"
#include "CCDirectorCaller.h"
#include "CCSet.h"
#include "CCTouch.h"
#include "CCTouchDispatcher.h"
#import "MacGLView.h"
#import "MacWindow.h"

namespace cocos2d {
    
    static CCEGLView* s_pMainWindow = NULL;
    static NSWindow *m_windowGLView = nil;
    static NSWindow *m_fullScreen = nil;
    static NSView *m_superViewGLView = nil;
    
    CCEGLView::CCEGLView()
    : m_bCaptured(false)
    , m_bOrientationReverted(false)
    , m_bOrientationInitVertical(false)
    , m_pDelegate(0)
    , m_eInitOrientation(CCDeviceOrientationPortrait)
    , m_originalWinRect(0, 0, 800, 480)
    , m_fScreenScaleFactor(1.0f)
    , m_isFullScreen(false)
    {
        s_pMainWindow = this;
    }
    
    CCEGLView::~CCEGLView()
    {
    }
    
    cocos2d::CCSize  CCEGLView::getSize()
    {
        NSRect rect = [(NSView*)[MacGLView sharedMacGLView] bounds]; 
        cocos2d::CCSize size = cocos2d::CCSizeMake(rect.size.width, rect.size.height);
        return size;
    }
    
    void  CCEGLView::setFullScreen(bool isFullScreen)
    {
        if (m_isFullScreen == isFullScreen) return;
        
        if( isFullScreen ) {
            NSRect originalWinRect_ = [(NSView*)[MacGLView sharedMacGLView] frame];
            m_originalWinRect = CCRect(originalWinRect_.origin.x, originalWinRect_.origin.y, originalWinRect_.size.width, originalWinRect_.size.height);
            
            if(!m_windowGLView)
                m_windowGLView = [[[MacGLView sharedMacGLView] window] retain];
            if(m_superViewGLView)
                [m_superViewGLView release];
            m_superViewGLView = [[[MacGLView sharedMacGLView] superview] retain];

            NSRect displayRect = [[NSScreen mainScreen] frame];
            
            m_fullScreen = [[MacWindow alloc] initWithFrame:displayRect fullscreen:YES];
            
            [[MacGLView sharedMacGLView] removeFromSuperview];
            
            [(NSView*)[MacGLView sharedMacGLView] setFrame:displayRect];
            
            [(id)m_fullScreen setContentView:[MacGLView sharedMacGLView]];
            
            [(id)m_fullScreen makeKeyAndOrderFront:m_fullScreen];
            [(id)m_fullScreen makeMainWindow];
            
        } else {
            [[MacGLView sharedMacGLView] removeFromSuperview];
            
            [(id)m_fullScreen release];
            m_fullScreen = nil;
            
            [m_superViewGLView addSubview:[MacGLView sharedMacGLView]];
            
            NSRect frameSize = {{m_originalWinRect.origin.x, m_originalWinRect.origin.y},{m_originalWinRect.size.width, m_originalWinRect.size.height}};
            
            [(NSView*)[MacGLView sharedMacGLView] setFrame:frameSize];
            
            [(id)m_fullScreen makeKeyAndOrderFront:m_fullScreen];
            [(id)m_fullScreen makeMainWindow];
        }
        
        [(NSView*)[MacGLView sharedMacGLView] setNeedsDisplay:YES];
    }
    
    bool CCEGLView::isOpenGLReady()
    {
        return [MacGLView sharedMacGLView] != NULL;
    }
    
    bool CCEGLView::canSetContentScaleFactor()
    {
        return FALSE;
    }
    
    void CCEGLView::setContentScaleFactor(float contentScaleFactor)
    {
        CCLog("could not set contentScaleFactor after initialized");
    }
    
    void CCEGLView::release()
    {
        [CCDirectorCaller destroy];
        
        [[MacGLView sharedMacGLView] removeFromSuperview];
        [m_windowGLView release];
        [m_fullScreen release];
    }
    
    void CCEGLView::setTouchDelegate(EGLTouchDelegate * pDelegate)
    {
        m_pDelegate = pDelegate;
    }
    
    void CCEGLView::swapBuffers()
    {
        [[[MacGLView sharedMacGLView] openGLContext] flushBuffer];
    }
	
    void CCEGLView::touchesBegan(CCSet *set)
    {
        if (m_pDelegate) {
            m_pDelegate->touchesBegan(set, NULL);
        }
    }
    
    void CCEGLView::touchesMoved(CCSet *set)
    {
        if (m_pDelegate) {
            m_pDelegate->touchesMoved(set, NULL);
        }
    }
    
    void CCEGLView::touchesEnded(CCSet *set)
    {
        if (m_pDelegate) {
            m_pDelegate->touchesEnded(set, NULL);
        }
    }
    
    void CCEGLView::touchesCancelled(CCSet *set)
    {
        if (m_pDelegate) {
            m_pDelegate->touchesCancelled(set, NULL);
        }
    }

    int CCEGLView::setDeviceOrientation(int eOritation)
    {
        do 
        {
            bool bVertical = (CCDeviceOrientationPortrait == eOritation
                    || kCCDeviceOrientationPortraitUpsideDown == eOritation) ? true : false;

            CC_BREAK_IF(m_bOrientationReverted && bVertical != m_bOrientationInitVertical);
            CC_BREAK_IF(! m_bOrientationReverted && bVertical == m_bOrientationInitVertical);

            m_bOrientationReverted = (bVertical == m_bOrientationInitVertical) ? false : true;

            [[MacGLView sharedMacGLView] changeDeviceOrientation]; 
        }while(0);
        return m_eInitOrientation;
    }
    
    void CCEGLView::setViewPortInPoints(float x, float y, float w, float h)
    {
        glViewport((GLint)x, (GLint)y, (GLint)w, (GLint)h);
    }
    
    void CCEGLView::setScissorInPoints(float x, float y, float w, float h)
    {
        glScissor((GLint)x, (GLint)y, (GLint)w, (GLint)h);
    }
    
    void CCEGLView::setIMEKeyboardState(bool bOpen)
    {
        if (bOpen)
        {
            [[MacGLView sharedMacGLView] becomeFirstResponder];
        }
        else
        {
            [[MacGLView sharedMacGLView] resignFirstResponder];
        }
    }
    
    CCEGLView& CCEGLView::sharedOpenGLView()
    {
        CC_ASSERT(s_pMainWindow);
        return *s_pMainWindow;
    }
    
} // end of namespace cocos2d;
