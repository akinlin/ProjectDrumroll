//
//  Grid.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#include "Grid.h"
#include "GamePiece.h"
#include "ScreenHelper.h"

enum ToucState
{
    interact = 0,
    eliminate = 1
};

Grid::Grid()
{
    setTouchEnabled( true );
    
    // create game pieces and fill the grid
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            // create a piece and assign it to the grid location
            GamePiece* gamePieceSprite = new GamePiece();
            gamePieceSprite->setPosition(ccp(j * gamePieceSprite->getTextureWidth(), i * gamePieceSprite->getTextureHeight()));
            gamePieceSprite->setAnchorPoint(CCPointZero);
            gridTable[i][j] = gamePieceSprite;
            
            addChild(gridTable[i][j]);
        }
    }
    this->setAnchorPoint(CCPointZero);
    // set content size to grid size, assuming all pieces are the same size
    this->setContentSize(CCSizeMake(gridTable[0][0]->getTextureWidth() * GRID_COLS, gridTable[0][0]->getTextureHeight() * GRID_ROWS));
    
    touchState = interact;
}

Grid::~Grid()
{
    // destroy all of the game pieces in the grid
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            // if there is a piece at this location destroy it
            if (gridTable[i][j] != NULL)
            {
                delete gridTable[i][j];
            }
        }
    }
}

GamePiece* Grid::getGamePieceAtIndex(int row, int col)
{
    return gridTable[row][col];
}

GamePiece* Grid::getGamePieceAtLocation(CCPoint p)
{
    int row = (p.x-getPositionX())/VisibleRect::getScaledFont(32);
    int col = (p.y-getPositionY())/VisibleRect::getScaledFont(32);
    CCLog("ROWCOL: x=%d y=%d", row, col);
    
    return getGamePieceAtIndex(col, row);
}

float Grid::getWidth()
{
    // assuming all pieces are the same size
    // just using the first piece to calculate dimentions
    return this->getContentSize().width;
}

float Grid::getHeight()
{
    // assuming all pieces are the same size
    // just using the first piece to calculate dimentions
    return this->getContentSize().height;
}

void Grid::handleTouch(CCPoint p)
{
    CCLog("Touch_X = %d", p.x);
    CCLog("Touch_Y = %d", p.y);
    // check if location is within grid bounds
    if (getPositionX() <= p.x && getPositionX() + getWidth() >= p.x)
    {
        if (getPositionY() <= p.y && getPositionY() + getHeight() >= p.y)
        {
            // touch location is within the grid
            
            // find the piece selected
            GamePiece* gamePieceSprite = getGamePieceAtLocation(p);
            
            if (gamePieceSprite != NULL)
            {
                // handle the touch according to touchState
                if (touchState == interact)
                {
                    // do something with it to test the touch location
                    gamePieceSprite->switchToRandomPiece();
                }
                else
                {
                    // do something with it to test the touch location
                    eliminateGamePieces();
                }
                CCLog("Touch handled");
            }
        }
    }
}

void Grid::toggleTouchType()
{
    if (touchState == interact)
    {
        touchState = eliminate;
    }
    else
    {
        touchState = interact;
    }
}

void Grid::eliminateGamePieces()
{
    // check all linked pieces and remove them
    
}

void Grid::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        handleTouch( location );
        //addNewSpriteAtPosition( location );
    }
}



