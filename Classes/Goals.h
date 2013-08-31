//
//  Goals.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/28/13.
//
//

#ifndef __ProjectDrumroll__Goals__
#define __ProjectDrumroll__Goals__

#include "cocos2d.h"
USING_NS_CC;

class Goals : public CCLayer
{
public:
    Goals();
    ~Goals();
    
    float getWidth();
    float getHeight();
    // handle the touch event at a given coordinate
    void handleTouch(CCPoint p);
    
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    
private:
    int m_goalsWidth;
    int m_goalsHeight;
    
    CCSprite* goalsTab;
    CCLabelTTF* goal_1;
    CCLabelTTF* goal_2;
    CCLabelTTF* goal_3;
    
    bool m_isDrawerAjar;
};

#endif /* defined(__ProjectDrumroll__Goals__) */
