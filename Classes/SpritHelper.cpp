//
//  SpritHelper.cpp
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#include "SpritHelper.h"
#include "ScreenHelper.h"

const int targetWidth = 320;
const int targetHeight = 480;

CCTexture2D* TextureManager::s_blocksSpriteSheet;
CCTexture2D* TextureManager::s_jewelsSpriteSheet;

static bool initRun = false;

void TextureManager::lazyInit()
{
    if (!initRun)
    {
        CCSpriteBatchNode *parent;
        
        // set the blocks texture
        // create batch sprite for blocks
        parent = CCSpriteBatchNode::create("blocks.png", 100);
        parent->setScale(VisibleRect::getScale());
        s_blocksSpriteSheet = parent->getTexture();
        
        // set the jewels texture
        // create batch sprite for blocks
        parent = CCSpriteBatchNode::create("jewels.png", 100);
        parent->setScale(VisibleRect::getScale());
        s_jewelsSpriteSheet = parent->getTexture();
        
        initRun = true;
    }
}

CCTexture2D* TextureManager::getBlocksTexture()
{
    lazyInit();
    return s_blocksSpriteSheet;
}

CCTexture2D* TextureManager::getJewelsTexture()
{
    lazyInit();
    return s_jewelsSpriteSheet;
}

int TextureManager::getTextureWidth()
{
    return VisibleRect::getScaledFont(32);
}

int TextureManager::getTextureHeight()
{
    return VisibleRect::getScaledFont(32);
}
