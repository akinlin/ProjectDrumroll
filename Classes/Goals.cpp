//
//  Goals.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/28/13.
//
//

#include "Goals.h"
#include "ScreenHelper.h"

// TODO: review if this should be part of the spritehelper class
enum goalTab
{
    goal_1Tag = 0,
    goal_2Tag = 1,
    goal_3Tag = 2
};

enum goalTabItems
{
    tab_textTag = 0,
    tab_iconTag = 1
};

Goals::Goals()
{
    // turn on touch events
    setTouchEnabled( true );
    
    // TEMP HACK
    scoreTextOffsetX = VisibleRect::getScaledFont(10);
    scoreTextOffsetY = VisibleRect::getScaledFont(35);
    
    // create the goals sprite
    goalsTab = CCSprite::create("goalsTab.png");
    goalsTab->setScale(VisibleRect::getScale());
    goalsTab->setAnchorPoint(CCPointZero);
    CCSize screenSize = VisibleRect::getVisibleRect().size;
    CCSize goalsTabSize = goalsTab->getContentSize();
    goalsTab->setPosition(ccp(screenSize.width - VisibleRect::getScaledFont(50), (screenSize.height - goalsTabSize.height)/2));
    addChild(goalsTab);
    
    m_goalsWidth = goalsTabSize.width;
    m_goalsHeight = goalsTabSize.height;
    
    // goals list
    goal_1 = new GoalItem(CCLabelTTF::create("Interact less then 40 times", "Arial", VisibleRect::getScaledFont(15)), true);
    goal_2 = new GoalItem(CCLabelTTF::create("Score more than 1000 points", "Arial", VisibleRect::getScaledFont(15)), true);
    goal_3 = new GoalItem(CCLabelTTF::create("Get a combo larger than 5x", "Arial", VisibleRect::getScaledFont(15)), true);
    goal_1->setAnchorPoint(CCPointZero);
    goal_2->setAnchorPoint(CCPointZero);
    goal_3->setAnchorPoint(CCPointZero);
    
    // set the goal locations
    int xPos = goalsTab->getPositionX();
    int yPos = goalsTab->getPositionY();
    goal_1->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY));
    goal_2->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 2));
    goal_3->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 3));
    
    addChild(goal_1, goal_1Tag);
    addChild(goal_2, goal_2Tag);
    addChild(goal_3, goal_3Tag);
    
    m_isDrawerAjar = false;
}

Goals::~Goals()
{
    // delete the GoalItems
    delete goal_1;
    delete goal_2;
    delete goal_3;
}

float Goals::getWidth()
{
    // assuming all pieces are the same size
    return m_goalsWidth;
}

float Goals::getHeight()
{
    // assuming all pieces are the same size
    return m_goalsHeight;
}

void Goals::handleTouch(CCPoint p)
{
    CCLog("Touch_X = %d", p.x);
    CCLog("Touch_Y = %d", p.y);
    // check if location is within grid bounds
    if (goalsTab->getPositionX() <= p.x && goalsTab->getPositionX() + getWidth() >= p.x)
    {
        if (goalsTab->getPositionY() <= p.y && goalsTab->getPositionY() + getHeight() >= p.y)
        {
            // touch location is on the goals tab slide the tab out
            CCSize screenSize = VisibleRect::getVisibleRect().size;
            CCSize goalsTabSize = goalsTab->getTextureRect().size;
            int xPos;
            int yPos;
            
            if (!m_isDrawerAjar)
            {
                xPos = screenSize.width - goalsTabSize.width;
                yPos = (screenSize.height - goalsTabSize.height)/2;
                
                goalsTab->setPosition(ccp(xPos, yPos));
                m_isDrawerAjar = true;
                
                goal_1->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY));
                goal_2->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 2));
                goal_3->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 3));
            }
            else
            {
                xPos = screenSize.width - VisibleRect::getScaledFont(50);
                yPos = (screenSize.height - goalsTabSize.height)/2;
                
                goalsTab->setPosition(ccp(xPos, yPos));
                m_isDrawerAjar = false;
                
                goal_1->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY));
                goal_2->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 2));
                goal_3->setPosition(ccp(xPos + scoreTextOffsetX,yPos + goalsTabSize.height - scoreTextOffsetY * 3));
            }
            
            CCLog("Goals Touch handled");
        }
    }
}

void Goals::setGoalStatus(bool goalStatus, int goalIndex)
{
    switch (goalIndex)
    {
        case 0:
            goal_1->setIsGoalComplete(goalStatus);
            break;
            
        case 1:
            goal_2->setIsGoalComplete(goalStatus);
            break;
            
        case 2:
            goal_3->setIsGoalComplete(goalStatus);
            break;
            
        default:
            break;
    }
}

bool Goals::getGoalStatus(int goalIndex)
{
    switch (goalIndex)
    {
        case 0:
            return goal_1->getIsGoalComplete();
            break;
            
        case 1:
            return goal_2->getIsGoalComplete();
            break;
            
        case 2:
            return goal_3->getIsGoalComplete();
            break;
            
        default:
            return false;
            break;
    }
}

bool Goals::areGoalsComplete()
{
    // check all the goals and return false if any are not complete
    if (!goal_1->getIsGoalComplete())
    {
        return false;
    }
    
    if (!goal_2->getIsGoalComplete())
    {
        return false;
    }
    
    if (!goal_3->getIsGoalComplete())
    {
        return false;
    }
    
    return true;
}

void Goals::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        handleTouch( location );
    }
}

// GoalItem Class
GoalItem::GoalItem(CCLabelTTF* goalText, bool isGoalComplete)
{
    m_goalText = goalText;
    m_goalText->setColor(ccBLACK);
    m_goalText->setAnchorPoint(CCPointZero);
    m_goalText->setPositionX(VisibleRect::getScaledFont(20) + VisibleRect::getScaledFont(10));
    
    m_goalComplete = true;
    m_goalIcon = CCSprite::create("goalComplete.png");
    m_goalIcon->setScale(VisibleRect::getScale());
    m_goalIcon->setAnchorPoint(CCPointZero);
    
    addChild(m_goalText, tab_textTag);
    addChild(m_goalIcon, tab_iconTag);
}

GoalItem::~GoalItem()
{
    
}

void GoalItem::setIsGoalComplete(bool isGoalComplete)
{
    m_goalComplete = isGoalComplete;
    
    if (isGoalComplete)
    {
        m_goalIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage("goalComplete.png"));
    }
    else
    {
        m_goalIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage("goalFailed.png"));
    }
}

bool GoalItem::getIsGoalComplete()
{
    return m_goalComplete;
}
