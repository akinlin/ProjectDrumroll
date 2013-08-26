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

enum TouchState
{
    interact = 0,
    eliminate = 1
};

const int GRID_SPACE = 10;

Grid::Grid()//GameScene* parentScene)
{
    // reset score
    m_score = 0;
    
    // turn on touch events
    setTouchEnabled( true );
    
    // create game pieces and fill the grid
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            // create a piece and assign it to the grid location
            GamePiece* gamePieceSprite = new GamePiece();
            
            // set the piece location with space in between
            //setPieceLocaiton(j,i);
            int piecePosX = (j * gamePieceSprite->getTextureWidth()) + (VisibleRect::getScaledFont(GRID_SPACE) * j);
            int piecePoxY = (i * gamePieceSprite->getTextureHeight()) + (VisibleRect::getScaledFont(GRID_SPACE) * i);
            
            gamePieceSprite->setPosition(ccp(piecePosX, piecePoxY));
            gamePieceSprite->setAnchorPoint(CCPointZero);
            gridTable[i][j] = gamePieceSprite;
            
            addChild(gridTable[i][j]);
        }
    }
    // set the anchor point to zero
    setAnchorPoint(CCPointZero);
    
    // set the width and height
    // just using the size of the first piece to calculate dimensions
    m_gridWidth = (gridTable[0][0]->getTextureWidth() * GRID_COLS) + (VisibleRect::getScaledFont(GRID_SPACE) * GRID_COLS);
    m_gridHeight = (gridTable[0][0]->getTextureHeight() * GRID_ROWS) + (VisibleRect::getScaledFont(GRID_SPACE) * GRID_ROWS);
    
    // set content size to grid size, assuming all pieces are the same size
    setContentSize(CCSizeMake(m_gridWidth, m_gridHeight));
    
    m_touchState = interact;
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

CCPoint Grid::getIndexAtGamePiece(GamePiece* basePiece)
{
    // get the piece global location
    CCPoint globalPostion = basePiece->getPosition();
    CCLog("Global Location row:%f col:%f", globalPostion.y, globalPostion.x);
    
    // get the referenced piece width and height
    int pieceWidth = getPieceWidth();
    int pieceHeight = getPieceHeight();
    
    // get the row and col index of the piece
    int row = globalPostion.y/pieceWidth;
    int col = globalPostion.x/pieceHeight;
    CCPoint indexPoint = ccp(col,row);
    CCLog("Created Point row:%f col:%f", indexPoint.y, indexPoint.x);
    
    return indexPoint;
}

GamePiece* Grid::getGamePieceAtLocation(CCPoint p)
{
    // get the referenced piece width and height
    int pieceWidth = getPieceWidth();
    int pieceHeight = getPieceHeight();
    
    // get the row and col index of the piece
    int row = (p.y-getPositionY())/pieceWidth;
    int col = (p.x-getPositionX())/pieceHeight;
    CCLog("ROWCOL: x=%d y=%d", row, col);
    
    // get the piece at that location
    return getGamePieceAtIndex(row, col);
}

float Grid::getWidth()
{
    // assuming all pieces are the same size
    return m_gridWidth;
}

float Grid::getHeight()
{
    // assuming all pieces are the same size
    return m_gridHeight;
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
                if (m_touchState == interact)
                {
                    // do something with it to test the touch location
                    gamePieceSprite->switchToRandomPiece();
                    
                    // take away 5 points for every touch
                    m_score = m_score - 5;
                }
                else
                {
                    // do something with it to test the touch location
                    int comboCount = eliminateGamePieces(gamePieceSprite,0);
                    if (comboCount == 0)
                    {
                        // only one piece was eliminated
                        m_score = m_score - 150;
                    }
                    else
                    {
                        // a combo of two or more was created
                        m_score = m_score + (100*(comboCount+1));
                    }
                }
                CCLog("Touch handled");
            }
        }
    }
}

void Grid::toggleTouchType()
{
    if (m_touchState == interact)
    {
        m_touchState = eliminate;
    }
    else
    {
        m_touchState = interact;
    }
}

void Grid::setInteractTouchType()
{
    m_touchState = interact;
}

void Grid::setEliminateTouchType()
{
    m_touchState = eliminate;
}

int Grid::getTouchState()
{
    return m_touchState;
}

// TODO: This function is bloated as hell. The logic is expanded for readability and debugging.
// Once this is verified as solid it should be moved into a less readable but more efficient form.
int Grid::eliminateGamePieces(GamePiece* basePiece, int comboCount)
{
    CCLog("^^^^^^^^^^^");
    // check all linked pieces and remove them
    // run a recursive function checking for matching pieces in the following order:
    // up, right, down, left (clockwise)
    if(basePiece != NULL && basePiece->isVisible())
    {
        // set the flag to indicate the piece is in an eliminate loop check
        basePiece->setElinationCheck(true);
        
        // get the grid location of the basepiece
        CCPoint basePieceindex = getIndexAtGamePiece(basePiece);
        
        // check up
        float aboveRow = basePieceindex.y + 1.0f;
        CCLog("Check piece row:%f col:%f", basePieceindex.y, basePieceindex.x);
        CCLog("Above piece row:%f col:%f", aboveRow, basePieceindex.x);
        
        // really only need to check if the index is out of bounds in one direction since the
        // basePieceindex is assumed to be valid, but checking both for completeness.
        // similar checks for the rest of the tests
        if (aboveRow > 0 && aboveRow < GRID_ROWS)
        {
            GamePiece* abovePiece = getGamePieceAtIndex(aboveRow, basePieceindex.x);
            CCPoint abovePieceLocation = abovePiece->getPosition();
            CCLog("Actual above piece row:%f col:%f", abovePieceLocation.y, abovePieceLocation.x);
            // first make sure the piece hasn't already been checked
            if (abovePiece != NULL)
            {
                if (!abovePiece->isInElinationCheck())
                {
                    if (basePiece->getPieceColor() == abovePiece->getPieceColor())
                    {
                        CCLog("FOUND MATCH");
                        // piece above matches trigger recursive check with this as a the base piece
                        comboCount = MAX(comboCount, eliminateGamePieces(abovePiece, comboCount+1));
                    }
                    else
                    {
                        CCLog("NO MATCH FOUND");
                    }
                }
                else
                {
                    CCLog("PIECE ALREADY CHECKED");
                }
            }
            else
            {
                CCLog("PIECE NOT VALID");
            }
        }
        else
        {
            CCLog("PIECE OUT OF BOUNDS");
        }
        
        // check right
        float rightCol = basePieceindex.x + 1.0f;
        CCLog("Check piece row:%f col:%f", basePieceindex.y, basePieceindex.x);
        CCLog("Piece to the right row:%f col:%f", basePieceindex.y, rightCol);
        
        // really only need to check if the index is out of bounds in one direction since the
        // basePieceindex is assumed to be valid, but checking both for completeness.
        // similar checks for the rest of the tests
        if (rightCol > 0 && rightCol < GRID_COLS)
        {
            GamePiece* rightPiece = getGamePieceAtIndex(basePieceindex.y, rightCol);
            CCPoint rightPieceLocation = rightPiece->getPosition();
            CCLog("Actual right piece row:%f col:%f", rightPieceLocation.y, rightPieceLocation.x);
            // first make sure the piece hasn't already been checked
            if (rightPiece != NULL)
            {
                if (!rightPiece->isInElinationCheck())
                {
                    if (basePiece->getPieceColor() == rightPiece->getPieceColor())
                    {
                        CCLog("FOUND MATCH");
                        // piece above matches trigger recursive check with this as a the base piece
                        comboCount = MAX(comboCount, eliminateGamePieces(rightPiece,comboCount+1));
                    }
                    else
                    {
                        CCLog("NO MATCH FOUND");
                    }
                }
                else
                {
                    CCLog("PIECE ALREADY CHECKED");
                }
            }
            else
            {
                CCLog("PIECE NOT VALID");
            }
        }
        else
        {
            CCLog("PIECE OUT OF BOUNDS");
        }
        
        // check down
        float downRow = basePieceindex.y - 1.0f;
        CCLog("Check piece row:%f col:%f", basePieceindex.y, basePieceindex.x);
        CCLog("Down piece row:%f col:%f", downRow, basePieceindex.x);
        
        // really only need to check if the index is out of bounds in one direction since the
        // basePieceindex is assumed to be valid, but checking both for completeness.
        // similar checks for the rest of the tests
        if (downRow >= 0 && downRow < GRID_ROWS)
        {
            GamePiece* downPiece = getGamePieceAtIndex(downRow, basePieceindex.x);
            CCPoint downPieceLocation = downPiece->getPosition();
            CCLog("Actual down piece row:%f col:%f", downPieceLocation.y, downPieceLocation.x);
            // first make sure the piece hasn't already been checked
            if (downPiece != NULL)
            {
                if (!downPiece->isInElinationCheck())
                {
                    if (basePiece->getPieceColor() == downPiece->getPieceColor())
                    {
                        CCLog("FOUND MATCH");
                        // piece above matches trigger recursive check with this as a the base piece
                        comboCount = MAX(comboCount, eliminateGamePieces(downPiece,comboCount+1));
                    }
                    else
                    {
                        CCLog("NO MATCH FOUND");
                    }
                }
                else
                {
                    CCLog("PIECE ALREADY CHECKED");
                }
            }
            else
            {
                CCLog("PIECE NOT VALID");
            }
        }
        else
        {
            CCLog("PIECE OUT OF BOUNDS");
        }
        
        // check left
        float leftCol = basePieceindex.x - 1.0f;
        CCLog("Check piece row:%f col:%f", basePieceindex.y, basePieceindex.x);
        CCLog("Piece to the left row:%f col:%f", basePieceindex.y, leftCol);
        
        // really only need to check if the index is out of bounds in one direction since the
        // basePieceindex is assumed to be valid, but checking both for completeness.
        // similar checks for the rest of the tests
        if (leftCol >= 0 && leftCol < GRID_COLS)
        {
            GamePiece* leftPiece = getGamePieceAtIndex(basePieceindex.y, leftCol);
            CCPoint leftPieceLocation = leftPiece->getPosition();
            CCLog("Actual right piece row:%f col:%f", leftPieceLocation.y, leftPieceLocation.x);
            // first make sure the piece hasn't already been checked
            if (leftPiece != NULL)
            {
                if (!leftPiece->isInElinationCheck())
                {
                    if (basePiece->getPieceColor() == leftPiece->getPieceColor())
                    {
                        CCLog("FOUND MATCH");
                        // piece above matches trigger recursive check with this as a the base piece
                        comboCount = MAX(comboCount, eliminateGamePieces(leftPiece,comboCount+1));
                    }
                    else
                    {
                        CCLog("NO MATCH FOUND");
                    }
                }
                else
                {
                    CCLog("PIECE ALREADY CHECKED");
                }
            }
            else
            {
                CCLog("PIECE NOT VALID");
            }
        }
        else
        {
            CCLog("PIECE OUT OF BOUNDS");
        }

        // reset the flag to indicate the piece is in an eliminate loop check
        basePiece->setElinationCheck(false);
        
        // remove the piece
        // try just deleting it (hopefully the rest of the code has checks for valid pieces)
        //delete basePiece;
        basePiece->setVisible(false);
        
        CCLog("COMBO COUNT: %d", comboCount);
    }
    else
    {
        CCLog("BASE NOT VALID");
    }
    CCLog("XX^^^^^^^^^^^^^XX");
    
    return comboCount;
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
    }
}

bool Grid::isLevelComplete()
{
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            // check each gamePiece in the grid and if all are not visible then return true
            // otherwise return false
            GamePiece* gamePieceSprite = gridTable[i][j];
            if (gamePieceSprite->isVisible())
            {
                return false;
            }
        }
    }
    return true;
}

int Grid::getCurrentScore()
{
    return m_score;
}

void Grid::setPieceLocaiton(int row, int col)
{
    
}

// returns the width of the piece referenced with grid padding
// assumes all pieces are the same size
int Grid::getPieceWidth()
{
    GamePiece* pieceReference = gridTable[0][0];
    return pieceReference->getTextureWidth() + VisibleRect::getScaledFont(GRID_SPACE);
}

// returns the height of the piece referenced with grid padding
// assumes all pieces are the same size
int Grid::getPieceHeight()
{
    GamePiece* pieceReference = gridTable[0][0];
    return pieceReference->getTextureHeight() + VisibleRect::getScaledFont(GRID_SPACE);
}

