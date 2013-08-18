//
//  Grid.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#ifndef __ProjectDrumroll__Grid__
#define __ProjectDrumroll__Grid__

#include "cocos2d.h"
USING_NS_CC;

class Grid
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

#endif /* defined(__ProjectDrumroll__Grid__) */
