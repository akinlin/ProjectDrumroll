//
//  TitleScene.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#include "TitleScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int LINE_SPACE = 50;
const int ITEM_COUNT = 3;
const std::string menuItem[ITEM_COUNT] =
{
    "Start Game",
    "Hello Stupid Physics",
    "Exit"
};

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    //add the menu item for back to main menu
    int contentHeight = 0;
    int contentWidth = 0;
    m_pItemMenu = CCMenu::create();
    for (int i = 0; i < ITEM_COUNT; ++i)
    {
        CCLabelTTF* label = CCLabelTTF::create(menuItem[i].c_str(), "Arial", VisibleRect::getScaledFont(20));
        CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TitleScene::menuCallback));
        pMenuItem->setAnchorPoint(CCPointZero);
        
        contentHeight = MAX(contentHeight, pMenuItem->getContentSize().height);
        contentWidth = MAX(contentWidth, pMenuItem->getContentSize().width);
        CCLog("Height = %d", contentHeight);
        CCLog("Width = %d", contentWidth);
        
        m_pItemMenu->addChild(pMenuItem, i + 10000);
    }
    
    m_pItemMenu->setContentSize(CCSizeMake(contentWidth, (ITEM_COUNT - 1) * contentHeight));
    m_pItemMenu->setPosition(ccp( CCDirector::sharedDirector()->getWinSize().width - m_pItemMenu->getContentSize().width, m_pItemMenu->getContentSize().height));
    m_pItemMenu->alignItemsVertically();
    this->addChild(m_pItemMenu, 1);
        
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
//    CCLabelTTF* pLabel = CCLabelTTF::create("Title Scene", "Thonburi", VisibleRect::getScaledFont(34));
//    
//    // ask director the window size
//    CCSize size = VisibleRect::getVisibleRect().size;
//    
//    // position the label on the center of the screen
//    pLabel->setPosition( ccp(size.width / 2, size.height - VisibleRect::getScaledFont(20)) );
//    
//    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setScale(VisibleRect::getScale());
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}

void TitleScene::menuCallback(CCObject* pSender)
{
    // get the userdata, it's the index of the menu item clicked
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    int nIdx = pMenuItem->getZOrder() - 10000;
    
    CCLog("Index = %d", nIdx);
    
    if (nIdx == ITEM_COUNT - 1)
    {
        // last item in the list is exit
        CCDirector::sharedDirector()->end();
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
    else
    {
        // create the scene and run it
        CCScene *pScene = NULL;
        switch (nIdx)
        {
        case 0:
            pScene = GameScene::scene(); break;
        case 1:
            pScene = HelloWorld::scene(); break;
        default:
            break;
        }
        
        // run
        if (pScene)
        {
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
    
}

