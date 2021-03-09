//
//  CCParallaxNodeExtras.cpp
//  space-game-mobile
//
//  Created by Dung Ta Van on 3/7/21.
//

#include "ParallaxNodeExtras.h"

USING_NS_CC;

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
        IPointObject* point = (IPointObject*)_parallaxArray->arr[i];
        Node* curNode = point->getChild();
        if(curNode == node) {
            point->setOffset(point->getOffset() + offset);
            break;
        }
    }
}
