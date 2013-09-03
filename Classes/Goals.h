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

// Right now this is purely a display item. GoalsTab will have the logic for completed goals
class GoalItem : public CCLayer
{
public:
    GoalItem(CCLabelTTF* goalText, bool isGoalComplete);
    ~GoalItem();
    
    void setIsGoalComplete(bool isGoalComplete);
    bool getIsGoalComplete();
    
private:
    CCSprite* m_goalIcon;
    CCLabelTTF* m_goalText;
    
    bool m_goalComplete;
};

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
    
    // set and get goal status (probably need to review how this is done)
    void setGoalStatus(bool goalStatus, int goalIndex);
    bool getGoalStatus(int goalIndex);
    // return true if the all the goals are complete/false if any are false
    bool areGoalsComplete();
    
private:
    int m_goalsWidth;
    int m_goalsHeight;
    int scoreTextOffsetX;
    int scoreTextOffsetY;
    
    CCSprite* goalsTab;
    GoalItem* goal_1;
    GoalItem* goal_2;
    GoalItem* goal_3;
    
    bool m_isDrawerAjar;
};

#endif /* defined(__ProjectDrumroll__Goals__) */
