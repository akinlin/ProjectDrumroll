//
//  SpritHelper.h
//  ProjectDrumroll
//
//  Created by Alexander Kinlin on 8/17/13.
//
//

#ifndef __ProjectDrumroll__SpritHelper__
#define __ProjectDrumroll__SpritHelper__

#include "cocos2d.h"
USING_NS_CC;

class TextureManager
{
public:
    static CCTexture2D* getBlocksTexture();
    static CCTexture2D* getJewelsTexture();
    
    // this is stupid but it will work
    static int getTextureWidth();
    static int getTextureHeight();
    static int getScaledTextureWidth();
    static int getScaledTextureHeight();
    
    static CCRect* textureRectArray[];
    
private:
    static void lazyInit();
    static CCTexture2D* s_blocksSpriteSheet;
    static CCTexture2D* s_jewelsSpriteSheet;
};

class TextureManagerTesting
{
protected:
    CCTexture2D* m_Texture;
    //CCRect* m_TextureRects[];
    
public:
    // returns the texture pointer
    CCTexture2D* getTexture();
    
    // returns the width and height before scaling is done
    virtual int getActualTextureWidth() = 0;
    virtual int getActualTextureHeight() = 0;
    // returns the width and height after scaling is done
    virtual int getScaledTextureWidth() = 0;
    virtual int getScaledTextureHeight() = 0;
    // returns a list of rects based on the sprite sheet
    //virtual CCRect* getSpriteRects();
    virtual CCRect getSpriteRect(int sprite) = 0;
};

class Blocks : public TextureManagerTesting
{
public:
    Blocks();
    
    // returns the width and height before scaling is done
    virtual int getActualTextureWidth();
    virtual int getActualTextureHeight();
    // returns the width and height after scaling is done
    virtual int getScaledTextureWidth();
    virtual int getScaledTextureHeight();
    // returns a list of rects based on the sprite sheet
    //virtual CCRect* getSpriteRects();
    virtual CCRect getSpriteRect(int sprite);
    
private:
    //const int NUM_SPRITES = 4;
    
};

class Jewles : public TextureManagerTesting
{
public:
    Jewles();
    
    // returns the width and height before scaling is done
    virtual int getActualTextureWidth();
    virtual int getActualTextureHeight();
    // returns the width and height after scaling is done
    virtual int getScaledTextureWidth();
    virtual int getScaledTextureHeight();
    // returns a list of rects based on the sprite sheet
    //virtual CCRect* getSpriteRects();
    virtual CCRect getSpriteRect(int sprite);
    
private:
    // This is way wrong but I didn't want to figure it out right now
    //const int NUM_SPRITES = 4;
};

#endif /* defined(__ProjectDrumroll__SpritHelper__) */
