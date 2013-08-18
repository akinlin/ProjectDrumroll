//
//  TitleScene.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/15/13.
//
//

#ifndef __ProjectDrumroll__TitleScene__
#define __ProjectDrumroll__TitleScene__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TitleScene);
    
private:
    cocos2d::CCMenu* m_pItemMenu;
};

#endif /* defined(__ProjectDrumroll__TitleScene__) */
