//
//  Grid.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#ifndef __ProjectDrumroll__Grid__
#define __ProjectDrumroll__Grid__

#include "cocos2d.h"
#include "GamePiece.h"
USING_NS_CC;

const int GRID_COLS = 5;
const int GRID_ROWS = 5;

class Grid : public CCLayer
{
public:
    Grid();
    ~Grid();
    
    GamePiece* getGamePieceAtIndex(int row, int col);
    CCPoint getIndexAtGamePiece(GamePiece* basePiece);
    GamePiece* getGamePieceAtLocation(CCPoint p);
    
    float getWidth();
    float getHeight();
    // handle the touch event at a given coordinate
    void handleTouch(CCPoint p);
    
    void toggleTouchType();
    void setInteractTouchType();
    void setEliminateTouchType();
    int getTouchState();
    int eliminateGamePieces(GamePiece* basePiece, int comboCount);
    
    // touch functions
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    bool isLevelComplete();
    int getCurrentScore();
    int getInteractionCount();
    int getComboCount();
    bool m_IsRecursiveMatchCheck;
    
private:
    GamePiece* gridTable[GRID_ROWS][GRID_COLS];
    int m_score;
    int m_touchState;
    int m_interactionState;
    GamePiece* m_interactionGamePiece;
    
    int m_gridWidth;
    int m_gridHeight;
    int m_pieceTextureWidth;
    int m_pieceTextureHeight;
    int m_highComboCount;
    int m_interactionCount;
    
    void setPieceLocaiton(int row, int col);
    // returns the width of the piece referenced with grid padding
    int getPieceWidth();
    // returns the height of the piece referenced with grid padding
    int getPieceHeight();
    
    // after an elimination move, reset the grid after gravity drop
    void recalculateGrid();
    
    // interaction handling functions
    void handleSlideMove(CCPoint location);
    void handleRotaryMove(CCPoint location);
    void handleSwitchInteraction(GamePiece* gamePieceSprite);
    void handleFlipInteraction(GamePiece* gamePieceSprite);
    void handleDPadFlipInteraction(GamePiece* gamePieceSprite);
};

#endif /* defined(__ProjectDrumroll__Grid__) */
