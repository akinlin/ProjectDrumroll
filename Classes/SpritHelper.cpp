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
    // hard coded to the blocks size
    return 32;
}

int TextureManager::getTextureHeight()
{
    // hard coded to the blocks size
    return 32;
}

int TextureManager::getScaledTextureWidth()
{
    // hard coded to the blocks size
    return VisibleRect::getScaledFont(getTextureWidth());
}

int TextureManager::getScaledTextureHeight()
{
    // hard coded to the blocks size
    return VisibleRect::getScaledFont(getTextureHeight());
}

//
// TextureManagerTesting Class
//////////////////////////////////////////////////////////////////////////////////////

CCTexture2D* TextureManagerTesting::getTexture()
{
    return m_Texture;
};


//
// Blocks Class
//////////////////////////////////////////////////////////////////////////////////////

Blocks::Blocks()
{
    CCSpriteBatchNode *parent;
    
    // set the blocks texture
    // create batch sprite for blocks
    parent = CCSpriteBatchNode::create("blocks.png", 100);
    parent->setScale(VisibleRect::getScale());
    m_Texture = parent->getTexture();
};

// returns the width and height before scaling is done
int Blocks::getActualTextureWidth()
{
    return 32;
};
 int Blocks::getActualTextureHeight()
{
    return 32;
};

// returns the width and height after scaling is done
int Blocks::getScaledTextureWidth()
{
    return VisibleRect::getScaledFont(getActualTextureWidth());
};
int Blocks::getScaledTextureHeight()
{
    return VisibleRect::getScaledFont(getActualTextureHeight());
};

// returns a list of rects based on the sprite sheet
//CCRect* Blocks::getSpriteRects()
//{
//    m_TextureRects = new CCRect* [4]
//    {
//        CCRectMake(0,0,32,32),
//        CCRectMake(0,1,32,32),
//        CCRectMake(1,0,32,32),
//        CCRectMake(1,1,32,32)
//    }
//    return m_TextureRects;
//};

CCRect Blocks::getSpriteRect(int sprite)
{
    switch (sprite) {
        case 0:
            return CCRectMake(0, 0, 32, 32);
            break;
        case 1:
            return CCRectMake(32, 0, 32, 32);
            break;
        case 2:
            return CCRectMake(0, 32, 32, 32);
            break;
        case 3:
            return CCRectMake(32, 32, 32, 32);
            
        default:
            CCLog("Failed to find sprite type");
            break;
    }
    return CCRectMake(0, 0, 32, 32);
};

//
// Jewles Class
//////////////////////////////////////////////////////////////////////////////////////

Jewles::Jewles()
{
    CCSpriteBatchNode *parent;
    
    // set the jewels texture
    // create batch sprite for blocks
    parent = CCSpriteBatchNode::create("jewels.png", 100);
    parent->setScale(VisibleRect::getScale());
    m_Texture = parent->getTexture();
};

// returns the width and height before scaling is done
int Jewles::getActualTextureWidth()
{
    return 32;
};
int Jewles::getActualTextureHeight()
{
    return 32;
};

// returns the width and height after scaling is done
int Jewles::getScaledTextureWidth()
{
    return VisibleRect::getScaledFont(getActualTextureWidth());
};
int Jewles::getScaledTextureHeight()
{
    return VisibleRect::getScaledFont(getActualTextureHeight());
};

CCRect Jewles::getSpriteRect(int sprite)
{
    return CCRectMake(0, 0, 32, 32);
};

// returns a list of rects based on the sprite sheet
//CCRect* Jewles::getSpriteRects()
//{
//    m_TextureRects =
//    {
//        CCRectMake(0,0,32,32),
//        CCRectMake(0,1,32,32),
//        CCRectMake(1,0,32,32),
//        CCRectMake(1,1,32,32)
//    }
//    return m_TextureRects;
//};

