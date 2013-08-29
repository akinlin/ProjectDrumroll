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
            
            if (!m_isDrawerAjar)
            {
                goalsTab->setPosition(ccp(screenSize.width - goalsTabSize.width, (screenSize.height - goalsTabSize.height)/2));
                m_isDrawerAjar = true;
            }
            else
            {
                goalsTab->setPosition(ccp(screenSize.width - 50, (screenSize.height - goalsTabSize.height)/2));
                m_isDrawerAjar = false;
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