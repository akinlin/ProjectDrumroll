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
    
    CCRect getPieceColor();
    CCRect getInteractionType();
    
    int getTextureWidth();
    int getTextureHeight();
    
    void switchToRandomPiece();
    
private:
    int s_color;
    int s_interactionType;
    Blocks* m_BlocksSprite;
};

#endif /* defined(__ProjectDrumroll__GamePiece__) */
