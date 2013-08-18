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
#include "SpritHelper.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum gamePieceColor
{
    pieceColorRed = 0,
    pieceColorBlue = 1,
    pieceColorGreen = 2,
    gamePieceColorCount = 3
};

enum gamePieceInteractionType
{
    pieceInteractionToggle = 0,
    pieceInteractionCount = 1,
};

GamePiece::GamePiece()
{
    s_color = arc4random() % gamePieceColorCount;
    s_interactionType = arc4random() % pieceInteractionCount;
    
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    CCTexture2D* textureSheet = TextureManager::getBlocksTexture();
    
    textureWidth = TextureManager::getTextureWidth();
    textureHeight = TextureManager::getTextureHeight();
    
    this->initWithTexture(textureSheet, CCRectMake(32 * idx, 32 * idy, 32, 32));
    this->setScale(VisibleRect::getScale());
    this->autorelease();
}

int GamePiece::getTextureWidth()
{
    // temp solution need to save a local variable 
    return textureWidth;
}

int GamePiece::getTextureHeight()
{
    // temp solution need to save a local variable
    return textureHeight;
}

