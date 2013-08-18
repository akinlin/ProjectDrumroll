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
    
private:
    static void lazyInit();
    static CCTexture2D* s_blocksSpriteSheet;
    static CCTexture2D* s_jewelsSpriteSheet;
};

#endif /* defined(__ProjectDrumroll__SpritHelper__) */
