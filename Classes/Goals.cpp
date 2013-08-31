//
//  Goals.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/28/13.
//
//

#include "Goals.h"
#include "ScreenHelper.h"

Goals::Goals()
{
    // turn on touch events
    setTouchEnabled( true );
    
    // create the goals sprite
    goalsTab = CCSprite::create("goalsTab.png");
    goalsTab->setAnchorPoint(CCPointZero);
    CCSize screenSize = VisibleRect::getVisibleRect().size;
    CCSize goalsTabSize = goalsTab->getTextureRect().size;
    goalsTab->setPosition(ccp(screenSize.width - 50, (screenSize.height - goalsTabSize.height)/2));
    addChild(goalsTab);
    
    m_goalsWidth = goalsTabSize.width;
    m_goalsHeight = goalsTabSize.height;
    
    // goals list
    goal_1 = CCLabelTTF::create("Interact less then 40 times", "Arial", VisibleRect::getScaledFont(15));
    goal_2 = CCLabelTTF::create("Score more than 1000 points", "Arial", VisibleRect::getScaledFont(15));
    goal_3 = CCLabelTTF::create("Get a combo larger than 5x", "Arial", VisibleRect::getScaledFont(15));
    goal_1->setAnchorPoint(CCPointZero);
    goal_2->setAnchorPoint(CCPointZero);
    goal_3->setAnchorPoint(CCPointZero);
    goal_1->setColor(ccBLACK);
    goal_2->setColor(ccBLACK);
    goal_3->setColor(ccBLACK);
    
    // set the goal locations
    int xPos = goalsTab->getPositionX();
    int yPos = goalsTab->getPositionY();
    goal_1->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 20));
    goal_2->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 40));
    goal_3->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 60));
    
    addChild(goal_1);
    addChild(goal_2);
    addChild(goal_3);
    
    m_isDrawerAjar = false;
}

Goals::~Goals()
{
    
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
            int xPos = goalsTab->getPositionX();
            int yPos = goalsTab->getPositionY();
            
            if (!m_isDrawerAjar)
            {
                goalsTab->setPosition(ccp(screenSize.width - goalsTabSize.width, (screenSize.height - goalsTabSize.height)/2));
                m_isDrawerAjar = true;
                
//                goal_1->setPosition(ccp(xPos + goalsTabSize.width + 10,yPos + goalsTabSize.height - 20));
//                goal_2->setPosition(ccp(xPos + goalsTabSize.width + 10,yPos + goalsTabSize.height - 40));
//                goal_3->setPosition(ccp(xPos + goalsTabSize.width + 10,yPos + goalsTabSize.height - 60));
            }
            else
            {
                goalsTab->setPosition(ccp(screenSize.width - 50, (screenSize.height - goalsTabSize.height)/2));
                m_isDrawerAjar = false;
                
                goal_1->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 20));
                goal_2->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 40));
                goal_3->setPosition(ccp(xPos + 10,yPos + goalsTabSize.height - 60));
            }
            
            CCLog("Goals Touch handled");
        }
    }
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