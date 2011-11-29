#ifndef __CC_EGLVIEW_MAC_H
#define __CC_EGLVIEW_MAC_H

#import "CCCommon.h"
#import "CCGeometry.h"


namespace cocos2d {
    class CCSet;
    class CCTouch;
    class EGLTouchDelegate;
    class CCSize;
    
    class CC_DLL CCEGLView
    {
    public:
        CCEGLView();
        ~CCEGLView();
        
        CCSize getSize();
        bool isOpenGLReady();
        bool canSetContentScaleFactor();
        void setContentScaleFactor(float contentScaleFactor);
        
        void release();
        void setTouchDelegate(EGLTouchDelegate * pDelegate);
        void swapBuffers();
        
        int setDeviceOrientation(int eOritation);
        void setFullScreen(bool isFullScreen);
        void setViewPortInPoints(float x, float y, float w, float h);
        void setScissorInPoints(float x, float y, float w, float h);
        
        void setIMEKeyboardState(bool bOpen);
        
        void touchesBegan(CCSet *set);
        void touchesMoved(CCSet *set);
        void touchesEnded(CCSet *set);
        void touchesCancelled(CCSet *set);
        
        void resize(int width, int height);
        void centerWindow();
        void setScreenScale(float factor);
        
        static CCEGLView& sharedOpenGLView();
    private:
        EGLTouchDelegate *m_pDelegate;
        bool                m_bCaptured;
        bool				m_bOrientationReverted;
        bool				m_bOrientationInitVertical;
        int					m_eInitOrientation;
        
        CCRect              m_originalWinRect;
        bool                m_isFullScreen;
        
        CCPoint             m_mousePoint;
        
        float               m_fScreenScaleFactor;
    };
    
}   // end of namespace   cocos2d


#endif
