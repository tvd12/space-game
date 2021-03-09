//
//  CustomParallaxNode.hpp
//  space-game-mobile
//
//  Created by Dung Ta Van on 3/9/21.
//

#ifndef CustomParallaxNode_h
#define CustomParallaxNode_h

#include "cocos2d.h"

namespace cocos2d {
    struct _ccArray;
}

class IPointObject: public cocos2d::Ref {
public:
    virtual cocos2d::Node* getChild() const = 0;
    virtual const cocos2d::Vec2& getOffset() const = 0;
    virtual void setOffset(const cocos2d::Vec2& offset) = 0;
};

class CustomParallaxNode : public cocos2d::Node
{
public:
    static CustomParallaxNode* create();
    
    using cocos2d::Node::addChild;
    
    void addChild(cocos2d::Node * child, int z, const cocos2d::Vec2& parallaxRatio, const cocos2d::Vec2& positionOffset);
    
    void setParallaxArray(struct cocos2d::_ccArray *parallaxArray) { _parallaxArray = parallaxArray; }
    struct cocos2d::_ccArray* getParallaxArray() { return _parallaxArray; }
    const struct cocos2d::_ccArray* getParallaxArray() const { return _parallaxArray; }
    
    virtual void removeChild(cocos2d::Node* child, bool cleanup) override;
    virtual void removeAllChildrenWithCleanup(bool cleanup) override;
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
    
CC_CONSTRUCTOR_ACCESS:
    CustomParallaxNode();
    virtual ~CustomParallaxNode();
    
protected:
    cocos2d::Vec2 absolutePosition();
    
    cocos2d::Vec2    _lastPosition;
    struct cocos2d::_ccArray* _parallaxArray;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(CustomParallaxNode);
};

#endif /* CustomParallaxNode_hpp */
