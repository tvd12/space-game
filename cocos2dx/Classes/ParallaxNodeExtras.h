//
//  ParallaxNodeExtras.h
//  space-game-mobile
//
//  Created by Dung Ta Van on 3/7/21.
//

#ifndef ParallaxNodeExtras_h
#define ParallaxNodeExtras_h

#include "cocos2d.h"

class ParallaxNodeExtras : public cocos2d::ParallaxNode {
public:
    
    // Need to provide a constructor
    ParallaxNodeExtras();
    ~ParallaxNodeExtras();
    
    // just to avoid ugly later cast and also for safety
    static ParallaxNodeExtras* node();
    
    // Facility method (it’s expected to have it soon in COCOS2DX)
    void incrementOffset(cocos2d::Point offset, cocos2d::Node* node);
} ;

#endif /* ParallaxNodeExtras_h */
