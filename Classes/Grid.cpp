//
//  Grid.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#include "Grid.h"
#include "GamePiece.h"

Grid::Grid()
{
    // create game pieces and fill the grid
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            // create a piece and assign it to the grid location
            GamePiece* gamePieceSprite = new GamePiece();
            gamePieceSprite->setPosition(ccp(j * gamePieceSprite->getTextureWidth(), i * gamePieceSprite->getTextureHeight()));
            gridTable[i][j] = gamePieceSprite;
            
            gridWidth += gamePieceSprite->getTextureWidth();
            gridHeight += gamePieceSprite->getTextureHeight();
            
            addChild(gridTable[i][j]);
        }
    }
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

GamePiece Grid::getGamePieceAtIndex(int row, int col)
{
    return *gridTable[row][col];
}

int Grid::getWidth()
{
    return gridWidth;
}

int Grid::getHeight()
{
    return gridHeight;
}


