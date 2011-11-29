#ifndef __CC_ACCELEROMETER_MAC_H
#define __CC_ACCELEROMETER_MAC_H

#include "CCAccelerometerDelegate.h"

namespace  cocos2d {
    
    class CC_DLL CCAccelerometer
    {
    public:
        CCAccelerometer();
        ~CCAccelerometer();
        
        static CCAccelerometer* sharedAccelerometer() { return NULL; }
        
        void removeDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);}
        void setDelegate(CCAccelerometerDelegate* pDelegate) {CC_UNUSED_PARAM(pDelegate);}
    };

    
}//namespace   cocos2d 

#endif
