//
//  HUD.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/24/13.
//
//

#include "HUD.h"
#include "ScreenHelper.h"
#include "Grid.h"
#include "TitleScene.h"

HUD::HUD()
{
    // turn on touch events
    setTouchEnabled( true );
    
    // display the top and bottom bars
    CCSprite* topHud = CCSprite::create("HUDBar.png");
    topHud->setScale(VisibleRect::getScale());
    // position the sprite on the top of the screen
    topHud->setAnchorPoint(CCPointZero);
    topHud->setPosition(ccp(0, VisibleRect::getScaledFont(430)));
    // add the sprite as a child to this layer
    addChild(topHud, 0);
    
    CCSprite* botHud = CCSprite::create("HUDBar.png");
    botHud->setScale(VisibleRect::getScale());
    // position the sprite on the bottom of the screen
    botHud->setAnchorPoint(CCPointZero);
    botHud->setPosition(VisibleRect::leftBottom());
    // add the sprite as a child to this layer
    addChild(botHud, 0);
    
    // display the score value
    char scoreDisplayString[100];
    sprintf(scoreDisplayString, "Score: 0");
    m_scoreDisplayString = CCLabelTTF::create(scoreDisplayString, "Arial", VisibleRect::getScaledFont(15));
    m_scoreDisplayString->setAnchorPoint(CCPointZero);
    // yeah yeah its hardcoded, i just didn't want to do that math right now
    m_scoreDisplayString->setPosition(ccp(VisibleRect::getScaledFont(30), VisibleRect::getScaledFont(450)));
    addChild(m_scoreDisplayString);
    
    // display the score value
    char levelDisplayString[100];
    sprintf(scoreDisplayString, "Level: 1");
    m_levelDisplayString = CCLabelTTF::create(levelDisplayString, "Arial", VisibleRect::getScaledFont(15));
    m_levelDisplayString->setAnchorPoint(CCPointZero);
    // yeah yeah its hardcoded, i just didn't want to do that math right now
    m_levelDisplayString->setPosition(ccp(VisibleRect::getScaledFont(250), VisibleRect::getScaledFont(450)));
    addChild(m_levelDisplayString);
    
    // display the quit button
    CCMenuItemImage* quitButton = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HUD::returnToMenu));
    quitButton->setPosition(ccp(VisibleRect::getScaledFont(300),VisibleRect::getScaledFont(30)));
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(quitButton, NULL);
    pMenu->setPosition( CCPointZero );
    addChild(pMenu);
}

HUD::~HUD()
{
    // may not need a destrcutor
}

void HUD::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
//    //Add a new body/atlas sprite at the touched location
//    CCSetIterator it;
//    CCTouch* touch;
//    
//    for( it = touches->begin(); it != touches->end(); it++)
//    {
//        touch = (CCTouch*)(*it);
//        
//        if(!touch)
//            break;
//        
//        CCPoint location = touch->getLocationInView();
//        
//        location = CCDirector::sharedDirector()->convertToGL(location);
//        
//        handleTouch( location );
//    }
}

void HUD::returnToMenu(CCObject* pSender)
{
    CCScene *pScene = NULL;
    pScene = TitleScene::scene();
            
    // run
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}

void HUD::updateScore(int score)
{
    char scoreDisplayString[100];
    sprintf(scoreDisplayString, "Score: %d", score);
    m_scoreDisplayString->setString(scoreDisplayString);
}

void HUD::updateLevel(int level)
{
    char levelDisplayString[100];
    sprintf(levelDisplayString, "Level: %d", level);
    m_levelDisplayString->setString(levelDisplayString);
}
