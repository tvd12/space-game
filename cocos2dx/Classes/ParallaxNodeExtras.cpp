//
//  CCParallaxNodeExtras.cpp
//  space-game-mobile
//
//  Created by Dung Ta Van on 3/7/21.
//

#include "ParallaxNodeExtras.h"

USING_NS_CC;

// Hack to access CCPointObject (which is not a public class)
class PointObject: Ref {
    CC_SYNTHESIZE(Point, m_tRatio, Ratio)
    CC_SYNTHESIZE(Point, m_tOffset, Offset)
    CC_SYNTHESIZE(Node *, m_pChild, Child)    // weak ref
};

// Need to provide a constructor
ParallaxNodeExtras::ParallaxNodeExtras() {
    ParallaxNode(); // call parent constructor
}

ParallaxNodeExtras::~ParallaxNodeExtras() {
    _parallaxArray = 0;
}

ParallaxNodeExtras * ParallaxNodeExtras::node() {
    ParallaxNodeExtras* pRet = new ParallaxNodeExtras();
    return pRet;
}

void ParallaxNodeExtras::incrementOffset(Point offset, Node* node){
    for(unsigned int i = 0; i < _parallaxArray->num; i++) {
        PointObject *point = (PointObject *)_parallaxArray->arr[i];
        Node * curNode = point->getChild();
        if(curNode == node) {
            point->setOffset(point->getOffset() + offset);
            break;
        }
    }
}
