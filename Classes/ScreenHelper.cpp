//
//  ScreenHelper.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#include "ScreenHelper.h"

const int targetWidth = 320;
const int targetHeight = 480;

CCRect VisibleRect::s_visibleRect;
CCRect VisibleRect::s_targetRect;

void VisibleRect::lazyInit()
{
    if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
    {
        //  set the visible rect
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
        s_visibleRect.origin = pEGLView->getVisibleOrigin();
        s_visibleRect.size = pEGLView->getVisibleSize();
        
        // set the target rect
        s_targetRect.origin = CCPointZero;
        s_targetRect.size = CCSize(targetWidth, targetHeight);
    }
}

CCRect VisibleRect::getVisibleRect()
{
    lazyInit();
    return CCRectMake(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

CCRect VisibleRect::getTargetRect()
{
    lazyInit();
    return CCRectMake(0, 0, targetWidth, targetHeight);
}

CCPoint VisibleRect::left()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint VisibleRect::right()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint VisibleRect::top()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::bottom()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

CCPoint VisibleRect::center()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint VisibleRect::leftTop()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::rightTop()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

CCPoint VisibleRect::rightBottom()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}

int VisibleRect::getScaledFont(int fontSize)
{
    lazyInit();
        
//    CCLog("s_targetRect.size.height %d", s_targetRect.size.height);
//    CCLog("s_targetRect.size.width %d", s_targetRect.size.width);
//    CCLog("s_visibleRect.size.height %d", s_visibleRect.size.height);
//    CCLog("s_visibleRect.size.width %d", s_visibleRect.size.width);
    
    return fontSize * getScale();
}

float VisibleRect::getScale()
{
    lazyInit();
   
    return MIN(s_visibleRect.size.height / s_targetRect.size.height, s_visibleRect.size.width / s_targetRect.size.width);
}
