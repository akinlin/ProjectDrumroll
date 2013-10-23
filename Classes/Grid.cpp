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

enum InteractionState
{
    is_empty = 0,
    is_slide = 1,
    is_rotary = 2,
    is_switch = 3,
    is_dpadflip = 4,
    is_flip = 5,
    is_count = 6
};

const int GRID_SPACE = 10;

Grid::Grid()
{
    // reset score
    m_score = 0;
    m_highComboCount  = 0;
    m_interactionCount = 0;
    
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
            // set piece width and height (assuming all are the same size)
            m_pieceTextureWidth = gamePieceSprite->getTextureWidth();
            m_pieceTextureHeight = gamePieceSprite->getTextureHeight();

            int piecePosX = (j * m_pieceTextureWidth) + (VisibleRect::getScaledFont(GRID_SPACE) * j);
            int piecePoxY = (i * m_pieceTextureHeight) + (VisibleRect::getScaledFont(GRID_SPACE) * i);
            
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
    m_gridWidth = (m_pieceTextureWidth * GRID_COLS) + (VisibleRect::getScaledFont(GRID_SPACE) * GRID_COLS);
    m_gridHeight = (m_pieceTextureHeight * GRID_ROWS) + (VisibleRect::getScaledFont(GRID_SPACE) * GRID_ROWS);
    
    // set content size to grid size, assuming all pieces are the same size
    setContentSize(CCSizeMake(m_gridWidth, m_gridHeight));
    
    m_touchState = interact;
    m_interactionState = is_empty;
    m_interactionGamePiece = NULL;
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
    if (row < GRID_ROWS && row >= 0 && col < GRID_COLS && col >= 0)
    {
        return gridTable[row][col];
    }
    return NULL;
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
    // check if location is within grid bounds
    if (getPositionX() <= p.x && getPositionX() + getWidth() >= p.x)
    {
        if (getPositionY() <= p.y && getPositionY() + getHeight() >= p.y)
        {
            // touch location is within the grid
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
    }
    return NULL;
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
            
    // find the piece selected
    GamePiece* gamePieceSprite = getGamePieceAtLocation(p);
    if (gamePieceSprite != NULL)
    {
        if (gamePieceSprite->isVisible())
        {
            // handle the touch according to touchState
            if (m_touchState == interact)
            {
                // handle the interaction type
                
                // super bad hard core coupling between this and GamePiece.cpp gamePieceInteractionType enum
                // FIX IT SOON!!!
//                        pieceInteractionSlide = 0,
//                        pieceInteractionRotary = 1,
//                        pieceInteractionSwitch = 2,
//                        pieceInteractionFlip = 3,
//                        pieceInteractionCount = 4
                switch (m_interactionState)
                {
                    // pieceInteractionSlide
                    case is_slide:
//                        m_interactionState = is_empty;
//                        m_interactionGamePiece = NULL;
                        break;
                    
                    // pieceInteractionRotary
                    case is_rotary:
//                        m_interactionState = is_empty;
//                        m_interactionGamePiece = NULL;
                        break;
                     
                    // pieceInteractionSwitch
                    case is_switch:
                        if (m_interactionGamePiece != NULL)
                        {
                            handleSwitchInteraction(gamePieceSprite);
                            m_interactionState = is_empty;
                            m_interactionGamePiece = NULL;
                        }
                        else
                        {
                            m_interactionGamePiece = gamePieceSprite;
                        }
                        break;
                        
                    case is_flip:
                        // flip the piece
                        handleFlipInteraction(gamePieceSprite);
                        break;
                        
                    case is_dpadflip:
                        handleDPadFlipInteraction(gamePieceSprite);
                        break;
                      
                    // pieceInteractionFlip is case 3 and default
                    default:
                        break;
                }
                
            }
            else
            {
                // do something with it to test the touch location
                int comboCount = eliminateGamePieces(gamePieceSprite,0);
                // reset the pieces in the grid
                recalculateGrid();
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
                
                // set the high combo
                if (comboCount > m_highComboCount)
                {
                    m_highComboCount = comboCount;
                }
            }
        }
        CCLog("Touch handled");
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
    if(basePiece != NULL)
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
            // first make sure the piece hasn't already been checked
            if (abovePiece != NULL)
            {
                CCPoint abovePieceLocation = abovePiece->getPosition();
                CCLog("Actual above piece row:%f col:%f", abovePieceLocation.y, abovePieceLocation.x);
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
        basePiece->setActive(false);
        
        CCLog("COMBO COUNT: %d", comboCount);
    }
    else
    {
        CCLog("BASE NOT VALID");
    }
    CCLog("XX^^^^^^^^^^^^^XX");
    
    return comboCount;
}

void Grid::ccTouchesBegan(CCSet *touches, CCEvent *event)
{
    // Only handle the touch start if the touch state is interaction
    // Skip setting the state if interactionState is is_switch
    if (m_touchState == interact && m_interactionState != is_switch)
    {
        // Set the current grid state depending on the interaction type
        CCSetIterator it;
        CCTouch* touch;
        
        for( it = touches->begin(); it != touches->end(); it++)
        {
            touch = (CCTouch*)(*it);
            
            if(!touch)
                break;
            
            CCPoint location = touch->getLocationInView();
            location = CCDirector::sharedDirector()->convertToGL(location);
            
            // get the game piece that was selected
            GamePiece *selectedGamePiece = getGamePieceAtLocation(location);
            if (selectedGamePiece)
            {
                // FIX IT SOON
                switch (selectedGamePiece->getInteractionType())
                {
//                        // pieceInteractionSlide
//                    case 0:
//                        m_interactionState = is_slide;
//                        // set the selected game piece
//                        m_interactionGamePiece = selectedGamePiece;
//                        break;
//                        
//                        // pieceInteractionRotary
//                    case 1:
//                        m_interactionState = is_rotary;
//                        // set the selected game piece
//                        m_interactionGamePiece = selectedGamePiece;
//                        break;
//                        
//                        // pieceInteractionSwitch
//                    case 2:
//                        m_interactionState = is_switch;
//                        break;
                    case 1:
                        m_interactionState = is_flip;
                        break;
                        
                    case 2:
                        m_interactionState = is_dpadflip;
                        break;
                        
                    case 3:
                        m_interactionState = is_switch;
                        break;
                        
                        // pieceInteractionFlip is case 3 and default
                    default:
                        m_interactionState = is_empty;
                        break;
                }
                // piece found break the loop
                break;
            }
        }
    }
}

void Grid::ccTouchesMoved(CCSet *touches, CCEvent *event)
{
    // Check the current grid state and handle the move event
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        // FIX IT SOON
        switch (m_interactionState)
        {
                // pieceInteractionSlide
            case is_slide:
                //handleSlideMove(location);
                break;
                
                // pieceInteractionRotary
            case is_rotary:
                //handleRotaryMove(location);
                break;
                
                // pieceInteractionFlip and pieceInteractionSwitch default to nothing on move
            default:
                break;
        }
    }
}

void Grid::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    // Check the current grid state and handle the end event
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        // legacy function handleTouch doesn't account for grid state
        handleTouch( location );
    }
}

void Grid::ccTouchesCancelled(CCSet *touches, CCEvent *event)
{
    CCLog("Touch Cancelled");
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

int Grid::getInteractionCount()
{
    return m_interactionCount;
}

int Grid::getComboCount()
{
    return m_highComboCount;
}

void Grid::setPieceLocaiton(int row, int col)
{
    
}

// returns the width of the piece referenced with grid padding
// assumes all pieces are the same size
int Grid::getPieceWidth()
{
    return m_pieceTextureWidth + VisibleRect::getScaledFont(GRID_SPACE);
}

// returns the height of the piece referenced with grid padding
// assumes all pieces are the same size
int Grid::getPieceHeight()
{
    return m_pieceTextureHeight + VisibleRect::getScaledFont(GRID_SPACE);
}

// remove the pieces that are not active and drop the pieces above
void Grid::recalculateGrid()
{
    // run through each column and move all of the pieces down if non-active pieces are below
    CCPoint firstNonActive;
    CCPoint firstNonActivePosition = CCPointZero;
    int numPreviousEmptyCols = 0;
    for (int i = 0; i < GRID_COLS; i++)
    {
        // check if the previous row was empty
        if (firstNonActive.x == -1)
        {
            // increment the previous row empty count
            numPreviousEmptyCols++;
        }
        else
        {
            // if previous rows are not empty then reset the pevious row empty counter
            numPreviousEmptyCols = 0;
        }
        
        // reset the point
        firstNonActive = ccp(-1,-1);
        for (int j = 0; j < GRID_ROWS; j++)
        {
            // check if the piece is not active
            if (!gridTable[j][i]->isActive())
            {
                // found a non active piece set the firstNoActive Point if not already set
                if (firstNonActive.x == -1)
                {
                    firstNonActive = ccp(j,i);
                    firstNonActivePosition = gridTable[j][i]->getPosition();
                }
            }
            else
            {
                // piece is active check if point is set
                if (firstNonActive.x != -1)
                {
                    // switch the piece to the new table reference
                    int row = firstNonActive.x;
                    int col = firstNonActive.y;
                    // goofy test
                    gridTable[row][col]->setPosition(gridTable[j][i]->getPosition());
                              
                    // move the piece to the firstNonActive location
                    gridTable[j][i]->setPosition(firstNonActivePosition);
                    
                    // extended goofy test
                    GamePiece* emptySpace = gridTable[row][col];
                    gridTable[row][col] = gridTable[j][i];
                    gridTable[j][i] = emptySpace;
                    
                    // update the firstNonActive point
                    CCPoint testPoint = gridTable[row][col]->getPosition();
                    row++;
                    if (row < GRID_ROWS)
                    {
                        firstNonActive = ccp(row, col);
                        firstNonActivePosition = ccp(firstNonActivePosition.x, getPieceHeight()*row);
                    }
                }
            }
        }
    }
    
    // first find all empty rows and move pieces to the left
    int emptyColumnCount = 0;
    for (int i = 0; i < GRID_COLS; i++)
    {
        // check the first game piece is active
        if (!gridTable[0][i]->isActive())
        {
            // assume this entire row is empty
            emptyColumnCount++;
        }
        else
        {
            // the game piece is active
            // check to for a column movement
            if (emptyColumnCount > 0)
            {
                // move the active column to the left
                // loop all of the pieces in the column until an empty piece is encountered
                for(int j = 0; j < GRID_ROWS; j++)
                {
                    // check for the first inactive piece
                    if (!gridTable[j][i]->isActive())
                    {
                        // if the piece is inactive break the loop
                        break;
                    }
                    
//                    // need a temp holder piece
//                    GamePiece gamePieceHolder = *gridTable[j][i - emptyColumnCount];
//                    // replace the empty piece pointer with the active piece
//                    gridTable[j][i - emptyColumnCount] = gridTable[j][i];
//                    // replace the moved active piece with the empty piece stored in holder
//                    gridTable[j][i] = &gamePieceHolder;
                    
                    // fix the positions
                    CCPoint positionHolder = gridTable[j][i - emptyColumnCount]->getPosition();
                    gridTable[j][i - emptyColumnCount]->setPosition(gridTable[j][i]->getPosition());
                    gridTable[j][i]->setPosition(positionHolder);
                    
                    // switch the pointers
                    GamePiece* pointerHolder = gridTable[j][i - emptyColumnCount];
                    gridTable[j][i - emptyColumnCount] = gridTable[j][i];
                    gridTable[j][i] = pointerHolder;
                    
                    //gridTable[j][i]->setColor(ccBLUE);
                }
                // hacky decrement the i counter
                i--;
                
                // reset the counter
                emptyColumnCount = 0;
            }
        }
    }
}

void Grid::handleSlideMove(CCPoint location)
{
    // slide the row or column until the user releases the touch
    // funky row move
    // all the pieces in the row the offset of the touch movement
    // get the current location of the selected piece
    CCPoint currLoc = m_interactionGamePiece->getPosition();
    
    // get the delta of the piece movement
    float deltaX = currLoc.x - location.x;
    
    // set the location of the selected piece to the new location
    //m_interactionGamePiece->setPosition(location);
    
    // offset all the pieces in the row by the delta
}

void Grid::handleRotaryMove(CCPoint location)
{
    // rotate the pieces in a rotary movement
    // this one might be tricky since it relies on the user input
    // this is probably best for a grid state to account for user input
}

void Grid::handleSwitchInteraction(GamePiece* gamePieceSprite)
{
    // switch two pieces location
    // need the gridTable pointers to switch the pieces
    CCPoint firstSelectedGamePieceIndex = getIndexAtGamePiece(m_interactionGamePiece);
    CCPoint secondSelectedGamePieceIndex = getIndexAtGamePiece(gamePieceSprite);
    GamePiece* firstGamePiece = getGamePieceAtIndex(firstSelectedGamePieceIndex.x, firstSelectedGamePieceIndex.y);
    GamePiece* secondGamePiece = getGamePieceAtIndex(secondSelectedGamePieceIndex.x, secondSelectedGamePieceIndex.y);
    int firstRow = firstSelectedGamePieceIndex.y;
    int firstCol = firstSelectedGamePieceIndex.x;
    int secondRow = secondSelectedGamePieceIndex.y;
    int secondCol = secondSelectedGamePieceIndex.x;
    
    // get the first selected gamepiece's location
    CCPoint selectedLocation = gridTable[firstRow][firstCol]->getPosition();
    // set the first selected gamepiece's location to the location of the second piece
    gridTable[firstRow][firstCol]->setPosition(gridTable[secondRow][secondCol]->getPosition());
    // set the second selected gamepiece's location to the saved location
    gridTable[secondRow][secondCol]->setPosition(selectedLocation);
    
    // switch the pointers
    GamePiece* pointerHolder = gridTable[firstRow][firstCol];
    gridTable[firstRow][firstCol] = gridTable[secondRow][secondCol];
    gridTable[secondRow][secondCol] = pointerHolder;
}

void Grid::handleFlipInteraction(GamePiece* gamePieceSprite)
{
    // single piece flip interaction
    // since this is an instant action no state is required
    
    gamePieceSprite->switchToNextPiece();
    
    // reset the interactionState
    m_interactionState = is_empty;
    
    // take away 5 points for every touch
    m_score = m_score - 5;
    
    // increment the interaction count
    m_interactionCount++;
}

void Grid::handleDPadFlipInteraction(GamePiece* gamePieceSprite)
{
    // DPad flip interaction
    // since this is an instant action no state is required
    // do something with it to test the touch location
    
    // change the pieces to the top/bottom/left/right
    CCPoint selectedIndex = getIndexAtGamePiece(gamePieceSprite);
    CCLog("Index x:%f y:%f", selectedIndex.x, selectedIndex.y);
    // check up
    GamePiece* gamePieceHolder = getGamePieceAtIndex(selectedIndex.y + 1, selectedIndex.x);
    if(gamePieceHolder != NULL)
    {
        gamePieceHolder->switchToNextPiece();
    }
    
    // check right
    gamePieceHolder = getGamePieceAtIndex(selectedIndex.y, selectedIndex.x + 1);
    if(gamePieceHolder != NULL)
    {
        gamePieceHolder->switchToNextPiece();
    }
    
    // check bottom
    gamePieceHolder = getGamePieceAtIndex(selectedIndex.y - 1, selectedIndex.x);
    if(gamePieceHolder != NULL)
    {
        gamePieceHolder->switchToNextPiece();
    }
    
    // check left
    gamePieceHolder = getGamePieceAtIndex(selectedIndex.y, selectedIndex.x - 1);
    if(gamePieceHolder != NULL)
    {
        gamePieceHolder->switchToNextPiece();
    }
    
    // reset the interactionState
    m_interactionState = is_empty;
    
    // take away 5 points for every touch
    m_score = m_score - 5;
    
    // increment the interaction count
    m_interactionCount++;
}


