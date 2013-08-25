//
//  GameScene.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#include "GameScene.h"
#include "TitleScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ScreenHelper.h"

using namespace CocosDenshion;

const int LINE_SPACE = 50;
const int ITEM_COUNT = 4;
const std::string menuItem[ITEM_COUNT] =
{
    "Game Over",
    "Next Level",
    "Toogle Touch State"
};

static int LEVEL = 0;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // increment the level
    ++LEVEL;
    
    //add the menu item for back to main menu
    // removing to replace with HUD controls
//    m_pItemMenu = CCMenu::create();
//    for (int i = 0; i < ITEM_COUNT; ++i)
//    {
//        CCLabelTTF* label = CCLabelTTF::create(menuItem[i].c_str(), "Arial", VisibleRect::getScaledFont(20));
//        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(GameScene::menuCallback));
//        pMenuItem->setAnchorPoint(CCPointZero);
//        
//        m_pItemMenu->addChild(pMenuItem, i + 10000);
//    }
//    
//    m_pItemMenu->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getWinSize().width, (ITEM_COUNT + 1) * LINE_SPACE));
//    m_pItemMenu->setPosition(ccp( CCDirector::sharedDirector()->getWinSize().width - VisibleRect::getScaledFont(200), CCDirector::sharedDirector()->getWinSize().height - VisibleRect::getScaledFont(100)));
//    m_pItemMenu->alignItemsVerticallyWithPadding(5);
//    this->addChild(m_pItemMenu, 1);
    
    // add a label shows "Game Scene [LEVEL]"
//    // create and initialize a label
//    char title[256];
//    sprintf(title, "Game Scene %d", LEVEL);
//    CCLabelTTF* pLabel = CCLabelTTF::create(title, "Thonburi", VisibleRect::getScaledFont(34));
//    // ask director the window size
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - VisibleRect::getScaledFont(20)) );
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
    
    // add background for the main screen"
    m_backgroundReference = CCSprite::create("MainScreen.png");
    m_backgroundReference->setScale(VisibleRect::getScale());
    // position the sprite on the center of the screen
    m_backgroundReference->setPosition( ccp(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height/2) );
    // add the sprite as a child to this layer
    this->addChild(m_backgroundReference, 0);
        
    // create and add the grid
    m_gridReference = new Grid();
    m_gridReference->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2 - m_gridReference->getWidth()/2, CCDirector::sharedDirector()->getWinSize().height/2 - m_gridReference->getHeight()/2));
    this->addChild(m_gridReference, 2);
    
    // set the background tint to the color of the grid touch state
    // assuming the interact state is set, should probably check the state and set the color accordingly
    m_backgroundReference->setColor(ccBLUE);
    
    // create the HUD
    // create and add the grid
    m_hudReference = new HUD();
    m_hudReference->setPosition(CCPointZero);
    m_hudReference->updateLevel(LEVEL);
    this->addChild(m_hudReference, 3);
    
    // create and add the interact and eliminate buttons
    // should probably be in a HUD class
    m_touchStateMenu = CCMenu::create();
    CCMenuItemImage* interactButton = CCMenuItemImage::create("interactButton.png", "interactButton.png", this, menu_selector(GameScene::menuInteractionCallback));
    interactButton->setAnchorPoint(CCPointZero);
    interactButton->setPosition(ccp(VisibleRect::getScaledFont(40), 0));
    m_backgroundReference->setScale(VisibleRect::getScale());
    m_touchStateMenu->addChild(interactButton, 2);
    
    CCMenuItemImage* eliminateButton = CCMenuItemImage::create("eliminateButton.png", "eliminateButton.png", this, menu_selector(GameScene::menuEliminateCallback));
    eliminateButton->setAnchorPoint(CCPointZero);
    eliminateButton->setPosition(ccp(VisibleRect::getScaledFont(180), 0));
    m_backgroundReference->setScale(VisibleRect::getScale());
    m_touchStateMenu->addChild(eliminateButton, 1);
    
    m_touchStateMenu->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getWinSize().width, VisibleRect::getScaledFont(100)));
    m_touchStateMenu->setAnchorPoint(CCPointZero);
    m_touchStateMenu->setPosition(CCPointZero);
    addChild(m_touchStateMenu, 4);
    
    // schedule the level complete check
    schedule( schedule_selector(GameScene::checkForEndOfLevel), 0.2f);
    // schedule the score check
    schedule( schedule_selector(GameScene::refreshScore), 0.2f);
    
    return true;
}

void GameScene::menuCallback(CCObject* pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;
    
    CCLog("Index = %d", nIdx);
    
    // create the scene and run it
    CCScene *pScene = NULL;
    switch (nIdx)
    {
        case 0:
            pScene = TitleScene::scene();
            LEVEL = 0;
            break;
        case 1:
            pScene = GameScene::scene();
            m_backgroundReference->setColor(ccBLUE);
            break;
        case 2:
            // change the touch state
            m_gridReference->toggleTouchType();
            // tint the background for the interaction type
            if (m_gridReference->getTouchState() == 0)
            {
                // hard coded to be the interaction state so set to blue
                m_backgroundReference->setColor(ccBLUE);
            }
            else if(m_gridReference->getTouchState() == 1)
            {
                // hard coded to be the elimination state so set to red
                m_backgroundReference->setColor(ccRED);
            }
            break;
        default:
            break;
    }
    
    // run
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    
}

void GameScene::menuInteractionCallback(CCObject* pSender)
{
    // change the touch state
    m_gridReference->setInteractTouchType();
    // hard coded to be the interaction state so set to blue
    m_backgroundReference->setColor(ccBLUE);
}

void GameScene::menuEliminateCallback(CCObject* pSender)
{
    // change the touch state
    m_gridReference->setEliminateTouchType();
    // hard coded to be the elimination state so set to red
    m_backgroundReference->setColor(ccRED);
}

void GameScene::checkForEndOfLevel()
{
    if (m_gridReference->isLevelComplete())
    {
        // change to the next level
        CCScene *pScene = NULL;
        pScene = GameScene::scene();
        // run
        if (pScene)
        {
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
}

void GameScene::refreshScore()
{
    // get the score from the grid
    int currentScore = m_gridReference->getCurrentScore();
    
    // give it to the HUD
    m_hudReference->updateScore(currentScore);
}
