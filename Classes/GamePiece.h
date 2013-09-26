//
//  GamePiece.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#ifndef __ProjectDrumroll__GamePiece__
#define __ProjectDrumroll__GamePiece__


#include "cocos2d.h"
#include "SpritHelper.h"
USING_NS_CC;

class GamePiece : public CCSprite
{
public:
    GamePiece();
    //GamePiece(GamePiece& gamePiece);
    
    int getPieceColor();
    int getInteractionType();
    
    int getTextureWidth();
    int getTextureHeight();
    
    void switchToRandomPiece();
    void switchToNextPiece();
    
    bool isInElinationCheck();
    void setElinationCheck(bool isInEliminationCheck);
    
    bool isActive();
    void setActive(bool isActive);
    
private:
    int s_color;
    int s_interactionType;
    Blocks* m_BlocksSprite;
    CCLabelTTF* m_interactionSprite;
    
    bool m_isInElinationCheck;
    bool m_isActive;
};

#endif /* defined(__ProjectDrumroll__GamePiece__) */
