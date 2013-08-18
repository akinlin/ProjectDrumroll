//
//  ScreenHelper.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#ifndef __ProjectDrumroll__ScreenHelper__
#define __ProjectDrumroll__ScreenHelper__

#include "cocos2d.h"
USING_NS_CC;

class VisibleRect
{
public:
    static CCRect getVisibleRect();
    static CCRect getTargetRect();
    
    static CCPoint left();
    static CCPoint right();
    static CCPoint top();
    static CCPoint bottom();
    static CCPoint center();
    static CCPoint leftTop();
    static CCPoint rightTop();
    static CCPoint leftBottom();
    static CCPoint rightBottom();
    
    static int getScaledFont(int fontSize);
    static float getScale();
private:
    static void lazyInit();
    static CCRect s_visibleRect;
    static CCRect s_targetRect;
};

#endif /* defined(__ProjectDrumroll__ScreenHelper__) */
