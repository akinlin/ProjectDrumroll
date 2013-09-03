//
//  GameScene.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#ifndef __ProjectDrumroll__GameScene__
#define __ProjectDrumroll__GameScene__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Grid.h"
#include "HUD.h"
#include "Goals.h"
USING_NS_CC;

class GameScene : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender);
    void menuInteractionCallback(CCObject* pSender);
    void menuEliminateCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
private:
// Member Components
    // Menu to handle the game
    CCMenu* m_pItemMenu;
    // Grid where all the gameplay happens
    Grid* m_gridReference;
        // Eliminate and Interact Buttons (should be in the HUD)
        CCMenu* m_touchStateMenu;
    // HUD for displaying information
    HUD* m_hudReference;
    // Background (Should probably be its own class)
    CCSprite* m_backgroundReference;
    // goals tab reference
    Goals* m_goalsTab;
    
    // Level
    int m_currentLevel;
    // Score
    int m_currentScore;
    int m_scoreCache;
    // Combo
    int m_highestCombo;
    // Interaction count
    int m_interactionCount;
    
// Member Management
    // Level state
    void checkForEndOfLevel();
    // Score update
    void refreshScore();
    // Goals udpate
    void updateGoals();
    // Touch state
    void refreshTouchState();
    // void update all
    void updateAll();
    
// Member helper functions
    // create the gird
    void createGrid();
    // change level
    void nextLevel();
    // store level cache
    void storeScoreCache();
};

#endif /* defined(__ProjectDrumroll__GameScene__) */
