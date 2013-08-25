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
    CCMenu* m_touchStateMenu;
    Grid* m_gridReference;
    HUD* m_hudReference;
    CCSprite* m_backgroundReference;
    
    void checkForEndOfLevel();
    void refreshScore();
    void refreshTouchState();
};

#endif /* defined(__ProjectDrumroll__GameScene__) */
