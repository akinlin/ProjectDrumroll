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

using namespace cocos2d;
using namespace CocosDenshion;

const int LINE_SPACE = 50;
const int ITEM_COUNT = 2;
const std::string menuItem[ITEM_COUNT] =
{
    "Game Over",
    "Next Level"
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
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        CCLabelTTF* label = CCLabelTTF::create(menuItem[i].c_str(), "Arial", VisibleRect::getScaledFont(20));
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(GameScene::menuCallback));
        pMenuItem->setAnchorPoint(CCPointZero);
        
        m_pItemMenu->addChild(pMenuItem, i + 10000);
    }
    
    m_pItemMenu->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getWinSize().width, (ITEM_COUNT + 1) * LINE_SPACE));
    m_pItemMenu->setPosition(ccp( CCDirector::sharedDirector()->getWinSize().width - VisibleRect::getScaledFont(200), CCDirector::sharedDirector()->getWinSize().height - VisibleRect::getScaledFont(100)));
    m_pItemMenu->alignItemsVerticallyWithPadding(5);
    this->addChild(m_pItemMenu, 1);
    
    // add a label shows "Game Scene [LEVEL]"
    // create and initialize a label
    char title[256];
    sprintf(title, "Game Scene %d", LEVEL);
    CCLabelTTF* pLabel = CCLabelTTF::create(title, "Thonburi", VisibleRect::getScaledFont(34));
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - VisibleRect::getScaledFont(20)) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//    
//    // position the sprite on the center of the screen
//    pSprite->setPosition( ccp(size.width/2, size.height/2) );
//    
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    
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
            pScene = GameScene::scene(); break;
        default:
            break;
    }
    
    // run
    if (pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
    
}
