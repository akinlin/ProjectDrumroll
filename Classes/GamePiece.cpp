//
//  GamePiece.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#include "GamePiece.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "ScreenHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

// TODO: review if this should be part of the spritehelper class
enum gamePieceColor
{
    pieceColorYellow = 0,
    pieceColorPurple = 1,
    pieceColorRed = 2,
    pieceColorGreen = 3,
    gamePieceColorCount = 4
};

enum gamePieceInteractionType
{
    pieceInteractionToggle = 0,
    pieceInteractionCount = 1,
};

GamePiece::GamePiece()
{
    // set elimination state flag
    // TODO: review if this should be part of a statemachine
    m_isInElinationCheck = false;
    // set the active flag
    m_isActive = true;
    
    s_color = arc4random() % gamePieceColorCount;
    s_interactionType = arc4random() % pieceInteractionCount;
    
//    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
//    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
//    CCTexture2D* textureSheet = TextureManager::getBlocksTexture();
//    
//    textureWidth = TextureManager::getTextureWidth();
//    textureHeight = TextureManager::getTextureHeight();
    
    m_BlocksSprite = new Blocks();
    
    this->initWithTexture(m_BlocksSprite->getTexture(), m_BlocksSprite->getSpriteRect(s_color));
    this->setScale(VisibleRect::getScale());
    this->autorelease();
}

int GamePiece::getPieceColor()
{
    return s_color;
}

int GamePiece::getInteractionType()
{
    return s_interactionType;
}

int GamePiece::getTextureWidth()
{
    // temp solution need to save a local variable
    // retuns the scaled value, probably should create a seperate funcation
    return m_BlocksSprite->getScaledTextureWidth();
}

int GamePiece::getTextureHeight()
{
    // temp solution need to save a local variable
    // retuns the scaled value, probably should create a seperate funcation
    return m_BlocksSprite->getScaledTextureHeight();
}

void GamePiece::switchToRandomPiece()
{
    if (this != NULL)
    {
        s_color = arc4random() % gamePieceColorCount;
        this->setTextureRect(m_BlocksSprite->getSpriteRect(s_color));
    }
}

bool GamePiece::isInElinationCheck()
{
    return m_isInElinationCheck;
}

void GamePiece::setElinationCheck(bool isInEliminationCheck)
{
    m_isInElinationCheck = isInEliminationCheck;
}

bool GamePiece::isActive()
{
    return m_isActive;
}

void GamePiece::setActive(bool isActive)
{
    m_isActive = isActive;
}