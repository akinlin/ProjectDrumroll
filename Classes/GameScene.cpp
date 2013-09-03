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

enum SceneTags {
    kTagBackgroundReference = 1,
    kTagGridReference = 2,
    kTagHUDReference = 3,
    kTagButtonMenu = 4,
    kTagGoalstab
};

enum ButtonMenuTags {
    kTagInteractButtonReference = 1,
    kTagEliminationButtonReference = 2,
    
};

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
    
    // init level
    m_currentLevel = 1;
    
    // init score
    m_currentScore = 0;
    m_scoreCache = 0;
    
    // init combo
    m_highestCombo = 0;
    // init interaction count
    m_interactionCount = 0;
    
    // add background for the main screen"
    m_backgroundReference = CCSprite::create("MainScreen.png");
    m_backgroundReference->setScale(VisibleRect::getScale());
    // position the sprite on the center of the screen
    m_backgroundReference->setPosition( ccp(VisibleRect::getVisibleRect().size.width/2, VisibleRect::getVisibleRect().size.height/2) );
    // add the sprite as a child to this layer
    addChild(m_backgroundReference, kTagBackgroundReference);
        
    // create and add the grid
    createGrid();
    addChild(m_gridReference, kTagGridReference);
    
    // create the HUD
    // create and add the grid
    m_hudReference = new HUD();
    m_hudReference->setPosition(CCPointZero);
    m_hudReference->updateLevel(m_currentLevel);
    this->addChild(m_hudReference, kTagHUDReference);
    
    // create and add the interact and eliminate buttons
    // should probably be in a HUD class
    m_touchStateMenu = CCMenu::create();
    CCMenuItemImage* interactButton = CCMenuItemImage::create("interactButton.png", "interactButton.png", this, menu_selector(GameScene::menuInteractionCallback));
    interactButton->setAnchorPoint(CCPointZero);
    interactButton->setPosition(ccp(VisibleRect::getScaledFont(40), 0));
    m_backgroundReference->setScale(VisibleRect::getScale());
    m_touchStateMenu->addChild(interactButton, kTagInteractButtonReference);
    
    CCMenuItemImage* eliminateButton = CCMenuItemImage::create("eliminateButton.png", "eliminateButton.png", this, menu_selector(GameScene::menuEliminateCallback));
    eliminateButton->setAnchorPoint(CCPointZero);
    eliminateButton->setPosition(ccp(VisibleRect::getScaledFont(180), 0));
    m_backgroundReference->setScale(VisibleRect::getScale());
    m_touchStateMenu->addChild(eliminateButton, kTagEliminationButtonReference);
    
    m_touchStateMenu->setContentSize(CCSizeMake(CCDirector::sharedDirector()->getWinSize().width, VisibleRect::getScaledFont(100)));
    m_touchStateMenu->setAnchorPoint(CCPointZero);
    m_touchStateMenu->setPosition(CCPointZero);
    addChild(m_touchStateMenu, kTagButtonMenu);
    
    // Add the goals tab
    m_goalsTab = new Goals();
    addChild(m_goalsTab, kTagGoalstab);
    
    // schedule the update check
    schedule( schedule_selector(GameScene::updateAll), 0.2f);
    
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
            break;
        case 1:
            // go to the next level
            nextLevel();
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
        // check to see if all the goals are complete
        if (m_goalsTab->areGoalsComplete())
        {
            // go to the next level
            nextLevel();
        }
        else
        {
            // end the game (go back to main menu)
            CCScene *pScene = TitleScene::scene();
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
    }
}

void GameScene::refreshScore()
{
    // get the score from the grid
    int levelScore = m_gridReference->getCurrentScore();
    // add the scoreCache variable, value stored from the previous levels
    m_currentScore = m_scoreCache + levelScore;
    
    // give it to the HUD
    m_hudReference->updateScore(m_currentScore);
}

void GameScene::updateGoals()
{
    // check each of the goals and update state
    // hard coded checks
    if (m_goalsTab->getGoalStatus(0))
    {
        //CCLog("Interaction Count: %d", m_gridReference->getInteractionCount());
        // icon is green
        if (m_gridReference->getInteractionCount() > 40)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(false, 0);
        }
    }
    else
    {
        // icon is red
        if (m_gridReference->getInteractionCount() <= 40)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(true, 0);
        }
    }
    
    if (m_goalsTab->getGoalStatus(1))
    {
        // icon is green
        if (m_gridReference->getCurrentScore() < 1000)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(false, 1);
        }
    }
    else
    {
        // icon is red
        if (m_gridReference->getCurrentScore() >= 1000)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(true, 1);
        }
    }
    
    if (m_goalsTab->getGoalStatus(2))
    {
        // icon is green
        if (m_gridReference->getComboCount() < 5)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(false, 2);
        }
    }
    else
    {
        // icon is red
        if (m_gridReference->getComboCount() > 5)
        {
            // strong coupling with the knowledge that this is the '0' index should change
            m_goalsTab->setGoalStatus(true, 2);
        }
    }
}

void GameScene::updateAll()
{
    // update goals
    updateGoals();
    
    // update score
    refreshScore();
    
    // check for the end of the level (grid returns complete when all pieces are gone)
    checkForEndOfLevel();
}

void GameScene::createGrid()
{
    // create and add the grid
    m_gridReference = new Grid();
    m_gridReference->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2 - m_gridReference->getWidth()/2, CCDirector::sharedDirector()->getWinSize().height/2 - m_gridReference->getHeight()/2));
    
    // set the background tint to the color of the grid touch state
    // assuming the interact state is set, should probably check the state and set the color accordingly
    m_backgroundReference->setColor(ccBLUE);
}

void GameScene::nextLevel()
{
    // remove the grid and create a new one
    createGrid();
    removeChildByTag(kTagGridReference);
    addChild(m_gridReference, kTagGridReference);
    
    // increment the level
    m_currentLevel++;
    m_hudReference->updateLevel(m_currentLevel);
    
    // store the score cache since the score will get reset in the next level
    storeScoreCache();
}

void GameScene::storeScoreCache()
{
    m_scoreCache = m_currentScore;
}
